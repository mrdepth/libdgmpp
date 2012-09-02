#include "Structure.h"
#include "Effect.h"
#include "Engine.h"
#include "Attribute.h"
#include "ControlTower.h"
#include "DamagePattern.h"
#include <math.h>

using namespace eufe;

static const float SHIELD_PEAK_RECHARGE = sqrt(0.25);

Structure::Structure(Engine* engine, TypeID typeID, Item* owner) : Module(engine, typeID, owner)
{
}

Structure::Structure(const Structure& from) : Module(from)
{
}

Structure::~Structure(void)
{
}

void Structure::setState(State state)
{
	if (canHaveState(state))
	{
		if (state < state_)
		{
			if (state_ >= STATE_ACTIVE && state < STATE_ACTIVE)
			{
				removeEffects(Effect::CATEGORY_ACTIVE);
				removeEffects(Effect::CATEGORY_TARGET);
			}
			if (state_ >= STATE_ONLINE && state < STATE_ONLINE)
			{
				removeEffects(Effect::CATEGORY_PASSIVE);
				getEffect(ONLINE_FOR_STRUCTURES_EFFECT_ID)->removeEffect(getEnvironment());
			}
		}
		else if (state > state_)
		{
			if (state_ < STATE_ONLINE && state >= STATE_ONLINE)
			{
				addEffects(Effect::CATEGORY_PASSIVE);
				getEffect(ONLINE_FOR_STRUCTURES_EFFECT_ID)->addEffect(getEnvironment());
			}
			if (state_ < STATE_ACTIVE && state >= STATE_ACTIVE)
			{
				addEffects(Effect::CATEGORY_ACTIVE);
				addEffects(Effect::CATEGORY_TARGET);
			}
		}
		state_ = state;
		engine_->reset(this);
	}
}

void Structure::reset()
{
	Module::reset();
	
	resistances_.armor.em = resistances_.armor.explosive = resistances_.armor.thermal = resistances_.armor.kinetic = -1;
	resistances_.hull = resistances_.shield = resistances_.armor;
	
	tank_.armorRepair = tank_.hullRepair = tank_.shieldRepair = tank_.passiveShield = -1.0;
	effectiveTank_ = tank_;
	
	hitPoints_.armor = hitPoints_.hull = hitPoints_.shield = -1.0;
	effectiveHitPoints_ = hitPoints_;
	
	shieldRecharge_ = -1;
}

//Tank

const Resistances& Structure::getResistances()
{
	if (resistances_.armor.em < 0.0)
	{
		resistances_.armor.em		 = 1.0 - getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.armor.explosive = 1.0 - getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.armor.kinetic   = 1.0 - getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.armor.thermal   = 1.0 - getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		
		resistances_.shield.em		  = 1.0 - getAttribute(SHIELD_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.shield.explosive = 1.0 - getAttribute(SHIELD_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.shield.kinetic   = 1.0 - getAttribute(SHIELD_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.shield.thermal   = 1.0 - getAttribute(SHIELD_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		
		resistances_.hull.em		= 1.0 - getAttribute(EM_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.hull.explosive = 1.0 - getAttribute(EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.hull.kinetic   = 1.0 - getAttribute(KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.hull.thermal   = 1.0 - getAttribute(THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
	}
	return resistances_;
}

const Tank& Structure::getTank()
{
	if (tank_.armorRepair < 0.0)
	{
		tank_.armorRepair = fabs(getAttribute(ARMOR_DAMAGE_ATTRIBUTE_ID)->getValue());
		tank_.hullRepair = fabs(getAttribute(DAMAGE_ATTRIBUTE_ID)->getValue());
		tank_.shieldRepair = fabs(getAttribute(SHIELD_CHARGE_ATTRIBUTE_ID)->getValue());
		tank_.passiveShield = getShieldRecharge();
	}
	return tank_;
}

const Tank& Structure::getEffectiveTank()
{
	ControlTower* controlTower = dynamic_cast<ControlTower*>(getOwner());
	const DamagePattern damagePattern = controlTower->getDamagePattern();
	if (effectiveTank_.armorRepair < 0.0)
		effectiveTank_ = damagePattern.effectiveTank(getResistances(), getTank());
	return effectiveTank_;
}

const HitPoints& Structure::getHitPoints()
{
	if (hitPoints_.armor < 0.0)
	{
		hitPoints_.armor = getAttribute(ARMOR_HP_ATTRIBUTE_ID)->getValue();
		hitPoints_.hull = getAttribute(HP_ATTRIBUTE_ID)->getValue();
		hitPoints_.shield = getAttribute(SHIELD_CAPACITY_ATTRIBUTE_ID)->getValue();
	}
	return hitPoints_;
}

const HitPoints& Structure::getEffectiveHitPoints()
{
	ControlTower* controlTower = dynamic_cast<ControlTower*>(getOwner());
	const DamagePattern damagePattern = controlTower->getDamagePattern();
	if (effectiveHitPoints_.armor < 0.0)
		effectiveHitPoints_ = damagePattern.effectiveHitPoints(getResistances(), getHitPoints());
	return effectiveHitPoints_;
}

float Structure::getShieldRecharge()
{
	if (shieldRecharge_ < 0.0)
	{
		float capacity = getAttribute(SHIELD_CAPACITY_ATTRIBUTE_ID)->getValue();
		float rechargeRate = getAttribute(SHIELD_RECHARGE_RATE_ATTRIBUTE_ID)->getValue();
		shieldRecharge_ = 10.0 / (rechargeRate / 1000.0) * SHIELD_PEAK_RECHARGE * (1 - SHIELD_PEAK_RECHARGE) * capacity;
	}
	return shieldRecharge_;
}
