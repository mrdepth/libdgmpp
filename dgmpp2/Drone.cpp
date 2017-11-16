//
//  Drone.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Drone.hpp"

namespace dgmpp2 {
	
	const Drone::SquadronTag Drone::anySquadronTag = -1;
	
	Drone::Drone (TypeID typeID): Type(typeID) {
		
		if ((*this)[AttributeID::fighterSquadronIsHeavy])
			squadron_ = Squadron::heavy;
		else if ((*this)[AttributeID::fighterSquadronIsLight])
			squadron_ = Squadron::light;
		else if ((*this)[AttributeID::fighterSquadronIsSupport])
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

		auto damageAttributes = {AttributeID::emDamage,
			AttributeID::explosiveDamage,
			AttributeID::kineticDamage,
			AttributeID::thermalDamage,
			AttributeID::fighterAbilityMissilesDamageMultiplier,
			AttributeID::fighterAbilityAttackMissileDamageMultiplier,
			AttributeID::fighterAbilityAttackTurretDamageMultiplier};
		
		flags_.dealsDamage = std::any_of(damageAttributes.begin(), damageAttributes.end(), [&](auto i) {
			return static_cast<bool>((*this)[i]);
		});
		
		flags_.active = true;
		
		if (auto attribute = (*this)[AttributeID::entityMissileTypeID]) {
			auto typeID = static_cast<TypeID>(attribute->value());
			auto charge = add(Charge::Create(typeID));
			
			flags_.isAssistance = flags_.isAssistance || charge->isAssistance();
			flags_.isOffensive = flags_.isOffensive || charge->isOffensive();
			flags_.dealsDamage = flags_.dealsDamage || charge->dealsDamage();
		}
		


		
	}
	
	void Drone::active(bool active) {
		if (flags_.active == active)
			return;
		
		if (active) {
			activateEffects(MetaInfo::Effect::Category::generic);
			activateEffects(MetaInfo::Effect::Category::target);
		}
		else {
			deactivateEffects(MetaInfo::Effect::Category::target);
			deactivateEffects(MetaInfo::Effect::Category::generic);
		}
	}
	
	void Drone::setEnabled (bool enabled) {
		Type::setEnabled(enabled);
		if (enabled && active()) {
			activateEffects(MetaInfo::Effect::Category::generic);
			activateEffects(MetaInfo::Effect::Category::target);
		}
		else {
			deactivateEffects(MetaInfo::Effect::Category::target);
			deactivateEffects(MetaInfo::Effect::Category::generic);
		}
	}
	
	Type* Drone::domain (MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::target :
				return nullptr;
			default:
				return Type::domain(domain);
		}
	}
	
	size_t Drone::squadronSize() {
		if (squadron_ == Squadron::none)
			return 5;
		else
			return static_cast<size_t>((*this)[AttributeID::fighterSquadronMaxSize]->value()) ?: 5;
	}
}
