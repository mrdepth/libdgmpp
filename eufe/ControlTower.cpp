#include "ControlTower.h"
#include "Structure.h"
#include "Attribute.h"
#include "Effect.h"
#include "Engine.h"
#include "Area.h"
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include <math.h>
#include <algorithm>

using namespace eufe;

static const float SHIELD_PEAK_RECHARGE = sqrtf(0.25f);

ControlTower::ControlTower(Engine* engine, TypeID typeID) : Item(engine, typeID, NULL)
{
	reset();
}

ControlTower::~ControlTower(void)
{
}

Structure* ControlTower::addStructure(Structure* structure)
{
	if (canFit(structure))
	{
		structures_.push_back(structure);
		structure->setOwner(this);
		
		structure->addEffects(Effect::CATEGORY_GENERIC);
		if (structure->canHaveState(Structure::STATE_ACTIVE))
			structure->setState(Structure::STATE_ACTIVE);
		else if (structure->canHaveState(Structure::STATE_ONLINE))
			structure->setState(Structure::STATE_ONLINE);
		engine_->reset(this);
		return structure;
	}
	else
		return NULL;
}

Structure* ControlTower::addStructure(TypeID typeID)
{
	try
	{
		return addStructure(new Structure(engine_, typeID, this));
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

void ControlTower::removeStructure(Structure* structure)
{
	structure->setState(Structure::STATE_OFFLINE);
	structure->removeEffects(Effect::CATEGORY_GENERIC);
	
	structures_.remove(structure);
	delete structure;
	engine_->reset(this);
}

const StructuresList& ControlTower::getStructures()
{
	return structures_;
}

bool ControlTower::canFit(Structure* structure)
{
	if (structure->getSlot() != Structure::SLOT_STRUCTURE)
		return false;
	if (structure->getCategoryID() == STRUCTURE_CATEGORY_ID && structure->getGroupID() != CONTROL_TOWER_GROUP_ID)
		return true;
	else
		return false;
}

Environment ControlTower::getEnvironment()
{
	Environment environment;
	environment["Self"] = this;
	environment["Ship"] = this;
	
	if (engine_->getArea())
		environment["Area"] = engine_->getArea();
	return environment;
}

void ControlTower::reset()
{
	Item::reset();
	
	StructuresList::iterator i, end = structures_.end();
	for (i = structures_.begin(); i != end; i++)
		(*i)->reset();
	
	resistances_.armor.em = resistances_.armor.explosive = resistances_.armor.thermal = resistances_.armor.kinetic = -1;
	resistances_.hull = resistances_.shield = resistances_.armor;
	
	tank_.armorRepair = tank_.hullRepair = tank_.shieldRepair = tank_.passiveShield = -1.0;
	effectiveTank_ = tank_;
	
	hitPoints_.armor = hitPoints_.hull = hitPoints_.shield = -1.0;
	effectiveHitPoints_ = hitPoints_;
	
	shieldRecharge_ = -1;
	
	weaponDps_ = weaponVolley_ = -1;
	
	cpuUsed_ = powerGridUsed_ = -1;
}

void ControlTower::addEffects(Effect::Category category)
{
	Item::addEffects(category);
	if (category == Effect::CATEGORY_GENERIC)
	{
		StructuresList::iterator i, end = structures_.end();
		for (i = structures_.begin(); i != end; i++)
			(*i)->addEffects(Effect::CATEGORY_GENERIC);
//		std::shared_ptr<Area> area = engine_->getArea();
//		if (area != NULL)
//			area->addEffectsToShip(this);
	}
}

void ControlTower::removeEffects(Effect::Category category)
{
	Item::removeEffects(category);
	if (category == Effect::CATEGORY_GENERIC)
	{
		StructuresList::iterator i, end = structures_.end();
		for (i = structures_.begin(); i != end; i++)
			(*i)->removeEffects(Effect::CATEGORY_GENERIC);
//		std::shared_ptr<Area> area = engine_->getArea();
//		if (area != NULL)
//			area->removeEffectsFromShip(this);
	}
}

const DamagePattern& ControlTower::getDamagePattern()
{
	return damagePattern_;
}

void ControlTower::setDamagePattern(const DamagePattern& damagePattern)
{
	damagePattern_ = damagePattern;
	engine_->reset(this);
}

//Calculations

float ControlTower::getPowerGridUsed()
{
	if (powerGridUsed_ < 0)
	{
		powerGridUsed_ = 0;
		StructuresList::iterator i, end = structures_.end();
		for (i = structures_.begin(); i != end; i++)
		{
			if ((*i)->getState() >= Module::STATE_ONLINE)
				powerGridUsed_ += (*i)->getAttribute(POWER_ATTRIBUTE_ID)->getValue();
		}
	}
	return powerGridUsed_;
}

float ControlTower::getTotalPowerGrid()
{
	return getAttribute(POWER_OUTPUT_ATTRIBUTE_ID)->getValue();
}

float ControlTower::getCpuUsed()
{
	if (cpuUsed_ < 0)
	{
		cpuUsed_ = 0;
		StructuresList::iterator i, end = structures_.end();
		for (i = structures_.begin(); i != end; i++)
		{
			if ((*i)->getState() >= Module::STATE_ONLINE)
				cpuUsed_ += (*i)->getAttribute(CPU_ATTRIBUTE_ID)->getValue();
		}
	}
	return cpuUsed_;
}

float ControlTower::getTotalCpu()
{
	return getAttribute(CPU_OUTPUT_ATTRIBUTE_ID)->getValue();
}

//Tank 8-033-3376391

const Resistances& ControlTower::getResistances()
{
	if (resistances_.armor.em < 0.0)
	{
		resistances_.armor.em		 = 1.0f - getAttribute(ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.armor.explosive = 1.0f - getAttribute(ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.armor.kinetic   = 1.0f - getAttribute(ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.armor.thermal   = 1.0f - getAttribute(ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		
		resistances_.shield.em		  = 1.0f - getAttribute(SHIELD_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.shield.explosive = 1.0f - getAttribute(SHIELD_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.shield.kinetic   = 1.0f - getAttribute(SHIELD_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.shield.thermal   = 1.0f - getAttribute(SHIELD_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		
		resistances_.hull.em		= 1.0f - getAttribute(HULL_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.hull.explosive = 1.0f - getAttribute(HULL_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.hull.kinetic   = 1.0f - getAttribute(HULL_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
		resistances_.hull.thermal   = 1.0f - getAttribute(HULL_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID)->getValue();
	}
	return resistances_;
}

const Tank& ControlTower::getTank()
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

const Tank& ControlTower::getEffectiveTank()
{
	if (effectiveTank_.armorRepair < 0.0)
		effectiveTank_ = damagePattern_.effectiveTank(getResistances(), getTank());
	return effectiveTank_;
}

const HitPoints& ControlTower::getHitPoints()
{
	if (hitPoints_.armor < 0.0)
	{
		hitPoints_.armor = getAttribute(ARMOR_HP_ATTRIBUTE_ID)->getValue();
		hitPoints_.hull = getAttribute(HP_ATTRIBUTE_ID)->getValue();
		hitPoints_.shield = getAttribute(SHIELD_CAPACITY_ATTRIBUTE_ID)->getValue();
	}
	return hitPoints_;
}

const HitPoints& ControlTower::getEffectiveHitPoints()
{
	if (effectiveHitPoints_.armor < 0.0)
		effectiveHitPoints_ = damagePattern_.effectiveHitPoints(getResistances(), getHitPoints());
	return effectiveHitPoints_;
}

float ControlTower::getShieldRecharge()
{
	if (shieldRecharge_ < 0.0)
	{
		float capacity = getAttribute(SHIELD_CAPACITY_ATTRIBUTE_ID)->getValue();
		float rechargeRate = getAttribute(SHIELD_RECHARGE_RATE_ATTRIBUTE_ID)->getValue();
		shieldRecharge_ = 10.0f / (rechargeRate / 1000.0f) * SHIELD_PEAK_RECHARGE * (1 - SHIELD_PEAK_RECHARGE) * capacity;
	}
	return shieldRecharge_;
}

//DPS

float ControlTower::getWeaponDps()
{
	if (weaponDps_ < 0)
		calculateDamageStats();
	return weaponDps_;
}

float ControlTower::getWeaponVolley()
{
	if (weaponVolley_ < 0)
		calculateDamageStats();
	return weaponVolley_;
}

void ControlTower::calculateDamageStats()
{
	weaponDps_ = weaponVolley_ = 0;
	StructuresList::iterator i, end = structures_.end();
	for (i = structures_.begin(); i != end; i++)
	{
		weaponDps_ += (*i)->getDps();
		weaponVolley_ += (*i)->getVolley();
	}
}

#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::ControlTower& controlTower)
{
	os << "{\"typeName\":\"" << controlTower.getTypeName() << "\", \"typeID\":\"" << controlTower.typeID_ << "\", \"groupID\":\"" << controlTower.groupID_ << "\", \"attributes\":[";
	
	if (controlTower.attributes_.size() > 0)
	{
		AttributesMap::const_iterator i, end = controlTower.attributes_.end();
		bool isFirst = true;
		for (i = controlTower.attributes_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i->second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (controlTower.effects_.size() > 0)
	{
		EffectsList::const_iterator i, end = controlTower.effects_.end();
		bool isFirst = true;
		for (i = controlTower.effects_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"structures\":[";
	
	if (controlTower.structures_.size() > 0)
	{
		StructuresList::const_iterator i, end = controlTower.structures_.end();
		bool isFirst = true;
		for (i = controlTower.structures_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"itemModifiers\":[";
	
	if (controlTower.itemModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = controlTower.itemModifiers_.end();
		bool isFirst = true;
		for (i = controlTower.itemModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (controlTower.locationModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = controlTower.locationModifiers_.end();
		bool isFirst = true;
		for (i = controlTower.locationModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (controlTower.locationGroupModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = controlTower.locationGroupModifiers_.end();
		bool isFirst = true;
		for (i = controlTower.locationGroupModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>(*i);
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (controlTower.locationRequiredSkillModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = controlTower.locationRequiredSkillModifiers_.end();
		bool isFirst = true;
		for (i = controlTower.locationRequiredSkillModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>(*i);
		}
	}
	
	os << "]}";
	return os;
}

#endif