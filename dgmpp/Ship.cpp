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
#include <cmath>
#include <algorithm>
#include "Charge.h"
#include <cassert>

using namespace dgmpp;

static const Float SHIELD_PEAK_RECHARGE = sqrt(0.25);

struct Repairer
{
	enum Type
	{
		TYPE_ARMOR,
		TYPE_HULL,
		TYPE_SHIELD
	} type;
	
	Module* module;
	Float hpPerSec;
	Float capPerSec;
	Float effectivity;
};

class RepairersEffectivityCompare : public std::binary_function<const std::shared_ptr<Repairer>&, const std::shared_ptr<Repairer>&, bool>
{
public:
	bool operator() (const std::shared_ptr<Repairer>& a, const std::shared_ptr<Repairer>& b)
	{
		return a->effectivity > b->effectivity;
	}
};


Ship::Ship(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner) : Item(engine, typeID, owner), capacitorSimulator_(nullptr), heatSimulator_(nullptr), disallowAssistance_(UNKNOWN), disallowOffensiveModifiers_(UNKNOWN)
{
}

Ship::~Ship(void)
{
	for (const auto& i: getModules()) {
		i->clearTarget();
	}
	
	for (const auto& drone: drones_)
		drone->clearTarget();
	
	if (projectedModules_.size() > 0)
	{
		std::list<std::weak_ptr<Module>> projectedModulesCopy = projectedModules_;
		for (const auto& i: projectedModulesCopy) {
			auto module = i.lock();
			if (module)
				module->clearTarget();
		}
	}
	if (projectedDrones_.size() > 0)
	{
		std::list<std::weak_ptr<Drone>> projectedDronesCopy = projectedDrones_;
		for (const auto& i: projectedDronesCopy) {
			auto drone = i.lock();
			if (drone)
				drone->clearTarget();
		}
	}
}

std::shared_ptr<Module> Ship::addModule(TypeID typeID, bool forced, int socket)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Module> module = std::make_shared<Module>(engine, typeID, shared_from_this());
		bool isModule = false;
		for (auto categoryID: getSupportedModuleCategories())
			if (categoryID == module->getCategoryID()) {
				isModule = true;
				break;
			}
		
		if (isModule && (forced || canFit(module)))
		{
			auto& array = modules_[module->getSlot()];
			
			if (socket < 0)
				socket = static_cast<int>(std::find_if(array.begin(), array.end(), [&](std::shared_ptr<Module> const& module) { return module->isDummy(); }) - array.begin());
			
			if (socket >= array.size()) {
				array.push_back(module);
			}
			else if (!array[socket]->isDummy()) {
				array.insert(array.begin() + socket, module);
			}
			else {
				array[socket] = module;
			}

			module->addEffects(Effect::CATEGORY_GENERIC);
			if (module->canHaveState(Module::STATE_ACTIVE))
				module->setState(Module::STATE_ACTIVE);
			else if (module->canHaveState(Module::STATE_ONLINE))
				module->setState(Module::STATE_ONLINE);
			engine->reset();
			
			//updateEnabledStatus();
			return module;
		}
		else
			return nullptr;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

std::shared_ptr<Module> Ship::replaceModule(std::shared_ptr<Module> const& oldModule, TypeID typeID) {
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;
		
		//Module* newModule =  new Module(engine_, typeID, this);
		auto& array = modules_[oldModule->getSlot()];
		auto i = std::find(array.begin(), array.end(), oldModule);
		if (i == array.end())
			return nullptr;
		
		Module::State state = oldModule->getPreferredState();
		std::shared_ptr<Charge> charge = oldModule->getCharge();
		TypeID chargeTypeID = charge ? charge->getTypeID() : 0;
		std::shared_ptr<Ship> target = oldModule->getTarget();
		auto socket = static_cast<int>(i - array.begin());
		
		oldModule->setState(Module::STATE_OFFLINE);
		oldModule->clearTarget();
		oldModule->removeEffects(Effect::CATEGORY_GENERIC);
		
		if (array.size() > getNumberOfSlots(oldModule->getSlot())) {
			array.erase(i);
		}
		else {
			*i = Module::dummy(engine, shared_from_this(), oldModule->getSlot());
		}
			
		std::shared_ptr<Module> newModule = addModule(typeID, false, socket);
		if (newModule) {
			if (chargeTypeID)
				newModule->setCharge(chargeTypeID);
			if (target)
				newModule->setTarget();
			newModule->setPreferredState(state);
		}
		
		engine->reset();
		//updateEnabledStatus();
		return newModule;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

ModulesList Ship::addModules(const std::list<TypeID>& typeIDs)
{
	ModulesList modules;
	for (const auto& i: typeIDs)
	{
		std::shared_ptr<Module> module;
		try
		{
			module = addModule(i);
			modules.push_back(module);
		}
		catch(Item::UnknownTypeIDException)
		{
			module = nullptr;
		}
		
	}
	return modules;
}

void Ship::removeModule(std::shared_ptr<Module> const& module) {
	auto engine = getEngine();
	if (!engine)
		return;
	
	auto& array = modules_[module->getSlot()];
	auto i = std::find(array.begin(), array.end(), module);
	if (i != array.end()) {
		module->setState(Module::STATE_OFFLINE);
		module->clearTarget();
		module->removeEffects(Effect::CATEGORY_GENERIC);
		
		*i = Module::dummy(engine, shared_from_this(), module->getSlot());
		engine->reset();
	}
}

std::shared_ptr<Drone> Ship::addDrone(TypeID typeID, int squadronTag)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;
		
		if (squadronTag < 0) {
			int lastTag = 0;
			int lastSize = 0;
			int squadronSize = 0;
			for (const auto& drone: drones_) {
				if (drone->getTypeID() != typeID)
					continue;
				
				auto tag = drone->getSquadronTag();
				if (squadronSize == 0) {
					squadronSize = drone->getSquadronSize() ?: 5;
				}
				if (tag > lastTag) {
					lastTag = tag;
					lastSize = 1;
				}
				else if (tag == lastTag) {
					lastSize++;
				}
			}
			if (lastSize < (squadronSize ?: 5))
				squadronTag = lastTag;
			else
				squadronTag = lastTag + 1;
		}

		
		std::shared_ptr<Drone> drone = std::make_shared<Drone>(engine, typeID, squadronTag, shared_from_this());
		for (auto categoryID: getSupportedDroneCategories())
			if (categoryID == drone->getCategoryID()) {
				
				auto i = std::find_if(drones_.begin(), drones_.end(), [&](const std::shared_ptr<Drone>& drone) {
					return drone->getTypeID() == typeID && drone->getSquadronTag() == squadronTag;
				});
				if (i == drones_.end()) {
					auto squadron = drone->getSquadron();
					if (squadron == Drone::FIGHTER_SQUADRON_NONE) {
						drone->setActive(getDroneSquadronLimit(squadron) > getDroneSquadronUsed(squadron));
					}
					else {
						drone->setActive(getTotalFighterLaunchTubes() > getFighterLaunchTubesUsed() && getDroneSquadronLimit(squadron) > getDroneSquadronUsed(squadron));
					}
				}
				else {
					drone->setActive((*i)->isActive());
				}
				
				drones_.push_back(drone);
				drone->addEffects(Effect::CATEGORY_GENERIC);
				drone->addEffects(Effect::CATEGORY_TARGET);
				engine->reset();
				
				return drone;
			}
		return nullptr;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void Ship::removeDrone(std::shared_ptr<Drone> const& drone)
{
	drone->removeEffects(Effect::CATEGORY_TARGET);
	drone->removeEffects(Effect::CATEGORY_GENERIC);
	
	//drones_.remove(drone);
	drones_.erase(std::find(drones_.begin(), drones_.end(), drone));
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

ModulesList Ship::getModules(bool includingDummies) {
	ModulesList list;
	for (const auto& i: modules_) {
		if (includingDummies)
			std::copy(i.second.begin(), i.second.end(), std::back_inserter(list));
		else
			std::copy_if(i.second.begin(), i.second.end(), std::back_inserter(list), [&](const std::shared_ptr<Module>& module) {return !module->isDummy(); });
	}
	return list;
}

ModulesList Ship::getModules(Module::Slot slot, bool includingDummies) {
	const auto& i = modules_[slot];
	
	if (includingDummies)
		return i;
	else {
		ModulesList list;
		std::copy_if(i.begin(), i.end(), std::back_inserter(list), [&](const std::shared_ptr<Module>& module) {return !module->isDummy(); });
		return list;
	}
}


const DronesList& Ship::getDrones()
{
	return drones_;
}

const std::list<std::weak_ptr<Module>>& Ship::getProjectedModules()
{
	std::remove_if(projectedModules_.begin(), projectedModules_.end(), [](std::weak_ptr<Module> module) {
		return module.lock() == nullptr;
	});
	return projectedModules_;
}

const std::list<std::weak_ptr<Drone>>& Ship::getProjectedDrones()
{
	std::remove_if(projectedDrones_.begin(), projectedDrones_.end(), [](std::weak_ptr<Drone> drone) {
		return drone.lock() == nullptr;
	});
	return projectedDrones_;
}

bool Ship::canFit(std::shared_ptr<Module> const& module)
{
	if (getFreeSlots(module->getSlot()) == 0)
		return false;
	
	Module::Hardpoint hardpoint = module->getHardpoint();
	if (hardpoint != Module::HARDPOINT_NONE && getFreeHardpoints(hardpoint) == 0)
		return false;
	
	std::vector<int> fitsOn;
	fitsOn.reserve(5);

	TypeID canFitToShipTypeAttribute[] = {
		FITS_TO_SHIP_TYPE_ATTRIBUTE_ID,
		CAN_FIT_SHIP_TYPE1_ATTRIBUTE_ID,
		CAN_FIT_SHIP_TYPE2_ATTRIBUTE_ID,
		CAN_FIT_SHIP_TYPE3_ATTRIBUTE_ID,
		CAN_FIT_SHIP_TYPE4_ATTRIBUTE_ID,
		CAN_FIT_SHIP_TYPE5_ATTRIBUTE_ID,
		CAN_FIT_SHIP_TYPE6_ATTRIBUTE_ID};

	for (auto attributeID: canFitToShipTypeAttribute) {
		if (module->hasAttribute(attributeID))
			fitsOn.push_back(static_cast<int>(module->getAttribute(attributeID)->getValue()));
		
	}

	int matchType = 1;
	if (fitsOn.size() > 0) {
		if (std::find(fitsOn.begin(), fitsOn.end(), typeID_) == fitsOn.end())
			matchType = -1;
		else
			matchType = 0;
	}
	
//	if (fitsOn.size() > 0 && std::find(fitsOn.begin(), fitsOn.end(), typeID_) == fitsOn.end())
//		return false;
	
	fitsOn.clear();
	TypeID canFitShipGroupAttribute[] = {
		CAN_FIT_SHIP_GROUP1_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP2_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP3_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP4_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP5_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP6_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP7_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP8_ATTRIBUTE_ID,
		CAN_FIT_SHIP_GROUP9_ATTRIBUTE_ID};

	for (auto attributeID: canFitShipGroupAttribute) {
		if (module->hasAttribute(attributeID))
			fitsOn.push_back(static_cast<int>(module->getAttribute(attributeID)->getValue()));
		
	}

	int matchGroup = 1;
	if (fitsOn.size() > 0) {
		if (std::find(fitsOn.begin(), fitsOn.end(), groupID_) == fitsOn.end())
			matchGroup = -1;
		else
			matchGroup = 0;
	}

//	if (fitsOn.size() > 0 && std::find(fitsOn.begin(), fitsOn.end(), groupID_) == fitsOn.end())
//		return false;
	
	if ((matchType == -1 && matchGroup == -1) || matchType * matchGroup < 0)
		return false;

	switch (module->getSlot())
	{
		case Module::SLOT_SUBSYSTEM:
		{
			int subsystemSlot = static_cast<int>(module->getAttribute(SUBSYSTEM_SLOT_ATTRIBUTE_ID)->getValue());
			for (const auto& i: getModules(Module::SLOT_SUBSYSTEM))
				if (!i->isDummy() && static_cast<int>(i->getAttribute(SUBSYSTEM_SLOT_ATTRIBUTE_ID)->getValue()) == subsystemSlot)
					return false;
			break;
		}
		case Module::SLOT_RIG:
		{
			if (static_cast<int>(module->getAttribute(RIG_SIZE_ATTRIBUTE_ID)->getValue()) != getRigSize())
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
		for (const auto& i: getModules()) {
			if (i->getGroupID() == groupID)
			{
				maxGroupFitted--;
				if (maxGroupFitted < 0)
					return false;
			}
		}
	}
	
	if (module->hasAttribute(MAX_TYPE_FITTED_ATTRIBUTE_ID)) {
		int maxTypeFitted = static_cast<int>(module->getAttribute(MAX_TYPE_FITTED_ATTRIBUTE_ID)->getValue()) - 1;
		TypeID typeID = module->getTypeID();
		for (const auto& i: getModules()) {
			if (i->getTypeID() == typeID)
			{
				maxTypeFitted--;
				if (maxTypeFitted < 0)
					return false;
			}
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
			for (const auto& i: getModules()) {
				if (i->getState() >= Module::STATE_ACTIVE &&
					i->hasAttribute(DISALLOW_ASSISTANCE_ATTRIBUTE_ID) &&
					i->getAttribute(DISALLOW_ASSISTANCE_ATTRIBUTE_ID)->getValue() != 0)
				{
					if (i->getGroupID() == WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID && i->getCharge())
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
			for (const auto& i: getModules()) {
				if (i->getState() >= Module::STATE_ACTIVE &&
					i->hasAttribute(DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID) &&
					i->getAttribute(DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID)->getValue() != 0)
				{
					disallowOffensiveModifiers_ = DISALLOWED;
					break;
				}
			}
		}
	}
	return disallowOffensiveModifiers_ == DISALLOWED;
}

void Ship::reset()
{
	Item::reset();
	for (const auto& i: modules_) {
		for (const auto& j: i.second) {
			j->reset();
		}
	}
	for (const auto& i: drones_)
		i->reset();
	
	getCapacitorSimulator()->reset();
	getHeatSimulator()->reset();
	disallowAssistance_ = disallowOffensiveModifiers_ = UNKNOWN;
	
	resistances_.armor.em = resistances_.armor.explosive = resistances_.armor.thermal = resistances_.armor.kinetic = -1;
	resistances_.hull = resistances_.shield = resistances_.armor;
	
	tank_.armorRepair = tank_.hullRepair = tank_.shieldRepair = tank_.passiveShield = -1.0;
	effectiveTank_ = sustainableTank_ = effectiveSustainableTank_ = tank_;
	
	hitPoints_.armor = hitPoints_.hull = hitPoints_.shield = -1.0;
	effectiveHitPoints_ = hitPoints_;
	
	shieldRecharge_ = -1;
	
	updateEnabledStatus();
	updateModulesState();
	updateModulesSockets();
}

std::vector<TypeID> Ship::getSupportedModuleCategories() const {
	return {MODULE_CATEGORY_ID, SUBSYSTEM_CATEGORY_ID};
}

std::vector<TypeID> Ship::getSupportedDroneCategories() const {
	return {DRONE_CATEGORY_ID, FIGHTER_CATEGORY_ID};
}


void Ship::addEffects(Effect::Category category)
{
	Item::addEffects(category);
	auto engine = getEngine();
	if (!engine)
		return;

	if (category == Effect::CATEGORY_GENERIC)
	{
		for (const auto& i: getModules()) {
			i->addEffects(Effect::CATEGORY_GENERIC);
		}
		for (const auto& i: drones_)
			i->addEffects(Effect::CATEGORY_GENERIC);

		std::shared_ptr<Area> area = engine->getArea();
		if (area)
			area->addEffectsToShip(shared_from_this());
	}
}

void Ship::removeEffects(Effect::Category category)
{
	Item::removeEffects(category);
	auto engine = getEngine();
	if (!engine)
		return;

	if (category == Effect::CATEGORY_GENERIC)
	{
		for (const auto& i: getModules()) {
			i->removeEffects(Effect::CATEGORY_GENERIC);
		}
		for (const auto& i: drones_)
			i->removeEffects(Effect::CATEGORY_GENERIC);

		std::shared_ptr<Area> area = engine->getArea();
		if (area)
			area->removeEffectsFromShip(shared_from_this());
	}
}

/*void Ship::addLocationGroupModifier(std::shared_ptr<Modifier> modifier)
{
	Item::addLocationGroupModifier(modifier);
	if (modifier->getAttributeID() == ACTIVATION_BLOCKED_ATTRIBUTE_ID)
		updateActiveStatus();
}

void Ship::addLocationRequiredSkillModifier(std::shared_ptr<Modifier> modifier)
{
	Item::addLocationRequiredSkillModifier(modifier);
	if (modifier->getAttributeID() == ACTIVATION_BLOCKED_ATTRIBUTE_ID)
		updateActiveStatus();
}*/

void Ship::addProjectedModule(std::shared_ptr<Module> const& module)
{
	if (std::none_of(projectedModules_.begin(), projectedModules_.end(), [=](std::weak_ptr<Module> i) {
		return i.lock() == module;
	}))
	{
		projectedModules_.push_back(module);
		auto engine = getEngine();
		if (engine)
			engine->reset();
	}
}

void Ship::removeProjectedModule(std::shared_ptr<Module> const& module)
{
	std::remove_if(projectedModules_.begin(), projectedModules_.end(), [=](std::weak_ptr<Module> i ) {
		return i.lock() == module;
	});
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

void Ship::addProjectedDrone(std::shared_ptr<Drone> const& drone)
{
	if (std::none_of(projectedDrones_.begin(), projectedDrones_.end(), [=](std::weak_ptr<Drone> i) {
		return i.lock() == drone;
	}))
	{
		projectedDrones_.push_back(drone);
		auto engine = getEngine();
		if (engine)
			engine->reset();
	}
}

void Ship::removeProjectedDrone(std::shared_ptr<Drone> const& drone)
{
	std::remove_if(projectedDrones_.begin(), projectedDrones_.end(), [=](std::weak_ptr<Drone> i ) {
		return i.lock() == drone;
	});
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

std::shared_ptr<CapacitorSimulator> Ship::getCapacitorSimulator()
{
	if (!capacitorSimulator_)
		capacitorSimulator_ = std::make_shared<CapacitorSimulator>(shared_from_this(), false, 6 * 60 * 60 * 1000);
	return capacitorSimulator_;
}

std::shared_ptr<HeatSimulator> Ship::getHeatSimulator()
{
	if (!heatSimulator_)
		heatSimulator_ = std::make_shared<HeatSimulator>(shared_from_this());
	return heatSimulator_;
}

const DamagePattern& Ship::getDamagePattern()
{
	return damagePattern_;
}

void Ship::setDamagePattern(const DamagePattern& damagePattern)
{
	damagePattern_ = damagePattern;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

std::shared_ptr<Cargo> Ship::addCargo(TypeID typeID, size_t count)
{
	
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;
		
		auto i = std::find_if(cargo_.begin(), cargo_.end(), [&](const std::shared_ptr<Cargo>& i) {
			return i->getItem()->getTypeID() == typeID;
		});
		if (i == cargo_.end()) {
			auto item = std::make_shared<Item>(engine, typeID, shared_from_this());
			auto cargo = std::make_shared<Cargo>(item, count);
			cargo_.push_back(cargo);
			return cargo;
		}
		else {
			(*i)->count += count;
			return *i;
		}

	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void Ship::removeCarge(TypeID typeID, size_t count)
{
	
}

const CargoList& Ship::getCargo()
{
	return cargo_;
}

void Ship::setName(const char* name) {
	name_ = name ?: "";
}

const char* Ship::getName() {
	return name_.c_str();
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
		case Module::SLOT_MODE:
			return static_cast<int>(getAttribute(TACTICAL_MODES_ATTRIBUTE_ID)->getValue());
		case Module::SLOT_SERVICE:
			return static_cast<int>(getAttribute(SERVICE_SLOT_ATTRIBUTE_ID)->getValue());
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
	return getModules(slot).size();
}

int Ship::getNumberOfHardpoints(Module::Hardpoint hardpoint)
{
	return getFreeHardpoints(hardpoint) + getUsedHardpoints(hardpoint);
}

int Ship::getRigSize() {
	return static_cast<int>(getAttribute(RIG_SIZE_ATTRIBUTE_ID)->getValue());
}

int Ship::getRaceID() {
	return static_cast<int>(getAttribute(RACE_ID_ATTRIBUTE_ID)->getValue());
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
	for (const auto& i: getModules()) {
		if (i->getHardpoint() == hardpoint)
			n++;
	}
	return n;
}

Float Ship::getCapacity() {
	return getAttribute(CAPACITY_ATTRIBUTE_ID)->getValue();
	}

Float Ship::getOreHoldCapacity() {
	return getAttribute(SPECIAL_ORE_HOLD_CAPACITY)->getValue();
}


Float Ship::getCalibrationUsed()
{
	Float calibration = 0;
	for (const auto& i: getModules(Module::SLOT_RIG))
		calibration += i->getAttribute(UPGRADE_COST_ATTRIBUTE_ID)->getValue();
	return calibration;
}

Float Ship::getTotalCalibration()
{
	return getAttribute(UPGRADE_CAPACITY_ATTRIBUTE_ID)->getValue();
}

Float Ship::getPowerGridUsed()
{
	return getAttribute(POWER_LOAD_ATTRIBUTE_ID)->getValue();
}

Float Ship::getTotalPowerGrid()
{
	return getAttribute(POWER_OUTPUT_ATTRIBUTE_ID)->getValue();
}

Float Ship::getCpuUsed()
{
	return getAttribute(CPU_LOAD_ATTRIBUTE_ID)->getValue();
}

Float Ship::getTotalCpu()
{
	return getAttribute(CPU_OUTPUT_ATTRIBUTE_ID)->getValue();
}

Float Ship::getDroneBandwidthUsed()
{
	Float bandwidth = 0;
	for (const auto& i: drones_)
		if (i->isActive())
			bandwidth += i->getAttribute(DRONE_BANDWIDTH_USED_ATTRIBUTE_ID)->getValue();
	return bandwidth;
}

Float Ship::getTotalDroneBandwidth()
{
	return getAttribute(DRONE_BANDWIDTH_ATTRIBUTE_ID)->getValue();
}

Float Ship::getDroneBayUsed()
{
	Float volume = 0;
	for (const auto& i: drones_)
		if (i->getSquadron() == Drone::FIGHTER_SQUADRON_NONE)
			volume += i->getAttribute(VOLUME_ATTRIBUTE_ID)->getValue();
	return volume;
}

Float Ship::getTotalDroneBay()
{
	return getAttribute(DRONE_CAPACITY_ATTRIBUTE_ID)->getValue();
}

Float Ship::getFighterHangarUsed() {
	Float volume = 0;
	for (const auto& i: drones_)
		if (i->getSquadron() != Drone::FIGHTER_SQUADRON_NONE/* && !i->isActive()*/)
			volume += i->getAttribute(VOLUME_ATTRIBUTE_ID)->getValue();
	return volume;
}

Float Ship::getTotalFighterHangar() {
	return getAttribute(FIGHTER_CAPACITY_ATTRIBUTE_ID)->getValue();
}

//Capacitor

Float Ship::getCapCapacity()
{
	return getAttribute(CAPACITOR_CAPACITY_ATTRIBUTE_ID)->getValue();
}

bool Ship::isCapStable()
{
	return getCapacitorSimulator()->isCapStable();
}

Float Ship::getCapLastsTime()
{
	return getCapacitorSimulator()->getCapLastsTime();
}

Float Ship::getCapStableLevel()
{
	return getCapacitorSimulator()->getCapStableLevel();
}

Float Ship::getCapUsed()
{
	return getCapacitorSimulator()->getCapUsed();
}

Float Ship::getCapRecharge()
{
	return getCapacitorSimulator()->getCapRecharge();
}

Float Ship::getCapRechargeTime() {
	return getAttribute(RECHARGE_RATE_ATTRIBUTE_ID)->getValue() / 1000.0;
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
			Item* currentCharacter = getOwner().get();

			sustainableTank_ = getTank();
			
			std::list<std::shared_ptr<Repairer> > repairers;
			Float capUsed = getCapUsed();
			
			TypeID attributes[] = {ARMOR_DAMAGE_ATTRIBUTE_ID, DAMAGE_ATTRIBUTE_ID, SHIELD_CHARGE_ATTRIBUTE_ID};
			Repairer::Type types[] = {Repairer::TYPE_ARMOR, Repairer::TYPE_HULL, Repairer::TYPE_SHIELD};
			Float* layers[] = {&sustainableTank_.armorRepair, &sustainableTank_.hullRepair, &sustainableTank_.shieldRepair};
			
			for (int i = 0; i < 3; i++)
			{
				ModifiersList modifiers;
				getModifiers(getAttribute(attributes[i]).get(), std::inserter(modifiers, modifiers.end()));
				for (const auto& j: modifiers)
				{
					Modifier::Association association = j->getAssociation();
					if (association == Modifier::ASSOCIATION_ADD_RATE || Modifier::ASSOCIATION_SUB_RATE)
					{
						Item* character = j->getCharacter();
						bool projected = character && character != currentCharacter;
						
						std::shared_ptr<Item> item = j->getModifier()->getOwner();
						if (!projected && item->getCategoryID() == MODULE_CATEGORY_ID)
						{
							std::shared_ptr<Module> module = std::dynamic_pointer_cast<Module>(item);
							assert(module);
							Float use = module->getCapUse();
							if (use > 0) {
								std::shared_ptr<Repairer> repairer (new Repairer);
								repairer->type = types[i];
								repairer->hpPerSec = j->getValue();
								repairer->capPerSec = use;
								repairer->effectivity = repairer->hpPerSec / use;
								*layers[i] -= repairer->hpPerSec;
								capUsed -= repairer->capPerSec;
								repairers.push_back(repairer);
							}
						}
					}
				}
			}
			repairers.sort(RepairersEffectivityCompare());
			
			Float totalPeakRecharge = getCapRecharge();

			for (const auto& repairer: repairers)
			{
				if (capUsed > totalPeakRecharge)
					break;

				if (repairer->capPerSec > 0 && repairer->hpPerSec > 0) {
					Float sustainability = std::min(Float(1.0), (totalPeakRecharge - capUsed) / repairer->capPerSec);
					
					Float amount = sustainability * repairer->hpPerSec;
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

Float Ship::getShieldRecharge()
{
	if (shieldRecharge_ < 0.0)
	{
		Float capacity = getAttribute(SHIELD_CAPACITY_ATTRIBUTE_ID)->getValue();
		Float rechargeRate = getAttribute(SHIELD_RECHARGE_RATE_ATTRIBUTE_ID)->getValue();
		shieldRecharge_ = 10.0 / (rechargeRate / 1000.0) * SHIELD_PEAK_RECHARGE * (1 - SHIELD_PEAK_RECHARGE) * capacity;
	}
	return shieldRecharge_;
}

//DPS

DamageVector Ship::getWeaponDps(const HostileTarget& target)
{
	DamageVector weaponDps = 0;
	for (const auto& i: getModules()) {
		weaponDps += i->getDps(target);
	}
	return weaponDps;
}

DamageVector Ship::getWeaponVolley()
{
	DamageVector weaponVolley = 0;
	for (const auto& i: getModules()) {
		weaponVolley += i->getVolley();
	}
	return weaponVolley;
}

DamageVector Ship::getDroneDps(const HostileTarget& target)
{
	DamageVector droneDps = 0;
	for (const auto& i: drones_)
		droneDps += i->getDps(target);
	return droneDps;
}

DamageVector Ship::getDroneVolley()
{
	DamageVector droneVolley = 0;
	for (const auto& i: drones_)
		droneVolley += i->getVolley();
	return droneVolley;
}

//mobility
Float Ship::getAlignTime()
{
	Float agility = getAgility();
	Float mass = getAttribute(MASS_ATTRIBUTE_ID)->getValue();
	return -std::log(0.25) * agility * mass / 1000000.0;
}

Float Ship::getWarpSpeed()
{
	Float base = getAttribute(BASE_WARP_SPEED_ATTRIBUTE_ID)->getValue();
	Float multiplier = getAttribute(WARP_SPEED_MULTIPLIER_ATTRIBUTE_ID)->getValue();
	if (base == 0.0)
		base = 1.0;
	if (multiplier == 0.0)
		multiplier = 1.0;
	return base * multiplier;
}

Float Ship::getMaxWarpDistance()
{
	Float capacity = getAttribute(CAPACITOR_CAPACITY_ATTRIBUTE_ID)->getValue();
	Float mass = getAttribute(MASS_ATTRIBUTE_ID)->getValue();
	Float warpCapNeed = getAttribute(WARP_CAPACITOR_NEED_ATTRIBUTE_ID)->getValue();
	return capacity / (mass * warpCapNeed);
}

Float Ship::getVelocity()
{
	return getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue();
}

Float Ship::getSignatureRadius()
{
	return getAttribute(SIGNATURE_RADIUS_ATTRIBUTE_ID)->getValue();
}

Float Ship::getMass()
{
	return getAttribute(MASS_ATTRIBUTE_ID)->getValue();
}

Float Ship::getVolume() {
	return getAttribute(VOLUME_ATTRIBUTE_ID)->getValue();
}

Float Ship::getAgility() {
	return getAttribute(AGILITY_ATTRIBUTE_ID)->getValue();
}

Float Ship::getMaxVelocityInOrbit(Float r) {
	double i = getAgility();
	double m = getMass() / 1000000.0;
	double v = getVelocity();
	double i2 = i * i;
	double m2 = m * m;
	double r2 = r * r;
	double r4 = r2 * r2;
	double v2 = v * v;
	return sqrt((sqrt(4 * i2 * m2 * r2 * v2 + r4) / (2 * i2 * m2)) - r2 / (2 * i2 * m2));
}

Float Ship::getOrbitRadiusWithTransverseVelocity(Float v) {
	double i = getAgility();
	double m = getMass() / 1000000.0;
	double vm = getVelocity();
	double s = vm * vm - v * v;
	if (s <= 0)
		return 0;
	return (i * m * v * v) / sqrt(s);
}

Float Ship::getOrbitRadiusWithAngularVelocity(Float v) {
	double lv = getVelocity();
	double r = 0;
	for (int i = 0; i < 10; i++) {
		r = lv / v;
		lv = getMaxVelocityInOrbit(r);
		double av = lv / r;
		if (fabs(av - v) / v < 0.001)
			break;
	}
	return r;
}


//targeting
int Ship::getMaxTargets()
{
	int maxTargetsShip = static_cast<int>(getAttribute(MAX_LOCKED_TARGETS_ATTRIBUTE_ID)->getValue());
	std::shared_ptr<Item> character = getOwner();
	if (character)
	{
		int maxTargetsChar = static_cast<int>(character->getAttribute(MAX_LOCKED_TARGETS_ATTRIBUTE_ID)->getValue());
		return std::min(maxTargetsShip, maxTargetsChar);
	}
	else
		return maxTargetsShip;
}

Float Ship::getMaxTargetRange()
{
	return getAttribute(MAX_TARGET_RANGE_ATTRIBUTE_ID)->getValue();
}

Float Ship::getScanStrength()
{
	Float maxStrength = -1;
	TypeID attributes[] = {SCAN_RADAR_STRENGTH_ATTRIBUTE_ID, SCAN_LADAR_STRENGTH_ATTRIBUTE_ID, SCAN_MAGNETOMETRIC_STRENGTH_ATTRIBUTE_ID, SCAN_GRAVIMETRIC_STRENGTH_ATTRIBUTE_ID};
	for (int i = 0; i < 4; i++)
	{
		Float strength = getAttribute(attributes[i])->getValue();
		if (strength > maxStrength)
		{
			maxStrength = strength;
		}
	}
	return maxStrength;
}

Ship::ScanType Ship::getScanType()
{
	Float maxStrength = -1;
	TypeID attributes[] = {SCAN_RADAR_STRENGTH_ATTRIBUTE_ID, SCAN_LADAR_STRENGTH_ATTRIBUTE_ID, SCAN_MAGNETOMETRIC_STRENGTH_ATTRIBUTE_ID, SCAN_GRAVIMETRIC_STRENGTH_ATTRIBUTE_ID};
	ScanType types[] = {SCAN_TYPE_RADAR, SCAN_TYPE_LADAR, SCAN_TYPE_MAGNETOMETRIC, SCAN_TYPE_GRAVIMETRIC};
	ScanType scanType = SCAN_TYPE_MULTISPECTRAL;
	for (int i = 0; i < 4; i++)
	{
		Float strength = getAttribute(attributes[i])->getValue();
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

Float Ship::getScanResolution()
{
	return getAttribute(SCAN_RESOLUTION_ATTRIBUTE_ID)->getValue();
}

Float Ship::getProbeSize()
{
	Float signatureRadius = getSignatureRadius();
	Float sensorStrength = getScanStrength();
	return sensorStrength > 0.0 ? signatureRadius / sensorStrength : 0.0;
}

//Drones
int Ship::getDroneSquadronLimit(Drone::FighterSquadron squadron)
{
	switch (squadron) {
		case Drone::FIGHTER_SQUADRON_HEAVY:
			return getAttribute(FIGHTER_HEAVY_SLOTS_ATTRIBUTE_ID)->getValue();
		case Drone::FIGHTER_SQUADRON_LIGHT:
			return getAttribute(FIGHTER_LIGHT_SLOTS_ATTRIBUTE_ID)->getValue();
		case Drone::FIGHTER_SQUADRON_SUPPORT:
			return getAttribute(FIGHTER_SUPPORT_SLOTS_ATTRIBUTE_ID)->getValue();
		default:
			auto owner = getOwner();
			return owner ? static_cast<int>(owner->getAttribute(MAX_ACTIVE_DRONES_ATTRIBUTE_ID)->getValue()) : 0;
	}
}

int Ship::getDroneSquadronUsed(Drone::FighterSquadron squadron)
{
	std::set<std::tuple<TypeID, int, bool>> squadrons;
	int n = 0;
	
	for (const auto& i: drones_)
		if (i->isActive() && i->getSquadron() == squadron) {
			if (squadron != Drone::FIGHTER_SQUADRON_NONE) {
				auto key = std::make_tuple(i->getTypeID(), i->getSquadronTag(), i->isActive());
				squadrons.insert(key);
			}
			else {
				n++;
			}
		}
	return squadrons.size() + n;
}

int Ship::getTotalFighterLaunchTubes() {
	return getAttribute(FIGHTER_TUBES_ATTRIBUTE_ID)->getValue();
}

int Ship::getFighterLaunchTubesUsed() {
	std::set<std::tuple<TypeID, int, bool>> squadrons;
	for (const auto& i: drones_)
		if (i->isActive() && i->getSquadron() != Drone::FIGHTER_SQUADRON_NONE) {
			auto key = std::make_tuple(i->getTypeID(), i->getSquadronTag(), i->isActive());
			squadrons.insert(key);
		}
	return squadrons.size();
}

//Other

void Ship::updateModulesState()
{
	for (const auto& i: getModules()) {
		Module::State state = i->getState();
		Module::State preferredState = i->getPreferredState();
		Module::State newState;
		for (newState = preferredState != Module::STATE_UNKNOWN ? preferredState : state; newState > Module::STATE_OFFLINE && !i->canHaveState(newState); newState = static_cast<Module::State>(static_cast<int>(newState) - 1));
		if (newState != state)
			i->setState(newState);
	}
}

void Ship::updateEnabledStatus() {
	for (auto slot: {Module::SLOT_HI, Module::SLOT_MED, Module::SLOT_LOW, Module::SLOT_RIG, Module::SLOT_SUBSYSTEM, Module::SLOT_MODE, Module::SLOT_SERVICE}) {
		int n = getNumberOfSlots(slot);
		auto modules = getModules(slot);
		for (const auto& i: modules) {
			i->setEnabled(n > 0);
			n--;
		}
	}
}

void Ship::updateModulesSockets() {
	auto engine = getEngine();
	if (!engine)
		return;
	
	for (auto slot: {Module::SLOT_HI, Module::SLOT_MED, Module::SLOT_LOW, Module::SLOT_RIG, Module::SLOT_SUBSYSTEM, Module::SLOT_MODE, Module::SLOT_SERVICE}) {
		auto& array = modules_[slot];
		size_t n = getNumberOfSlots(slot);
		if (n > array.size()) {
			for (size_t i = array.size(); i < n; i++) {
				array.push_back(Module::dummy(engine, shared_from_this(), slot));
			}
			//array.resize(n);
		}
		else {
			for (size_t i = array.size(); i > n; i--) {
				auto j = std::find_if(array.rbegin(), array.rend(), [&](const std::shared_ptr<Module>& module) { return module->isDummy(); });
				if (j != array.rend()) {
					array.erase((++j).base());
				}
				else {
					break;
				}
			}
		}
	}
}

void Ship::updateHeatDamage()
{
	getHeatSimulator()->simulate();
}

Item* Ship::character() {
	return getOwner().get();
}

Item* Ship::ship() {
	return this;
}


std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Ship& ship)
{
	os << "{\"typeName\":\"" << ship.getTypeName() << "\", \"typeID\":\"" << ship.typeID_ << "\", \"groupID\":\"" << ship.groupID_ << "\", \"attributes\":[";
	
	if (ship.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: ship.attributes_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i.second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (ship.effects_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: ship.effects_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}

	os << "], \"modules\":[";
	
	auto modules = ship.getModules();
	if (modules.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: modules)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}

	os << "], \"itemModifiers\":[";
	
	if (ship.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: ship.itemModifiers_) {
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
	
	if (ship.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: ship.locationModifiers_) {
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
	
	if (ship.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: ship.locationGroupModifiers_) {
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
	
	if (ship.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: ship.locationRequiredSkillModifiers_) {
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
