#include "Ship.h"
#include "Module.h"
#include "Drone.h"
#include "Character.h"
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

static const float SHIELD_PEAK_RECHARGE = sqrt(0.25);

struct Repairer
{
	enum Type
	{
		TYPE_ARMOR,
		TYPE_HULL,
		TYPE_SHIELD
	} type;
	
	Module* module;
	float hpPerSec;
	float capPerSec;
	float effectivity;
};

class RepairersEffectivityCompare : public std::binary_function<const Repairer*, const Repairer*, bool>
{
public:
	bool operator() (const Repairer* a, const Repairer* b)
	{
		return a->effectivity > b->effectivity;
	}
};


Ship::Ship(Engine* engine, TypeID typeID, Character* owner) : Item(engine, typeID, owner), capacitorSimulator_(this, false, 6 * 60 * 60 * 1000), heatSimulator_(this), disallowAssistance_(UNKNOWN), disallowOffensiveModifiers_(UNKNOWN)
{
	reset();
}

Ship::~Ship(void)
{
	if (projectedModules_.size() > 0)
	{
		std::list<Module*> projectedModulesCopy = projectedModules_;
		std::list<Module*>::iterator i, end = projectedModulesCopy.end();
		for (i = projectedModulesCopy.begin(); i != end; i++)
			(*i)->clearTarget();
	}
	if (projectedDrones_.size() > 0)
	{
		std::list<Drone*> projectedDronesCopy = projectedDrones_;
		std::list<Drone*>::iterator i, end = projectedDronesCopy.end();
		for (i = projectedDronesCopy.begin(); i != end; i++)
			(*i)->clearTarget();
		
	}
}

boost::shared_ptr<Module> Ship::addModule(const boost::shared_ptr<Module>& module)
{
	if (canFit(module))
	{
		modules_.push_back(module);
		module->setOwner(this);

		module->addEffects(Effect::CATEGORY_GENERIC);
		if (module->canHaveState(Module::STATE_ACTIVE))
			module->setState(Module::STATE_ACTIVE);
		else if (module->canHaveState(Module::STATE_ONLINE))
			module->setState(Module::STATE_ONLINE);
		engine_->reset(this);
		return module;
	}
	else
		return boost::shared_ptr<Module>();
}

boost::shared_ptr<Module> Ship::addModule(TypeID typeID)
{
	return addModule(boost::shared_ptr<Module>(new Module(engine_, typeID, this)));
}

void Ship::removeModule(const boost::shared_ptr<Module>& module)
{
	module->setState(Module::STATE_OFFLINE);
	module->clearTarget();
	module->removeEffects(Effect::CATEGORY_GENERIC);

	modules_.remove(module);
	engine_->reset(this);
}

boost::shared_ptr<Drone> Ship::addDrone(const boost::shared_ptr<Drone>& drone)
{
	drones_.push_back(drone);
	drone->setOwner(this);
	
	drone->addEffects(Effect::CATEGORY_GENERIC);
	drone->addEffects(Effect::CATEGORY_TARGET);
	engine_->reset(this);

	return drone;
}

boost::shared_ptr<Drone> Ship::addDrone(TypeID typeID)
{
	return addDrone(boost::shared_ptr<Drone>(new Drone(engine_, typeID, this)));
	
}

void Ship::removeDrone(const boost::shared_ptr<Drone>& drone)
{
	drone->removeEffects(Effect::CATEGORY_TARGET);
	drone->removeEffects(Effect::CATEGORY_GENERIC);
	
	drones_.remove(drone);
	engine_->reset(this);
}


const ModulesList& Ship::getModules()
{
	return modules_;
}

void Ship::getModules(Module::Slot slot, std::insert_iterator<ModulesList> outIterator)
{
	ModulesList::iterator i, end = modules_.end();
	for (i = modules_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			*outIterator++ = *i;
}

const DronesList& Ship::getDrones()
{
	return drones_;
}

const ProjectedModulesList& Ship::getProjectedModules()
{
	return projectedModules_;
}

const ProjectedDronesList& Ship::getProjectedDrones()
{
	return projectedDrones_;
}

bool Ship::canFit(const boost::shared_ptr<Module>& module)
{
	if (getFreeSlots(module->getSlot()) == 0)
		return false;
	
	Module::Hardpoint hardpoint = module->getHardpoint();
	if (hardpoint != Module::HARDPOINT_NONE && getFreeHardpoints(hardpoint) == 0)
		return false;
	
	std::vector<int> fitsOn;
	fitsOn.reserve(5);
	if (module->hasAttribute(FITS_TO_SHIP_TYPE_ATTRIBUTE_ID))
		fitsOn.push_back(static_cast<int>(module->getAttribute(FITS_TO_SHIP_TYPE_ATTRIBUTE_ID)->getValue()));

	for (TypeID i = CAN_FIT_SHIP_TYPE1_ATTRIBUTE_ID; i <= CAN_FIT_SHIP_TYPE4_ATTRIBUTE_ID; i++)
		if (module->hasAttribute(i))
			fitsOn.push_back(static_cast<int>(module->getAttribute(i)->getValue()));
	
	if (fitsOn.size() > 0 && std::find(fitsOn.begin(), fitsOn.end(), typeID_) == fitsOn.end())
		return false;
	
	fitsOn.clear();
	for (TypeID i = CAN_FIT_SHIP_GROUP1_ATTRIBUTE_ID; i <= CAN_FIT_SHIP_GROUP4_ATTRIBUTE_ID; i++)
		if (module->hasAttribute(i))
			fitsOn.push_back(static_cast<int>(module->getAttribute(i)->getValue()));

	if (fitsOn.size() > 0 && std::find(fitsOn.begin(), fitsOn.end(), groupID_) == fitsOn.end())
		return false;

	switch (module->getSlot())
	{
		case Module::SLOT_SUBSYSTEM:
		{
			int subsystemSlot = static_cast<int>(module->getAttribute(SUBSYSTEM_SLOT_ATTRIBUTE_ID)->getValue());
			ModulesList::iterator i, end = modules_.end();
			for (i = modules_.begin(); i != end; i++)
				if ((*i)->getSlot() == Module::SLOT_SUBSYSTEM && static_cast<int>((*i)->getAttribute(SUBSYSTEM_SLOT_ATTRIBUTE_ID)->getValue()) == subsystemSlot)
					return false;
			break;
		}
		case Module::SLOT_RIG:
		{
			if (module->getAttribute(RIG_SIZE_ATTRIBUTE_ID)->getValue() < getAttribute(RIG_SIZE_ATTRIBUTE_ID)->getValue())
				return false;
			break;
		}
		default:
			break;
	}
	
	if (module->hasAttribute(MAX_GROUP_FITTED_ATTRIBUTE_ID))
	{
		int maxGroupFitted = static_cast<int>(module->getAttribute(MAX_GROUP_FITTED_ATTRIBUTE_ID)->getValue()) - 1;
		TypeID groupID = module->getGroupID();
		ModulesList::iterator i, end = modules_.end();
		for (i = modules_.begin(); i != end; i++)
			if ((*i)->getGroupID() == groupID)
			{
				maxGroupFitted--;
				if (maxGroupFitted < 0)
					return false;
			}
	}
	
	return true;
}

bool Ship::isDisallowedAssistance()
{
	if (disallowAssistance_ == UNKNOWN)
	{
		if (hasAttribute(DISALLOW_ASSISTANCE_ATTRIBUTE_ID) && getAttribute(DISALLOW_ASSISTANCE_ATTRIBUTE_ID)->getValue() != 0)
			disallowAssistance_ = DISALLOWED;
		else
		{
			disallowAssistance_ = ALLOWED;
			ModulesList::iterator i, end = modules_.end();
			for (i = modules_.begin(); i != end; i++)
			{
				if ((*i)->getState() >= Module::STATE_ACTIVE &&
					(*i)->hasAttribute(DISALLOW_ASSISTANCE_ATTRIBUTE_ID) &&
					(*i)->getAttribute(DISALLOW_ASSISTANCE_ATTRIBUTE_ID)->getValue() != 0)
				{
					if ((*i)->getGroupID() == WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID && (*i)->getCharge() != NULL)
						continue;
					disallowAssistance_ = DISALLOWED;
					break;
				}
			}
		}
	}
	return disallowAssistance_ == DISALLOWED;
}

bool Ship::isDisallowedOffensiveModifiers()
{
	if (disallowOffensiveModifiers_ == UNKNOWN)
	{
		if (hasAttribute(DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID) && getAttribute(DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID)->getValue() != 0)
			disallowOffensiveModifiers_ = DISALLOWED;
		else
		{
			disallowOffensiveModifiers_ = ALLOWED;
			ModulesList::iterator i, end = modules_.end();
			for (i = modules_.begin(); i != end; i++)
			{
				if ((*i)->getState() >= Module::STATE_ACTIVE &&
					(*i)->hasAttribute(DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID) &&
					(*i)->getAttribute(DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID)->getValue() != 0)
				{
					disallowOffensiveModifiers_ = DISALLOWED;
					break;
				}
			}
		}
	}
	return disallowOffensiveModifiers_ == DISALLOWED;
}

boost::shared_ptr<Environment> Ship::getEnvironment()
{
	boost::shared_ptr<Environment> environment(new Environment());
	(*environment)["Self"] = this;
	(*environment)["Ship"] = this;
	Item* character = getOwner();
	Item* gang = character != NULL ? character->getOwner() : NULL;
	
	if (character != NULL)
		(*environment)["Char"] = character;
	if (gang != NULL)
		(*environment)["Gang"] = gang;
	if (engine_->getArea() != NULL)
		(*environment)["Area"] = engine_->getArea().get();
	return environment;
}

void Ship::reset()
{
	Item::reset();
	
	ModulesList::iterator i, end = modules_.end();
	for (i = modules_.begin(); i != end; i++)
		(*i)->reset();
	
	DronesList::iterator j, endj = drones_.end();
	for (j = drones_.begin(); j != endj; j++)
		(*j)->reset();
	
	capacitorSimulator_.reset();
	heatSimulator_.reset();
	disallowAssistance_ = disallowOffensiveModifiers_ = UNKNOWN;
	
	resistances_.armor.em = resistances_.armor.explosive = resistances_.armor.thermal = resistances_.armor.kinetic = -1;
	resistances_.hull = resistances_.shield = resistances_.armor;
	
	tank_.armorRepair = tank_.hullRepair = tank_.shieldRepair = tank_.passiveShield = -1.0;
	effectiveTank_ = sustainableTank_ = effectiveSustainableTank_ = tank_;
	
	hitPoints_.armor = hitPoints_.hull = hitPoints_.shield = -1.0;
	effectiveHitPoints_ = hitPoints_;
	
	shieldRecharge_ = -1;
	
	weaponDps_ = weaponVolley_ = droneDps_ = droneVolley_ = -1;
}

void Ship::addEffects(Effect::Category category)
{
	Item::addEffects(category);
	if (category == Effect::CATEGORY_GENERIC)
	{
		ModulesList::iterator i, end = modules_.end();
		for (i = modules_.begin(); i != end; i++)
		{
			(*i)->addEffects(Effect::CATEGORY_GENERIC);
		}
		boost::shared_ptr<Area> area = engine_->getArea();
		if (area != NULL)
			area->addEffectsToShip(this);
		
		DronesList::iterator j, endj = drones_.end();
		for (j = drones_.begin(); j != endj; j++)
			(*j)->addEffects(Effect::CATEGORY_GENERIC);
	}
}

void Ship::removeEffects(Effect::Category category)
{
	Item::removeEffects(category);
	if (category == Effect::CATEGORY_GENERIC)
	{
		ModulesList::iterator i, end = modules_.end();
		for (i = modules_.begin(); i != end; i++)
			(*i)->removeEffects(Effect::CATEGORY_GENERIC);
		boost::shared_ptr<Area> area = engine_->getArea();
		if (area != NULL)
			area->removeEffectsFromShip(this);
		
		DronesList::iterator j, endj = drones_.end();
		for (j = drones_.begin(); j != endj; j++)
			(*j)->removeEffects(Effect::CATEGORY_GENERIC);
	}
}

void Ship::addLocationGroupModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::addLocationGroupModifier(modifier);
	if (modifier->getAttributeID() == ACTIVATION_BLOCKED_ATTRIBUTE_ID)
		updateActiveStatus();
}

void Ship::addLocationRequiredSkillModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::addLocationRequiredSkillModifier(modifier);
	if (modifier->getAttributeID() == ACTIVATION_BLOCKED_ATTRIBUTE_ID)
		updateActiveStatus();
}

void Ship::addProjectedModule(Module* module)
{
	if (std::find(projectedModules_.begin(), projectedModules_.end(), module) == projectedModules_.end())
	{
		projectedModules_.push_back(module);
		engine_->reset(this);
	}
}

void Ship::removeProjectedModule(Module* module)
{
	projectedModules_.remove(module);
	engine_->reset(this);
}

void Ship::addProjectedDrone(Drone* drone)
{
	if (std::find(projectedDrones_.begin(), projectedDrones_.end(), drone) == projectedDrones_.end())
	{
		projectedDrones_.push_back(drone);
		engine_->reset(this);
	}
}

void Ship::removeProjectedDrone(Drone* drone)
{
	projectedDrones_.remove(drone);
	engine_->reset(this);
}

const CapacitorSimulator& Ship::getCapacitorSimulator()
{
	return capacitorSimulator_;
}

const HeatSimulator& Ship::getHeatSimulator()
{
	return heatSimulator_;
}

const DamagePattern& Ship::getDamagePattern()
{
	return damagePattern_;
}

void Ship::setDamagePattern(const DamagePattern& damagePattern)
{
	damagePattern_ = damagePattern;
	engine_->reset(this);
}

//Calculations

int Ship::getNumberOfSlots(Module::Slot slot)
{
	switch (slot)
	{
		case Module::SLOT_HI:
			return static_cast<int>(getAttribute(HI_SLOTS_ATTRIBUTE_ID)->getValue());
		case Module::SLOT_MED:
			return static_cast<int>(getAttribute(MED_SLOTS_ATTRIBUTE_ID)->getValue());
		case Module::SLOT_LOW:
			return static_cast<int>(getAttribute(LOW_SLOTS_ATTRIBUTE_ID)->getValue());
		case Module::SLOT_RIG:
			return static_cast<int>(getAttribute(RIG_SLOTS_ATTRIBUTE_ID)->getValue());
		case Module::SLOT_SUBSYSTEM:
			return static_cast<int>(getAttribute(MAX_SUBSYSTEMS_SLOTS_ATTRIBUTE_ID)->getValue());
		default:
			return 0;
			break;
	}
}

int Ship::getFreeSlots(Module::Slot slot)
{
	return getNumberOfSlots(slot) - getUsedSlots(slot);
}

int Ship::getUsedSlots(Module::Slot slot)
{
	int n = 0;
	ModulesList::iterator i, end = modules_.end();
	for (i = modules_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			n++;
	return n;
}

int Ship::getNumberOfHardpoints(Module::Hardpoint hardpoint)
{
	return getFreeHardpoints(hardpoint) + getUsedHardpoints(hardpoint);
}

int Ship::getFreeHardpoints(Module::Hardpoint hardpoint)
{
	switch (hardpoint)
	{
		case Module::HARDPOINT_LAUNCHER:
			return static_cast<int>(getAttribute(LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID)->getValue());
		case Module::HARDPOINT_TURRET:
			return static_cast<int>(getAttribute(TURRET_SLOTS_LEFT_ATTRIBUTE_ID)->getValue());
		default:
			return 0;
	}
}

int Ship::getUsedHardpoints(Module::Hardpoint hardpoint)
{
	int n = 0;
	ModulesList::iterator i, end = modules_.end();
	for (i = modules_.begin(); i != end; i++)
		if ((*i)->getHardpoint() == hardpoint)
			n++;
	return n;
}

float Ship::getCalibrationUsed()
{
	ModulesList::iterator i, end = modules_.end();
	float calibration = 0;
	for (i = modules_.begin(); i != end; i++)
		if ((*i)->getSlot() == Module::SLOT_RIG)
			calibration += (*i)->getAttribute(UPGRADE_COST_ATTRIBUTE_ID)->getValue();
	return calibration;
}

float Ship::getTotalCalibration()
{
	return getAttribute(UPGRADE_CAPACITY_ATTRIBUTE_ID)->getValue();
}

float Ship::getPowerGridUsed()
{
	return getAttribute(POWER_LOAD_ATTRIBUTE_ID)->getValue();
}

float Ship::getTotalPowerGrid()
{
	return getAttribute(POWER_OUTPUT_ATTRIBUTE_ID)->getValue();
}

float Ship::getCpuUsed()
{
	return getAttribute(CPU_LOAD_ATTRIBUTE_ID)->getValue();
}

float Ship::getTotalCpu()
{
	return getAttribute(CPU_OUTPUT_ATTRIBUTE_ID)->getValue();
}

float Ship::getDroneBandwidthUsed()
{
	DronesList::iterator i, end = drones_.end();
	float bandwidth = 0;
	for (i = drones_.begin(); i != end; i++)
		if ((*i)->isActive())
			bandwidth += (*i)->getAttribute(DRONE_BANDWIDTH_USED_ATTRIBUTE_ID)->getValue();
	return bandwidth;
}

float Ship::getTotalDroneBandwidth()
{
	return getAttribute(DRONE_BANDWIDTH_ATTRIBUTE_ID)->getValue();
}

float Ship::getDroneBayUsed()
{
	DronesList::iterator i, end = drones_.end();
	float volume = 0;
	for (i = drones_.begin(); i != end; i++)
		volume += (*i)->getAttribute(VOLUME_ATTRIBUTE_ID)->getValue();
	return volume;
}

float Ship::getTotalDroneBay()
{
	return getAttribute(DRONE_CAPACITY_ATTRIBUTE_ID)->getValue();
}

//Capacitor

float Ship::getCapCapacity()
{
	return getAttribute(CAPACITOR_CAPACITY_ATTRIBUTE_ID)->getValue();
}

bool Ship::isCapStable()
{
	return capacitorSimulator_.isCapStable();
}

float Ship::getCapLastsTime()
{
	return capacitorSimulator_.getCapLastsTime();
}

float Ship::getCapStableLevel()
{
	return capacitorSimulator_.getCapStableLevel();
}

float Ship::getCapUsed()
{
	return capacitorSimulator_.getCapUsed();
}

float Ship::getCapRecharge()
{
	return capacitorSimulator_.getCapRecharge();
}

//Tank

const Resistances& Ship::getResistances()
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

const Tank& Ship::getTank()
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

const Tank& Ship::getEffectiveTank()
{
	if (effectiveTank_.armorRepair < 0.0)
		effectiveTank_ = damagePattern_.effectiveTank(getResistances(), getTank());
	return effectiveTank_;
}

const Tank& Ship::getSustainableTank()
{
	if (sustainableTank_.armorRepair < 0.0)
	{
		if (isCapStable())
			sustainableTank_ = getTank();
		else
		{
			Item* currentCharacter = getOwner();

			sustainableTank_ = getTank();
			
			std::list<Repairer*> repairers;
			float capUsed = getCapUsed();
			
			TypeID attributes[] = {ARMOR_DAMAGE_ATTRIBUTE_ID, DAMAGE_ATTRIBUTE_ID, SHIELD_CHARGE_ATTRIBUTE_ID};
			Repairer::Type types[] = {Repairer::TYPE_ARMOR, Repairer::TYPE_HULL, Repairer::TYPE_SHIELD};
			float* layers[] = {&sustainableTank_.armorRepair, &sustainableTank_.hullRepair, &sustainableTank_.shieldRepair};
			
			for (int i = 0; i < 3; i++)
			{
				ModifiersList modifiers;
				getModifiers(getAttribute(attributes[i]).get(), std::inserter(modifiers, modifiers.begin()));
				ModifiersList::iterator j, end = modifiers.end();
				for (j = modifiers.begin(); j != end; j++)
				{
					Modifier::Association association = (*j)->getAssociation();
					if (association == Modifier::ASSOCIATION_ADD_RATE || Modifier::ASSOCIATION_SUB_RATE)
					{
						Item* character = (*j)->getCharacter();
						bool projected = character != NULL && character != currentCharacter;
						
						Item* item = (*j)->getModifier()->getOwner();
						if (!projected && item->getCategoryID() == MODULE_CATEGORY_ID)
						{
							Module* module = dynamic_cast<Module*>(item);
							assert(module);
							
							Repairer* repairer = new Repairer;
							repairer->type = types[i];
							repairer->hpPerSec = (*j)->getValue();
							repairer->capPerSec = module->getCapUse();
							repairer->effectivity = repairer->hpPerSec / repairer->capPerSec;
							*layers[i] -= repairer->hpPerSec;
							capUsed -= repairer->capPerSec;
							repairers.push_back(repairer);
						}
					}
				}
			}
			repairers.sort(RepairersEffectivityCompare());
			
			float totalPeakRecharge = getCapRecharge();

			std::list<Repairer*>::iterator i, end = repairers.end();
			for (i = repairers.begin(); i != end; i++)
			{
				Repairer* repairer = *i;
				if (capUsed > totalPeakRecharge)
					break;

				if (repairer->capPerSec > 0 && repairer->hpPerSec > 0) {
					float sustainability = std::min(float(1.0), (totalPeakRecharge - capUsed) / repairer->capPerSec);
					
					float amount = sustainability * repairer->hpPerSec;
					if (repairer->type == Repairer::TYPE_ARMOR)
						sustainableTank_.armorRepair += amount;
					else if (repairer->type == Repairer::TYPE_HULL)
						sustainableTank_.hullRepair += amount;
					else if (repairer->type == Repairer::TYPE_SHIELD)
						sustainableTank_.shieldRepair += amount;
					capUsed += repairer->capPerSec;
				}
			}
		}
	}
	return sustainableTank_;
}

const Tank& Ship::getEffectiveSustainableTank()
{
	if (effectiveSustainableTank_.armorRepair < 0.0)
		effectiveSustainableTank_ = damagePattern_.effectiveTank(getResistances(), getSustainableTank());
	return effectiveSustainableTank_;
}

const HitPoints& Ship::getHitPoints()
{
	if (hitPoints_.armor < 0.0)
	{
		hitPoints_.armor = getAttribute(ARMOR_HP_ATTRIBUTE_ID)->getValue();
		hitPoints_.hull = getAttribute(HP_ATTRIBUTE_ID)->getValue();
		hitPoints_.shield = getAttribute(SHIELD_CAPACITY_ATTRIBUTE_ID)->getValue();
	}
	return hitPoints_;
}

const HitPoints& Ship::getEffectiveHitPoints()
{
	if (effectiveHitPoints_.armor < 0.0)
		effectiveHitPoints_ = damagePattern_.effectiveHitPoints(getResistances(), getHitPoints());
	return effectiveHitPoints_;
}

float Ship::getShieldRecharge()
{
	if (shieldRecharge_ < 0.0)
	{
		float capacity = getAttribute(SHIELD_CAPACITY_ATTRIBUTE_ID)->getValue();
		float rechargeRate = getAttribute(SHIELD_RECHARGE_RATE_ATTRIBUTE_ID)->getValue();
		shieldRecharge_ = 10.0 / (rechargeRate / 1000.0) * SHIELD_PEAK_RECHARGE * (1 - SHIELD_PEAK_RECHARGE) * capacity;
	}
	return shieldRecharge_;
}

//DPS

float Ship::getWeaponDps()
{
	if (weaponDps_ < 0)
		calculateDamageStats();
	return weaponDps_;
}

float Ship::getWeaponVolley()
{
	if (weaponVolley_ < 0)
		calculateDamageStats();
	return weaponVolley_;
}

float Ship::getDroneDps()
{
	if (droneDps_ < 0)
		calculateDamageStats();
	return droneDps_;
}

float Ship::getDroneVolley()
{
	if (droneVolley_ < 0)
		calculateDamageStats();
	return droneVolley_;
}

void Ship::calculateDamageStats()
{
	weaponDps_ = weaponVolley_ = 0;
	ModulesList::iterator i, end = modules_.end();
	for (i = modules_.begin(); i != end; i++)
	{
		weaponDps_ += (*i)->getDps();
		weaponVolley_ += (*i)->getVolley();
	}
	
	droneDps_ = droneVolley_ = 0;
	DronesList::iterator j, endj = drones_.end();
	for (j = drones_.begin(); j != endj; j++)
	{
		droneDps_ += (*j)->getDps();
		droneVolley_ += (*j)->getVolley();
	}
}

//mobility
float Ship::getAlignTime()
{
	float agility = getAttribute(AGILITY_ATTRIBUTE_ID)->getValue();
	float mass = getAttribute(MASS_ATTRIBUTE_ID)->getValue();
	return -log(0.25) * agility * mass / 1000000.0;
}

float Ship::getWarpSpeed()
{
	float base = getAttribute(BASE_WARP_SPEED_ATTRIBUTE_ID)->getValue();
	float multiplier = getAttribute(WARP_SPEED_MULTIPLIER_ATTRIBUTE_ID)->getValue();
	if (base == 0.0)
		base = 1.0;
	if (multiplier == 0.0)
		multiplier = 1.0;
	return 3 * base * multiplier;
}

float Ship::getMaxWarpDistance()
{
	float capacity = getAttribute(CAPACITOR_CAPACITY_ATTRIBUTE_ID)->getValue();
	float mass = getAttribute(MASS_ATTRIBUTE_ID)->getValue();
	float warpCapNeed = getAttribute(WARP_CAPACITOR_NEED_ATTRIBUTE_ID)->getValue();
	return capacity / (mass * warpCapNeed);
}

float Ship::getVelocity()
{
	return getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue();
}

float Ship::getSignatureRadius()
{
	return getAttribute(SIGNATURE_RADIUS_ATTRIBUTE_ID)->getValue();
}

//targeting
int Ship::getMaxTargets()
{
	int maxTargetsShip = static_cast<int>(getAttribute(MAX_LOCKED_TARGETS_ATTRIBUTE_ID)->getValue());
	Item* character = getOwner();
	if (character)
	{
		int maxTargetsChar = static_cast<int>(character->getAttribute(MAX_LOCKED_TARGETS_ATTRIBUTE_ID)->getValue());
		return std::min(maxTargetsShip, maxTargetsChar);
	}
	else
		return maxTargetsShip;
}

float Ship::getMaxTargetRange()
{
	return std::min(getAttribute(MAX_TARGET_RANGE_ATTRIBUTE_ID)->getValue(), float(250000.0));
}

float Ship::getScanStrength()
{
	float maxStrength = -1;
	TypeID attributes[] = {SCAN_RADAR_STRENGTH_ATTRIBUTE_ID, SCAN_LADAR_STRENGTH_ATTRIBUTE_ID, SCAN_MAGNETOMETRIC_STRENGTH_ATTRIBUTE_ID, SCAN_GRAVIMETRIC_STRENGTH_ATTRIBUTE_ID};
	for (int i = 0; i < 4; i++)
	{
		float strength = getAttribute(attributes[i])->getValue();
		if (strength > maxStrength)
		{
			maxStrength = strength;
		}
	}
	return maxStrength;
}

Ship::ScanType Ship::getScanType()
{
	float maxStrength = -1;
	TypeID attributes[] = {SCAN_RADAR_STRENGTH_ATTRIBUTE_ID, SCAN_LADAR_STRENGTH_ATTRIBUTE_ID, SCAN_MAGNETOMETRIC_STRENGTH_ATTRIBUTE_ID, SCAN_GRAVIMETRIC_STRENGTH_ATTRIBUTE_ID};
	ScanType types[] = {SCAN_TYPE_RADAR, SCAN_TYPE_LADAR, SCAN_TYPE_MAGNETOMETRIC, SCAN_TYPE_GRAVIMETRIC};
	ScanType scanType = SCAN_TYPE_MULTISPECTRAL;
	for (int i = 0; i < 4; i++)
	{
		float strength = getAttribute(attributes[i])->getValue();
		if (strength > maxStrength)
		{
			maxStrength = strength;
			scanType = types[i];
		}
		else if (strength == maxStrength)
			scanType = SCAN_TYPE_MULTISPECTRAL;
	}
	return scanType;
}

float Ship::getScanResolution()
{
	return getAttribute(SCAN_RESOLUTION_ATTRIBUTE_ID)->getValue();
}

float Ship::getProbeSize()
{
	float signatureRadius = getSignatureRadius();
	float sensorStrength = getScanStrength();
	return sensorStrength > 0.0 ? signatureRadius / sensorStrength : 0.0;
}

//Drones
int Ship::getMaxActiveDrones()
{
	return static_cast<int>(getOwner()->getAttribute(MAX_ACTIVE_DRONES_ATTRIBUTE_ID)->getValue());
}

int Ship::getActiveDrones()
{
	DronesList::iterator i, end = drones_.end();
	int n = 0;
	for (i = drones_.begin(); i != end; i++)
		if ((*i)->isActive())
			n++;
	return n;
}


//Other

void Ship::updateActiveStatus()
{
	ModulesList::iterator i, end = modules_.end();
	for (i = modules_.begin(); i != end; i++)
	{
		Module::State state = (*i)->getState();
		if (state >= Module::STATE_ACTIVE && !(*i)->canHaveState(state))
			(*i)->setState(Module::STATE_ONLINE);
	}
}

void Ship::updateHeatDamage()
{
	heatSimulator_.simulate();
}

#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Ship& ship)
{
	os << "{\"typeName\":\"" << ship.getTypeName() << "\", \"typeID\":\"" << ship.typeID_ << "\", \"groupID\":\"" << ship.groupID_ << "\", \"attributes\":[";
	
	if (ship.attributes_.size() > 0)
	{
		AttributesMap::const_iterator i, end = ship.attributes_.end();
		bool isFirst = true;
		for (i = ship.attributes_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i->second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (ship.effects_.size() > 0)
	{
		EffectsList::const_iterator i, end = ship.effects_.end();
		bool isFirst = true;
		for (i = ship.effects_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}

	os << "], \"modules\":[";
	
	if (ship.modules_.size() > 0)
	{
		ModulesList::const_iterator i, end = ship.modules_.end();
		bool isFirst = true;
		for (i = ship.modules_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}

	os << "], \"itemModifiers\":[";
	
	if (ship.itemModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = ship.itemModifiers_.end();
		bool isFirst = true;
		for (i = ship.itemModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (ship.locationModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = ship.locationModifiers_.end();
		bool isFirst = true;
		for (i = ship.locationModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (ship.locationGroupModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = ship.locationGroupModifiers_.end();
		bool isFirst = true;
		for (i = ship.locationGroupModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>((*i).get());
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (ship.locationRequiredSkillModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = ship.locationRequiredSkillModifiers_.end();
		bool isFirst = true;
		for (i = ship.locationRequiredSkillModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>((*i).get());
		}
	}

	os << "]}";
	return os;
}

#endif