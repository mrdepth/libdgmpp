#include "StarbaseStructure.h"
#include "Effect.h"
#include "Engine.h"
#include "Attribute.h"
#include "ControlTower.h"
#include "DamagePattern.h"
#include <cmath>

using namespace dgmpp;

static const Float SHIELD_PEAK_RECHARGE = std::sqrt(0.25);

StarbaseStructure::StarbaseStructure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<ControlTower> const& owner) : Module(engine, typeID, owner)
{
}

StarbaseStructure::~StarbaseStructure(void)
{
}

void StarbaseStructure::setInternalState(State state)
{
	if (canHaveState(state))
	{
		if (state < state_)
		{
			if (state_ >= State::active && state < State::active)
			{
				removeEffects(Effect::Category::active);
				removeEffects(Effect::Category::target);
			}
			if (state_ >= Module::State::online && state < Module::State::online)
			{
				removeEffects(Effect::Category::passive);
				getEffect(EffectID::onlineForStructures)->removeEffect(this);
			}
		}
		else if (state > state_)
		{
			if (state_ < Module::State::online && state >= Module::State::online)
			{
				addEffects(Effect::Category::passive);
				getEffect(EffectID::onlineForStructures)->addEffect(this);
			}
			if (state_ < State::active && state >= State::active)
			{
				addEffects(Effect::Category::active);
				addEffects(Effect::Category::target);
			}
		}
		else
			return;
		
		state_ = state;
		auto engine = getEngine();
		if (engine)
			engine->reset();
	}
}

void StarbaseStructure::reset()
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

const Resistances& StarbaseStructure::getResistances()
{
	if (resistances_.armor.em < 0.0)
	{
		resistances_.armor.em		 = 1.0 - getAttribute(AttributeID::armorEmDamageResonance)->getValue();
		resistances_.armor.explosive = 1.0 - getAttribute(AttributeID::armorExplosiveDamageResonance)->getValue();
		resistances_.armor.kinetic   = 1.0 - getAttribute(AttributeID::armorKineticDamageResonance)->getValue();
		resistances_.armor.thermal   = 1.0 - getAttribute(AttributeID::armorThermalDamageResonance)->getValue();
		
		resistances_.shield.em		  = 1.0 - getAttribute(AttributeID::shieldEmDamageResonance)->getValue();
		resistances_.shield.explosive = 1.0 - getAttribute(AttributeID::shieldExplosiveDamageResonance)->getValue();
		resistances_.shield.kinetic   = 1.0 - getAttribute(AttributeID::shieldKineticDamageResonance)->getValue();
		resistances_.shield.thermal   = 1.0 - getAttribute(AttributeID::shieldThermalDamageResonance)->getValue();
		
		resistances_.hull.em		= 1.0 - getAttribute(AttributeID::emDamageResonance)->getValue();
		resistances_.hull.explosive = 1.0 - getAttribute(AttributeID::explosiveDamageResonance)->getValue();
		resistances_.hull.kinetic   = 1.0 - getAttribute(AttributeID::kineticDamageResonance)->getValue();
		resistances_.hull.thermal   = 1.0 - getAttribute(AttributeID::thermalDamageResonance)->getValue();
	}
	return resistances_;
}

const Tank& StarbaseStructure::getTank()
{
	if (tank_.armorRepair < 0.0)
	{
		tank_.armorRepair = fabs(getAttribute(AttributeID::armorDamage)->getValue());
		tank_.hullRepair = fabs(getAttribute(AttributeID::damage)->getValue());
		tank_.shieldRepair = fabs(getAttribute(AttributeID::shieldCharge)->getValue());
		tank_.passiveShield = getShieldRecharge();
	}
	return tank_;
}

const Tank& StarbaseStructure::getEffectiveTank()
{
	std::shared_ptr<ControlTower> controlTower = std::dynamic_pointer_cast<ControlTower>(getOwner());
	const DamagePattern damagePattern = controlTower->getDamagePattern();
	if (effectiveTank_.armorRepair < 0.0)
		effectiveTank_ = damagePattern.effectiveTank(getResistances(), getTank());
	return effectiveTank_;
}

const HitPoints& StarbaseStructure::getHitPoints()
{
	if (hitPoints_.armor < 0.0)
	{
		hitPoints_.armor = getAttribute(AttributeID::armorHP)->getValue();
		hitPoints_.hull = getAttribute(AttributeID::hp)->getValue();
		hitPoints_.shield = getAttribute(AttributeID::shieldCapacity)->getValue();
	}
	return hitPoints_;
}

const HitPoints& StarbaseStructure::getEffectiveHitPoints()
{
	std::shared_ptr<ControlTower> controlTower = std::dynamic_pointer_cast<ControlTower>(getOwner());
	const DamagePattern damagePattern = controlTower->getDamagePattern();
	if (effectiveHitPoints_.armor < 0.0)
		effectiveHitPoints_ = damagePattern.effectiveHitPoints(getResistances(), getHitPoints());
	return effectiveHitPoints_;
}

Float StarbaseStructure::getShieldRecharge()
{
	if (shieldRecharge_ < 0.0)
	{
		Float capacity = getAttribute(AttributeID::shieldCapacity)->getValue();
		Float rechargeRate = getAttribute(AttributeID::shieldRechargeRate)->getValue();
		shieldRecharge_ = 10.0 / (rechargeRate / 1000.0) * SHIELD_PEAK_RECHARGE * (1 - SHIELD_PEAK_RECHARGE) * capacity;
	}
	return shieldRecharge_;
}
