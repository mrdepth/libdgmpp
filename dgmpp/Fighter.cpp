//
//  Fighter.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 12.04.16.
//
//

#include "Fighter.h"
#include "Attribute.h"

using namespace dgmpp;

Fighter::Fighter(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Ship> const& owner): Drone(engine, typeID, owner) {
}

bool Fighter::dealsDamage() {
	loadIfNeeded();
	if (!isActive())
		return false;
	
	bool hasDamageAttribute = hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_EM_ATTRIBUTE_ID) ||
	hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_THERM_ATTRIBUTE_ID) ||
	hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_KIN_ATTRIBUTE_ID) ||
	hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_EXP_ATTRIBUTE_ID) ||
	hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EM_ATTRIBUTE_ID) ||
	hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_THERM_ATTRIBUTE_ID) ||
	hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_KIN_ATTRIBUTE_ID) ||
	hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EXP_ATTRIBUTE_ID);
	return hasDamageAttribute;
}

float Fighter::getCycleTime() {
	if (hasAttribute(SPEED_ATTRIBUTE_ID))
		return getAttribute(SPEED_ATTRIBUTE_ID)->getValue();
	else if (hasAttribute(DURATION_ATTRIBUTE_ID))
		return getAttribute(DURATION_ATTRIBUTE_ID)->getValue();
	else if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DURATION_ATTRIBUTE_ID))
		return getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DURATION_ATTRIBUTE_ID)->getValue();
	else
		return 0;
}


void Fighter::calculateDamageStats() {
	loadIfNeeded();
	if (!dealsDamage() || !isActive())
		dps_ = volley_ = 0;
	else
	{
		volley_ = 0;
		dps_ = 0;
		if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EM_ATTRIBUTE_ID))
			volley_.emAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EM_ATTRIBUTE_ID)->getValue();
		if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_KIN_ATTRIBUTE_ID))
			volley_.kineticAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_KIN_ATTRIBUTE_ID)->getValue();
		if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EXP_ATTRIBUTE_ID))
			volley_.explosiveAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EXP_ATTRIBUTE_ID)->getValue();
		if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_THERM_ATTRIBUTE_ID))
			volley_.thermalAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_THERM_ATTRIBUTE_ID)->getValue();
		
		if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
			volley_ *= getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();
		dps_ = volley_ / (getCycleTime() / 1000.0f) * (float) getSquadronSize();
	}
}

Fighter::Squadron Fighter::getSquadron() {
	loadIfNeeded();
	if (hasAttribute(FIGHTER_SQUADRON_IS_HEAVY_ATTRIBUTE_ID))
		return SQUADRON_HEAVY;
	else if (hasAttribute(FIGHTER_SQUADRON_IS_LIGHT_ATTRIBUTE_ID))
		return SQUADRON_LIGHT;
	else if (hasAttribute(FIGHTER_SQUADRON_IS_SUPPORT_ATTRIBUTE_ID))
		return SQUADRON_SUPPORT;
	else
		return SQUADRON_UNKNOWN;
}

int Fighter::getSquadronSize() {
	return getAttribute(FIGHTER_SQUADRON_MAX_SIZE_ATTRIBUTE_ID)->getValue();
}

