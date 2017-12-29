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
		if (target_)
			target_->removeProjected(this);
	}
	
	Drone::Drone (TypeID typeID): Type(typeID) {
		
		if (attribute(AttributeID::fighterSquadronIsHeavy))
			squadron_ = Squadron::heavy;
		else if (attribute(AttributeID::fighterSquadronIsLight))
			squadron_ = Squadron::light;
		else if (attribute(AttributeID::fighterSquadronIsSupport))
			squadron_ = Squadron::support;
		else
			squadron_ = Squadron::none;

		const auto& effects = this->effects();

		flags_.isAssistance = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isAssistance;
		});
		
		flags_.isOffensive = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isOffensive;
		});

		flags_.dealsDamage = std::any_of(SDE::droneDamageAttributes.begin(), SDE::droneDamageAttributes.end(), [&](auto i) {
			return static_cast<bool>(attribute(i));
		});
		
		flags_.active = true;
		
		if (auto attribute = this->attribute(AttributeID::entityMissileTypeID)) {
			auto typeID = static_cast<TypeID>(static_cast<int>(attribute->value_()));
			charge_ = Charge::Create(typeID);
			charge_->parent_(this);
			
			flags_.isAssistance = flags_.isAssistance || charge_->isAssistance();
			flags_.isOffensive = flags_.isOffensive || charge_->isOffensive();
			flags_.dealsDamage = flags_.dealsDamage || charge_->dealsDamage();
		}
	}
	
	Drone::Drone (const Drone& other): Type(other) {
		flags_ = other.flags_;
		squadron_ = other.squadron_;
		squadronTag_ = other.squadronTag_;
		if (auto charge = other.charge()) {
			charge_ = Charge::Create(*charge);
		}
	}
	
	void Drone::active(bool active) {
		if (flags_.active == active || !isEnabled())
			return;
		
		if (active) {
			activateEffects(MetaInfo::Effect::Category::generic);
			activateEffects(MetaInfo::Effect::Category::target);
			if (charge_ != nullptr)
				charge_->setEnabled(true);
		}
		else {
			deactivateEffects(MetaInfo::Effect::Category::target);
			deactivateEffects(MetaInfo::Effect::Category::generic);
			if (charge_ != nullptr)
				charge_->setEnabled(false);
		}
		flags_.active = active;
	}
	
	void Drone::target(Ship* target) {
		batchUpdates([&]() {
			batchUpdates([&]() {
				if (target_) {
					if (active())
						deactivateEffects(MetaInfo::Effect::Category::target);
					target_->removeProjected(this);
				}
				target_ = target;
				if (target) {
					target_->project(this);
					if (active())
						activateEffects(MetaInfo::Effect::Category::target);
				}
			});
		});
	}
	
	void Drone::setEnabled (bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
		

		if (enabled && active()) {
			activateEffects(MetaInfo::Effect::Category::generic);
			activateEffects(MetaInfo::Effect::Category::target);
			if (charge_ != nullptr)
				charge_->setEnabled(enabled);
		}
		else {
			deactivateEffects(MetaInfo::Effect::Category::target);
			deactivateEffects(MetaInfo::Effect::Category::generic);
			if (charge_ != nullptr)
				charge_->setEnabled(enabled);
		}
	}
	
	Type* Drone::domain (MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::target :
				return target_;
			default:
				return Type::domain(domain);
		}
	}
	
	std::size_t Drone::squadronSize() {
		if (squadron_ == Squadron::none)
			return 5;
		else {
			auto size = static_cast<std::size_t>(attribute(AttributeID::fighterSquadronMaxSize)->value_());
			return size > 0 ? size : 5;
		}
	}
	
	//Calculations
	
	std::chrono::milliseconds Drone::cycleTime() {
		if (auto attribute = this->attribute(AttributeID::speed))
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		else if (auto attribute = this->attribute(AttributeID::duration))
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		else
			return std::chrono::milliseconds::zero();
	}
	
	DamageVector Drone::volley() {
		if (active()) {
			auto volley = droneVolley();

			if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackMissileDuration); attribute && attribute->value_() > 0)
				volley += fighterAttackMissileVolley();
			if (auto attribute = this->attribute(AttributeID::fighterAbilityMissilesDuration); attribute && attribute->value_() > 0)
				volley += fighterMissileVolley();
			if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackTurretDuration); attribute && attribute->value_() > 0)
				volley += fighterAttackTurretVolley();
			
			return volley;
		}
		else
			return {0};
	}
	
	DamageVector Drone::droneVolley() {
		auto volley = DamageVector(0);
		auto& item = charge_ ? *static_cast<Type*> (charge_.get()) : *static_cast<Type*>(this);
		
		if (auto attribute = item.attribute(AttributeID::emDamage))
			volley.em += attribute->value_();
		if (auto attribute = item.attribute(AttributeID::kineticDamage))
			volley.kinetic += attribute->value_();
		if (auto attribute = item.attribute(AttributeID::thermalDamage))
			volley.thermal += attribute->value_();
		if (auto attribute = item.attribute(AttributeID::explosiveDamage))
			volley.explosive += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::damageMultiplier))
			volley *= attribute->value_();

		return volley;
	}
	
	DamageVector Drone::fighterAttackMissileVolley() {
		auto volley = DamageVector(0);
		
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackMissileDamageEM))
			volley.em += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackMissileDamageKin))
			volley.kinetic += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackMissileDamageTherm))
			volley.thermal += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackMissileDamageExp))
			volley.explosive += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackMissileDamageMultiplier))
			volley *= attribute->value_();

		return volley;
	}
	
	DamageVector Drone::fighterAttackTurretVolley() {
		auto volley = DamageVector(0);
		
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackTurretDamageEM))
			volley.em += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackTurretDamageKin))
			volley.kinetic += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackTurretDamageTherm))
			volley.thermal += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackTurretDamageExp))
			volley.explosive += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackTurretDamageMultiplier))
			volley *= attribute->value_();
		
		return volley;
	}
	
	DamageVector Drone::fighterMissileVolley() {
		auto volley = DamageVector(0);
		
		if (auto attribute = this->attribute(AttributeID::fighterAbilityMissilesDamageEM))
			volley.em += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityMissilesDamageKin))
			volley.kinetic += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityMissilesDamageTherm))
			volley.thermal += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityMissilesDamageExp))
			volley.explosive += attribute->value_();
		if (auto attribute = this->attribute(AttributeID::fighterAbilityMissilesDamageMultiplier))
			volley *= attribute->value_();
		
		return volley;
	}

	DamagePerSecond Drone::dps(const HostileTarget& target) {
		if (active()) {
			auto dps = rawDPS();
			
			if (target.signature > 0) {
				using namespace std::chrono_literals;

				auto range = Meter(0);
				if (auto attribute = this->attribute(AttributeID::entityFlyRange); attribute && attribute->value_() > 0)
					range = attribute->value_();
				else if (auto attribute = this->attribute(AttributeID::fighterSquadronOrbitRange); attribute && attribute->value_() > 0)
					range = attribute->value_();
				
				auto orbitVelocity = MetersPerSecond(0);
				if (auto attribute = this->attribute(AttributeID::entityCruiseSpeed); attribute && attribute->value_() > 0)
					orbitVelocity = make_rate(attribute->value_(), 1s);
				else if (auto attribute = this->attribute(AttributeID::maxVelocity); attribute && attribute->value_() > 0)
					orbitVelocity = make_rate(attribute->value_(), 1s);
				
				if (target.velocity.count() > 0) {
					auto velocity = this->velocity();
					if (velocity < target.velocity)
						return DamagePerSecond(0);
					
					decltype(velocity) v {std::sqrt(velocity.count() * velocity.count() - target.velocity.count() * target.velocity.count())};
					orbitVelocity = std::min(orbitVelocity, v);
				}
				
				RadiansPerSecond angularVelocity = range > 0 ? make_rate(orbitVelocity * 1s / range, 1s) : RadiansPerSecond(0);
				
				Float a = 0;
				if (angularVelocity.count() > 0) {
					if (auto accuracyScore = this->accuracyScore(); accuracyScore > 0)
						a = angularVelocity * 1s / accuracyScore;
				}
				
				if (auto signatureResolution = attribute(AttributeID::optimalSigRadius); signatureResolution && signatureResolution->value_() > 0)
					a = signatureResolution->value_() / target.signature;
				
				Float b = 0;
				if (target.range > 0) {
					auto optimal = this->optimal();
					auto falloff = this->falloff();
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
	
	DamagePerSecond Drone::rawDPS() {
		
		auto dps = make_rate(droneVolley(), cycleTime());
		
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackMissileDuration); attribute && attribute->value_() > 0)
			dps += make_rate(fighterAttackMissileVolley(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_())));
		if (auto attribute = this->attribute(AttributeID::fighterAbilityMissilesDuration); attribute && attribute->value_() > 0)
			dps += make_rate(fighterMissileVolley(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_())));
		if (auto attribute = this->attribute(AttributeID::fighterAbilityAttackTurretDuration); attribute && attribute->value_() > 0)
			dps += make_rate(fighterAttackTurretVolley(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_())));
		return dps;
	}
	
	Meter Drone::optimal() {
		
		for (auto attributeID: SDE::droneOptimalAttributes) {
			if (auto attribute = this->attribute(attributeID))
				return attribute->value_();
		}
		
		if (auto charge = this->charge()) {
			auto maxVelocity = charge->attribute(AttributeID::maxVelocity);
			auto explosionDelay = charge->attribute(AttributeID::explosionDelay);
			
			if (maxVelocity && explosionDelay) {
				rate<Meter, std::chrono::milliseconds> mv = MetersPerSecond(maxVelocity->value_());
				auto flightTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep> (explosionDelay->value_()));
				return mv * flightTime;
			}
		}
		return 0;
	}
	
	Meter Drone::falloff() {
		for (auto attributeID: SDE::droneFalloffAttributes) {
			if (auto attribute = this->attribute(attributeID))
				return attribute->value_();
		}
		return 0;
	}
	
	Points Drone::accuracyScore() {
		if (auto attribute = this->attribute(AttributeID::trackingSpeed))
			return attribute->value_();
		else
			return 0;
	}
	
	CubicMeterPerSecond Drone::miningYield() {
		if (active()) {
			CubicMeter volley = 0;
			if (auto attribute = this->attribute(AttributeID::specialtyMiningAmount))
				volley += attribute->value_();
			if (auto attribute = this->attribute(AttributeID::miningAmount))
				volley += attribute->value_();
			return make_rate(volley, cycleTime());
		}
		else
			return CubicMeterPerSecond(0.0);
	}
	
	MetersPerSecond Drone::velocity() {
		using namespace std::chrono_literals;
		return make_rate(attribute(AttributeID::maxVelocity)->value_(), 1s);
	}

}
