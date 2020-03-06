//
//  Drone.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Drone.hpp"
#include "SDE.hpp"
#include "Ship.hpp"

namespace dgmpp {
	
	const Drone::SquadronTag Drone::anySquadronTag = -1;
	
	Drone::~Drone() {
        if (auto target = targetValue_.lock())
            target->removeProjected_(this);
        
        if (charge_ != nullptr) {
            charge_->parent_(nullptr);
        }
	}
	
	Drone::Drone (TypeID typeID): Type(typeID) {
		if (!std::any_of(SDE::droneCategories.begin(), SDE::droneCategories.end(), [categoryID = metaInfo().categoryID](const auto& i) { return categoryID == i; })) {
			throw InvalidCategoryID(metaInfo().categoryID);
		}
		
		flags_.isAssistance = std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isAssistance;
		});
		
		flags_.isOffensive = std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isOffensive;
		});

		flags_.dealsDamage = std::any_of(SDE::droneDamageAttributes.begin(), SDE::droneDamageAttributes.end(), [&](auto i) {
			return static_cast<bool>(attribute_(i));
		});
		
		flags_.hasKamikazeAbility = std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			return i->metaInfo().effectID == EffectID::fighterAbilityKamikaze;
		});
		
		flags_.active = true;
		flags_.kamikaze = false;
		
		if (charge_) {
			flags_.isAssistance = flags_.isAssistance || charge_->flags_.isAssistance;
			flags_.isOffensive = flags_.isOffensive || charge_->flags_.isOffensive;
			flags_.dealsDamage = flags_.dealsDamage || charge_->flags_.dealsDamage;
		}
	}
	
	Drone::Drone (const Drone& other):
		Type(other),
		squadron_(other.squadron_),
		squadronSize_(other.squadronSize_),
		charge_ ([this, &other]() -> std::shared_ptr<Charge> {
			if (auto charge = other.charge_.get()) {
				auto myCharge = std::make_shared<Charge>(*charge);
				myCharge->parent_(this);
				return myCharge;
			}
			else
				return nullptr;
		}())
	{
		flags_ = other.flags_;
		squadronTagValue_ = other.squadronTagValue_;
	}
	
	void Drone::active_(bool active) {
		if (flags_.active == active)
			return;
		else if (!isEnabled_()) {
			flags_.active = active;
			return;
		}
		
		batchUpdates_([&]() {
			if (active) {
				activateEffects_(MetaInfo::Effect::Category::generic);
				activateEffects_(MetaInfo::Effect::Category::target);
				if (charge_ != nullptr)
					charge_->setEnabled_(true);
			}
			else {
				deactivateEffects_(MetaInfo::Effect::Category::target);
				deactivateEffects_(MetaInfo::Effect::Category::generic);
				if (charge_ != nullptr)
					charge_->setEnabled_(false);
			}
			flags_.active = active;
		});
	}
	
	void Drone::kamikaze_ (bool kamikaze) {
		flags_.kamikaze = kamikaze;
	}
	
	void Drone::target_(const std::shared_ptr<Ship>& target) {
		batchUpdates_([&]() {
			if (auto target = targetValue_.lock()) {
				if (active_())
					deactivateEffects_(MetaInfo::Effect::Category::target);
				target->removeProjected_(this);
			}
			targetValue_ = target;
			if (target) {
				target->project_(this);
				if (active_())
					activateEffects_(MetaInfo::Effect::Category::target);
			}
		});
	}
	
	void Drone::setEnabled_ (bool enabled) {
		if (isEnabled_() == enabled)
			return Type::setEnabled_(enabled);
		else
			Type::setEnabled_(enabled);
		

		if (enabled && active_()) {
			activateEffects_(MetaInfo::Effect::Category::generic);
			activateEffects_(MetaInfo::Effect::Category::target);
			if (charge_ != nullptr)
				charge_->setEnabled_(enabled);
		}
		else {
			deactivateEffects_(MetaInfo::Effect::Category::target);
			deactivateEffects_(MetaInfo::Effect::Category::generic);
			if (charge_ != nullptr)
				charge_->setEnabled_(enabled);
		}
	}
	
	Type* Drone::domain_ (MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::target :
				return targetValue_.lock().get();
			default:
				return Type::domain_(domain);
		}
	}
	
//	std::size_t Drone::squadronSize_() {
//		if (squadron_ == Squadron::none)
//			return 5;
//		else {
//			auto size = static_cast<std::size_t>(attribute_(AttributeID::fighterSquadronMaxSize)->value_());
//			return size > 0 ? size : 5;
//		}
//	}
	
	//Calculations
	
	std::chrono::milliseconds Drone::cycleTime_() {
		if (auto attribute = attribute_(AttributeID::speed))
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		else if (auto attribute = attribute_(AttributeID::duration))
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		else if (auto attribute = attribute_(AttributeID::fighterAbilityLaunchBombDuration))
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		else
			return std::chrono::milliseconds::zero();
	}
	
	DamageVector Drone::volley_() {
		if (active_()) {
			auto volley = droneVolley_();

			if (auto attribute = attribute_(AttributeID::fighterAbilityAttackMissileDuration); attribute && attribute->value_() > 0)
				volley += fighterAttackMissileVolley_();
			if (auto attribute = attribute_(AttributeID::fighterAbilityMissilesDuration); attribute && attribute->value_() > 0)
				volley += fighterMissileVolley_();
			if (auto attribute = attribute_(AttributeID::fighterAbilityAttackTurretDuration); attribute && attribute->value_() > 0)
				volley += fighterAttackTurretVolley_();
			if (kamikaze_())
				volley += fighterKamikazeVolley_();
			return volley;
		}
		else
			return DamageVector{0};
	}
	
	DamageVector Drone::droneVolley_() {
		auto volley = DamageVector{ 0 };
		auto& item = charge_ ? *static_cast<Type*> (charge_.get()) : *static_cast<Type*>(this);
		
		if (auto attribute = item.attribute_(AttributeID::emDamage))
			volley.em += attribute->value_();
		if (auto attribute = item.attribute_(AttributeID::kineticDamage))
			volley.kinetic += attribute->value_();
		if (auto attribute = item.attribute_(AttributeID::thermalDamage))
			volley.thermal += attribute->value_();
		if (auto attribute = item.attribute_(AttributeID::explosiveDamage))
			volley.explosive += attribute->value_();
		if (auto attribute = attribute_(AttributeID::damageMultiplier))
			volley *= attribute->value_();

		return volley;
	}
	
	DamageVector Drone::fighterAttackMissileVolley_() {
		auto volley = DamageVector(0);
		
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackMissileDamageEM))
			volley.em += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackMissileDamageKin))
			volley.kinetic += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackMissileDamageTherm))
			volley.thermal += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackMissileDamageExp))
			volley.explosive += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackMissileDamageMultiplier))
			volley *= attribute->value_();

		return volley;
	}
	
	DamageVector Drone::fighterAttackTurretVolley_() {
		auto volley = DamageVector(0);
		
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackTurretDamageEM))
			volley.em += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackTurretDamageKin))
			volley.kinetic += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackTurretDamageTherm))
			volley.thermal += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackTurretDamageExp))
			volley.explosive += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackTurretDamageMultiplier))
			volley *= attribute->value_();
		
		return volley;
	}
	
	DamageVector Drone::fighterMissileVolley_() {
		auto volley = DamageVector(0);
		
		if (auto attribute = attribute_(AttributeID::fighterAbilityMissilesDamageEM))
			volley.em += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityMissilesDamageKin))
			volley.kinetic += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityMissilesDamageTherm))
			volley.thermal += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityMissilesDamageExp))
			volley.explosive += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityMissilesDamageMultiplier))
			volley *= attribute->value_();
		
		return volley;
	}

	DamageVector Drone::fighterKamikazeVolley_() {
		auto volley = DamageVector(0);
		
		if (auto attribute = attribute_(AttributeID::fighterAbilityKamikazeDamageEM))
			volley.em += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityKamikazeDamageKin))
			volley.kinetic += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityKamikazeDamageTherm))
			volley.thermal += attribute->value_();
		if (auto attribute = attribute_(AttributeID::fighterAbilityKamikazeDamageExp))
			volley.explosive += attribute->value_();
		
		return volley;
	}
	
	DamagePerSecond Drone::dps_(const HostileTarget& target) {
		if (active_()) {
			auto dps = rawDPS_();
			
			if (target.signature > 0) {
				using namespace std::chrono_literals;

				auto range = Meter(0);
				if (auto attribute = attribute_(AttributeID::entityFlyRange); attribute && attribute->value_() > 0)
					range = attribute->value_();
				else if (auto attribute = attribute_(AttributeID::fighterSquadronOrbitRange); attribute && attribute->value_() > 0)
					range = attribute->value_();
				
				auto orbitVelocity = MetersPerSecond(0);
				if (auto attribute = attribute_(AttributeID::entityCruiseSpeed); attribute && attribute->value_() > 0)
					orbitVelocity = make_rate(attribute->value_(), 1s);
				else if (auto attribute = attribute_(AttributeID::maxVelocity); attribute && attribute->value_() > 0)
					orbitVelocity = make_rate(attribute->value_(), 1s);
				
				if (target.velocity.count() > 0) {
					auto velocity = this->velocity_();
					if (velocity < target.velocity)
						return DamagePerSecond(0.0);
					
					decltype(velocity) v {std::sqrt(velocity.count() * velocity.count() - target.velocity.count() * target.velocity.count())};
					orbitVelocity = std::min(orbitVelocity, v);
				}
				
				RadiansPerSecond angularVelocity = range > 0 ? make_rate(orbitVelocity * 1s / range, 1s) : RadiansPerSecond(0);
				
				Float a = 0;
				if (angularVelocity.count() > 0) {
					if (auto accuracyScore = this->accuracyScore_(); accuracyScore > 0)
						a = angularVelocity * 1s / accuracyScore;
				}
				
				if (auto signatureResolution = attribute_(AttributeID::optimalSigRadius); signatureResolution && signatureResolution->value_() > 0)
					a = signatureResolution->value_() / target.signature;
				
				Float b = 0;
				if (target.range > 0) {
					auto optimal = this->optimal_();
					auto falloff = this->falloff_();
					b = falloff > 0 ? std::max(0.0, (range - optimal) / falloff) : 0;
				}
				
				auto blob = std::pow(a, 2) + std::pow(b, 2);
				auto hitChance = std::pow(0.5, blob);
				auto relativeDPS = hitChance > 0.01
				? (hitChance - 0.01) * (0.5 + (hitChance + 0.49)) / 2 + 0.01 * 3
				: hitChance * 3;
				return dps * relativeDPS;
			}
			else
				return dps;
		}
		else {
			return DamagePerSecond(0);
		}
	}
	
	DamagePerSecond Drone::rawDPS_() {
		auto dps = make_rate(droneVolley_(), cycleTime_());
		
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackMissileDuration); attribute && attribute->value_() > 0)
			dps += make_rate(fighterAttackMissileVolley_(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_())));
		if (auto attribute = attribute_(AttributeID::fighterAbilityMissilesDuration); attribute && attribute->value_() > 0)
			dps += make_rate(fighterMissileVolley_(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_())));
		if (auto attribute = attribute_(AttributeID::fighterAbilityAttackTurretDuration); attribute && attribute->value_() > 0)
			dps += make_rate(fighterAttackTurretVolley_(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_())));
		return dps;
	}
	
	Meter Drone::optimal_() {
		
		for (auto attributeID: SDE::droneOptimalAttributes) {
			if (auto attribute = attribute_(attributeID))
				return attribute->value_();
		}
		
		if (charge_) {
			auto maxVelocity = charge_->attribute_(AttributeID::maxVelocity);
			auto explosionDelay = charge_->attribute_(AttributeID::explosionDelay);
			
			if (maxVelocity && explosionDelay) {
				rate<Meter, std::chrono::milliseconds> mv = MetersPerSecond(maxVelocity->value_());
				auto flightTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep> (explosionDelay->value_()));
				return mv * flightTime;
			}
		}
		return 0;
	}
	
	Meter Drone::falloff_() {
		for (auto attributeID: SDE::droneFalloffAttributes) {
			if (auto attribute = attribute_(attributeID))
				return attribute->value_();
		}
		return 0;
	}
	
	Points Drone::accuracyScore_() {
		if (auto attribute = attribute_(AttributeID::trackingSpeed))
			return attribute->value_();
		else
			return 0;
	}
	
	CubicMeterPerSecond Drone::miningYield_() {
		if (active_()) {
			CubicMeter volley = 0;
			if (auto attribute = attribute_(AttributeID::specialtyMiningAmount))
				volley += attribute->value_();
			if (auto attribute = attribute_(AttributeID::miningAmount))
				volley += attribute->value_();
			return make_rate(volley, cycleTime_());
		}
		else
			return CubicMeterPerSecond(0.0);
	}
	
	MetersPerSecond Drone::velocity_() {
		using namespace std::chrono_literals;
		return make_rate(attribute_(AttributeID::maxVelocity)->value_(), 1s);
	}

}
