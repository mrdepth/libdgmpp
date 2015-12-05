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

ControlTower::ControlTower(std::shared_ptr<Engine> const& engine, TypeID typeID) : Item(engine, typeID, nullptr)
{
}

ControlTower::~ControlTower(void)
{
}

std::shared_ptr<Structure> ControlTower::addStructure(TypeID typeID)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Structure> structure = std::make_shared<Structure>(engine, typeID, shared_from_this());
		structures_.push_back(structure);
		
		structure->addEffects(Effect::CATEGORY_GENERIC);
		if (structure->canHaveState(Structure::STATE_ACTIVE))
			structure->setState(Structure::STATE_ACTIVE);
		else if (structure->canHaveState(Structure::STATE_ONLINE))
			structure->setState(Structure::STATE_ONLINE);
		engine->reset(shared_from_this());
		return structure;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void ControlTower::removeStructure(std::shared_ptr<Structure> const& structure)
{
	structure->setState(Structure::STATE_OFFLINE);
	structure->removeEffects(Effect::CATEGORY_GENERIC);
	
	structures_.remove(structure);
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

const StructuresList& ControlTower::getStructures()
{
	return structures_;
}

bool ControlTower::canFit(std::shared_ptr<Structure> const& structure)
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
	auto engine = getEngine();
	if (engine) {
		environment["Self"] = shared_from_this();
		environment["Ship"] = shared_from_this();
		std::shared_ptr<Area> area = engine->getArea();
		if (area)
			environment["Area"] = area;
	}

	return environment;
}

void ControlTower::reset()
{
	Item::reset();
	
	for (const auto& i: structures_)
		i->reset();
	
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
		for (const auto& i: structures_)
			i->addEffects(Effect::CATEGORY_GENERIC);
//		std::shared_ptr<Area> area = engine_->getArea();
//		if (area != nullptr)
//			area->addEffectsToShip(this);
	}
}

void ControlTower::removeEffects(Effect::Category category)
{
	Item::removeEffects(category);
	if (category == Effect::CATEGORY_GENERIC)
	{
		for (const auto& i: structures_)
			i->removeEffects(Effect::CATEGORY_GENERIC);
//		std::shared_ptr<Area> area = engine_->getArea();
//		if (area != nullptr)
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
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

//Calculations

float ControlTower::getPowerGridUsed()
{
	if (powerGridUsed_ < 0)
	{
		powerGridUsed_ = 0;
		for (const auto& i: structures_)
		{
			if (i->getState() >= Module::STATE_ONLINE)
				powerGridUsed_ += i->getAttribute(POWER_ATTRIBUTE_ID)->getValue();
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
		for (const auto& i: structures_)
		{
			if (i->getState() >= Module::STATE_ONLINE)
				cpuUsed_ += i->getAttribute(CPU_ATTRIBUTE_ID)->getValue();
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

DamageVector ControlTower::getWeaponDps()
{
	if (weaponDps_ < 0)
		calculateDamageStats();
	return weaponDps_;
}

DamageVector ControlTower::getWeaponVolley()
{
	if (weaponVolley_ < 0)
		calculateDamageStats();
	return weaponVolley_;
}

void ControlTower::calculateDamageStats()
{
	weaponDps_ = weaponVolley_ = 0;
	for (const auto& i: structures_)
	{
		weaponDps_ += i->getDps();
		weaponVolley_ += i->getVolley();
	}
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::ControlTower& controlTower)
{
	os << "{\"typeName\":\"" << controlTower.getTypeName() << "\", \"typeID\":\"" << controlTower.typeID_ << "\", \"groupID\":\"" << controlTower.groupID_ << "\", \"attributes\":[";
	
	if (controlTower.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: controlTower.attributes_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i.second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (controlTower.effects_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: controlTower.effects_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"structures\":[";
	
	if (controlTower.structures_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: controlTower.structures_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"itemModifiers\":[";
	
	if (controlTower.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: controlTower.itemModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (controlTower.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: controlTower.locationModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (controlTower.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: controlTower.locationGroupModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (controlTower.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: controlTower.locationRequiredSkillModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}
	
	os << "]}";
	return os;
}
