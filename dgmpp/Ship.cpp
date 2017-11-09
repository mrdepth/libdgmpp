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

			module->addEffects(Effect::Category::generic);
			if (module->canHaveState(Module::State::active))
				module->setInternalState(Module::State::active);
			else if (module->canHaveState(Module::State::online))
				module->setInternalState(Module::State::online);
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
		TypeID chargeTypeID = charge ? charge->getTypeID() : TypeID::none;
		std::shared_ptr<Ship> target = oldModule->getTarget();
		auto socket = static_cast<int>(i - array.begin());
		
		oldModule->setInternalState(Module::State::offline);
		oldModule->clearTarget();
		oldModule->removeEffects(Effect::Category::generic);
		
		if (array.size() > getNumberOfSlots(oldModule->getSlot())) {
			array.erase(i);
		}
		else {
			*i = Module::dummy(engine, shared_from_this(), oldModule->getSlot());
		}
			
		std::shared_ptr<Module> newModule = addModule(typeID, false, socket);
		if (newModule) {
			if (chargeTypeID != TypeID::none)
				newModule->setCharge(chargeTypeID);
			if (target)
				newModule->setTarget();
			newModule->setState(state);
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
		module->setInternalState(Module::State::offline);
		module->clearTarget();
		module->removeEffects(Effect::Category::generic);
		
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
					if (squadron == Drone::Drone::FighterSquadron::none) {
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
				drone->addEffects(Effect::Category::generic);
				drone->addEffects(Effect::Category::target);
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
	drone->removeEffects(Effect::Category::target);
	drone->removeEffects(Effect::Category::generic);
	
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
	if (hardpoint != Module::Hardpoint::none && getFreeHardpoints(hardpoint) == 0)
		return false;
	
	std::vector<TypeID> fitsOnTypes;

	AttributeID canFitToShipTypeAttribute[] = {
		AttributeID::fitsToShipType,
		AttributeID::canFitShipType1,
		AttributeID::canFitShipType2,
		AttributeID::canFitShipType3,
		AttributeID::canFitShipType4,
		AttributeID::canFitShipType5,
		AttributeID::canFitShipType6,
		AttributeID::canFitShipType7,
		AttributeID::canFitShipType8,
		AttributeID::canFitShipType9,
		AttributeID::canFitShipType10,
	};

	for (auto attributeID: canFitToShipTypeAttribute) {
		if (module->hasAttribute(attributeID))
			fitsOnTypes.push_back(static_cast<TypeID>(module->getAttribute(attributeID)->getValue()));
		
	}

	int matchType = 1;
	if (fitsOnTypes.size() > 0) {
		if (std::find(fitsOnTypes.begin(), fitsOnTypes.end(), typeID_) == fitsOnTypes.end())
			matchType = -1;
		else
			matchType = 0;
	}
	
//	if (fitsOn.size() > 0 && std::find(fitsOn.begin(), fitsOn.end(), typeID_) == fitsOn.end())
//		return false;
	
	AttributeID canFitShipGroupAttribute[] = {
		AttributeID::canFitShipGroup01,
		AttributeID::canFitShipGroup02,
		AttributeID::canFitShipGroup03,
		AttributeID::canFitShipGroup04,
		AttributeID::canFitShipGroup05,
		AttributeID::canFitShipGroup06,
		AttributeID::canFitShipGroup07,
		AttributeID::canFitShipGroup08,
		AttributeID::canFitShipGroup09,
		AttributeID::canFitShipGroup10,
		AttributeID::canFitShipGroup11,
		AttributeID::canFitShipGroup12,
		AttributeID::canFitShipGroup13,
		AttributeID::canFitShipGroup14,
		AttributeID::canFitShipGroup15,
		AttributeID::canFitShipGroup16,
		AttributeID::canFitShipGroup17,
		AttributeID::canFitShipGroup18,
		AttributeID::canFitShipGroup19,
		AttributeID::canFitShipGroup20
	};

	std::vector<GroupID> fitsOnGroups;
	
	for (auto attributeID: canFitShipGroupAttribute) {
		if (module->hasAttribute(attributeID))
			fitsOnGroups.push_back(static_cast<GroupID>(module->getAttribute(attributeID)->getValue()));
		
	}

	int matchGroup = 1;
	if (fitsOnGroups.size() > 0) {
		if (std::find(fitsOnGroups.begin(), fitsOnGroups.end(), groupID_) == fitsOnGroups.end())
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
		case Module::Slot::subsystem:
		{
			int subsystemSlot = static_cast<int>(module->getAttribute(AttributeID::subSystemSlot)->getValue());
			for (const auto& i: getModules(Module::Slot::subsystem))
				if (!i->isDummy() && static_cast<int>(i->getAttribute(AttributeID::subSystemSlot)->getValue()) == subsystemSlot)
					return false;
			break;
		}
		case Module::Slot::rig:
		{
			if (static_cast<int>(module->getAttribute(AttributeID::rigSize)->getValue()) != getRigSize())
				return false;
			break;
		}
		default:
			break;
	}
	
	if (module->hasAttribute(AttributeID::maxGroupFitted))
	{
		int maxGroupFitted = static_cast<int>(module->getAttribute(AttributeID::maxGroupFitted)->getValue()) - 1;
		GroupID groupID = module->getGroupID();
		for (const auto& i: getModules()) {
			if (i->getGroupID() == groupID)
			{
				maxGroupFitted--;
				if (maxGroupFitted < 0)
					return false;
			}
		}
	}
	
	if (module->hasAttribute(AttributeID::maxTypeFitted)) {
		int maxTypeFitted = static_cast<int>(module->getAttribute(AttributeID::maxTypeFitted)->getValue()) - 1;
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
		if (hasAttribute(AttributeID::disallowAssistance) && getAttribute(AttributeID::disallowAssistance)->getValue() != 0)
			disallowAssistance_ = DISALLOWED;
		else
		{
			disallowAssistance_ = ALLOWED;
			for (const auto& i: getModules()) {
				if (i->getState() >= Module::State::active &&
					i->hasAttribute(AttributeID::disallowAssistance) &&
					i->getAttribute(AttributeID::disallowAssistance)->getValue() != 0)
				{
					if (i->getGroupID() == GroupID::warpDisruptFieldGenerator && i->getCharge())
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
		if (hasAttribute(AttributeID::disallowOffensiveModifiers) && getAttribute(AttributeID::disallowOffensiveModifiers)->getValue() != 0)
			disallowOffensiveModifiers_ = DISALLOWED;
		else
		{
			disallowOffensiveModifiers_ = ALLOWED;
			for (const auto& i: getModules()) {
				if (i->getState() >= Module::State::active &&
					i->hasAttribute(AttributeID::disallowOffensiveModifiers) &&
					i->getAttribute(AttributeID::disallowOffensiveModifiers)->getValue() != 0)
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

std::vector<CategoryID> Ship::getSupportedModuleCategories() const {
	return {CategoryID::module, CategoryID::subsystem};
}

std::vector<CategoryID> Ship::getSupportedDroneCategories() const {
	return {CategoryID::drone, CategoryID::fighter};
}


void Ship::addEffects(Effect::Category category)
{
	Item::addEffects(category);
	auto engine = getEngine();
	if (!engine)
		return;

	if (category == Effect::Category::generic)
	{
		for (const auto& i: getModules()) {
			i->addEffects(Effect::Category::generic);
		}
		for (const auto& i: drones_)
			i->addEffects(Effect::Category::generic);

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

	if (category == Effect::Category::generic)
	{
		for (const auto& i: getModules()) {
			i->removeEffects(Effect::Category::generic);
		}
		for (const auto& i: drones_)
			i->removeEffects(Effect::Category::generic);

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
		case Module::Slot::hi:
			return static_cast<int>(getAttribute(AttributeID::hiSlots)->getValue());
		case Module::Slot::med:
			return static_cast<int>(getAttribute(AttributeID::medSlots)->getValue());
		case Module::Slot::low:
			return static_cast<int>(getAttribute(AttributeID::lowSlots)->getValue());
		case Module::Slot::rig:
			return static_cast<int>(getAttribute(AttributeID::rigSlots)->getValue());
		case Module::Slot::subsystem:
			return static_cast<int>(getAttribute(AttributeID::maxSubSystems)->getValue());
		case Module::Slot::mode:
			return static_cast<int>(getAttribute(AttributeID::tacticalModes)->getValue());
		case Module::Slot::service:
			return static_cast<int>(getAttribute(AttributeID::serviceSlots)->getValue());
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
	return static_cast<int>(getModules(slot).size());
}

int Ship::getNumberOfHardpoints(Module::Hardpoint hardpoint)
{
	return getFreeHardpoints(hardpoint) + getUsedHardpoints(hardpoint);
}

int Ship::getRigSize() {
	return static_cast<int>(getAttribute(AttributeID::rigSize)->getValue());
}

RaceID Ship::getRaceID() {
	return static_cast<RaceID>(getAttribute(AttributeID::raceID)->getValue());
}

int Ship::getFreeHardpoints(Module::Hardpoint hardpoint)
{
	switch (hardpoint)
	{
		case Module::Hardpoint::launcher:
			return static_cast<int>(getAttribute(AttributeID::launcherSlotsLeft)->getValue());
		case Module::Hardpoint::turret:
			return static_cast<int>(getAttribute(AttributeID::turretSlotsLeft)->getValue());
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
	return getAttribute(AttributeID::capacity)->getValue();
	}

Float Ship::getOreHoldCapacity() {
	return getAttribute(AttributeID::specialOreHoldCapacity)->getValue();
}


Float Ship::getCalibrationUsed()
{
	Float calibration = 0;
	for (const auto& i: getModules(Module::Slot::rig))
		calibration += i->getAttribute(AttributeID::upgradeCost)->getValue();
	return calibration;
}

Float Ship::getTotalCalibration()
{
	return getAttribute(AttributeID::upgradeCapacity)->getValue();
}

Float Ship::getPowerGridUsed()
{
	return getAttribute(AttributeID::powerLoad)->getValue();
}

Float Ship::getTotalPowerGrid()
{
	return getAttribute(AttributeID::powerOutput)->getValue();
}

Float Ship::getCpuUsed()
{
	return getAttribute(AttributeID::cpuLoad)->getValue();
}

Float Ship::getTotalCpu()
{
	return getAttribute(AttributeID::cpuOutput)->getValue();
}

Float Ship::getDroneBandwidthUsed()
{
	Float bandwidth = 0;
	for (const auto& i: drones_)
		if (i->isActive())
			bandwidth += i->getAttribute(AttributeID::droneBandwidthUsed)->getValue();
	return bandwidth;
}

Float Ship::getTotalDroneBandwidth()
{
	return getAttribute(AttributeID::droneBandwidth)->getValue();
}

Float Ship::getDroneBayUsed()
{
	Float volume = 0;
	for (const auto& i: drones_)
		if (i->getSquadron() == Drone::FighterSquadron::none)
			volume += i->getAttribute(AttributeID::volume)->getValue();
	return volume;
}

Float Ship::getTotalDroneBay()
{
	return getAttribute(AttributeID::droneCapacity)->getValue();
}

Float Ship::getFighterHangarUsed() {
	Float volume = 0;
	for (const auto& i: drones_)
		if (i->getSquadron() != Drone::FighterSquadron::none/* && !i->isActive()*/)
			volume += i->getAttribute(AttributeID::volume)->getValue();
	return volume;
}

Float Ship::getTotalFighterHangar() {
	return getAttribute(AttributeID::fighterCapacity)->getValue();
}

//Capacitor

Float Ship::getCapCapacity()
{
	return getAttribute(AttributeID::capacitorCapacity)->getValue();
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
	return getAttribute(AttributeID::rechargeRate)->getValue() / 1000.0;
}

//Tank

const Resistances& Ship::getResistances()
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

const Tank& Ship::getTank()
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
			
			AttributeID attributes[] = {AttributeID::armorDamage, AttributeID::damage, AttributeID::shieldCharge};
			Repairer::Type types[] = {Repairer::TYPE_ARMOR, Repairer::TYPE_HULL, Repairer::TYPE_SHIELD};
			Float* layers[] = {&sustainableTank_.armorRepair, &sustainableTank_.hullRepair, &sustainableTank_.shieldRepair};
			
			for (int i = 0; i < 3; i++)
			{
				ModifiersList modifiers;
				getModifiers(getAttribute(attributes[i]).get(), std::inserter(modifiers, modifiers.end()));
				for (const auto& j: modifiers)
				{
					Modifier::Association association = j->getAssociation();
					if (association == Modifier::Association::addRate || association == Modifier::Association::subRate)
					{
						Item* character = j->getCharacter();
						bool projected = character && character != currentCharacter;
						
						std::shared_ptr<Item> item = j->getModifier()->getOwner();
						if (!projected && item->getCategoryID() == CategoryID::module)
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
		hitPoints_.armor = getAttribute(AttributeID::armorHP)->getValue();
		hitPoints_.hull = getAttribute(AttributeID::hp)->getValue();
		hitPoints_.shield = getAttribute(AttributeID::shieldCapacity)->getValue();
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
		Float capacity = getAttribute(AttributeID::shieldCapacity)->getValue();
		Float rechargeRate = getAttribute(AttributeID::shieldRechargeRate)->getValue();
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

//Mining

Float Ship::getMinerYield()
{
	Float yield = 0;
	for (const auto& i: getModules())
		yield += i->getMiningYield();
	return yield;
}

Float Ship::getDroneYield()
{
	Float yield = 0;
	for (const auto& i: drones_)
		yield += i->getMiningYield();
	return yield;
}

//Mobility
Float Ship::getAlignTime()
{
	Float agility = getAgility();
	Float mass = getAttribute(AttributeID::mass)->getValue();
	return -std::log(0.25) * agility * mass / 1000000.0;
}

Float Ship::getWarpSpeed()
{
	Float base = getAttribute(AttributeID::baseWarpSpeed)->getValue();
	Float multiplier = getAttribute(AttributeID::warpSpeedMultiplier)->getValue();
	if (base == 0.0)
		base = 1.0;
	if (multiplier == 0.0)
		multiplier = 1.0;
	return base * multiplier;
}

Float Ship::getMaxWarpDistance()
{
	Float capacity = getAttribute(AttributeID::capacitorCapacity)->getValue();
	Float mass = getAttribute(AttributeID::mass)->getValue();
	Float warpCapNeed = getAttribute(AttributeID::warpCapacitorNeed)->getValue();
	return capacity / (mass * warpCapNeed);
}

Float Ship::getVelocity()
{
	return getAttribute(AttributeID::maxVelocity)->getValue();
}

Float Ship::getSignatureRadius()
{
	return getAttribute(AttributeID::signatureRadius)->getValue();
}

Float Ship::getMass()
{
	return getAttribute(AttributeID::mass)->getValue();
}

Float Ship::getVolume() {
	return getAttribute(AttributeID::volume)->getValue();
}

Float Ship::getAgility() {
	return getAttribute(AttributeID::agility)->getValue();
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
	int maxTargetsShip = static_cast<int>(getAttribute(AttributeID::maxLockedTargets)->getValue());
	std::shared_ptr<Item> character = getOwner();
	if (character)
	{
		int maxTargetsChar = static_cast<int>(character->getAttribute(AttributeID::maxLockedTargets)->getValue());
		return std::min(maxTargetsShip, maxTargetsChar);
	}
	else
		return maxTargetsShip;
}

Float Ship::getMaxTargetRange()
{
	return getAttribute(AttributeID::maxTargetRange)->getValue();
}

Float Ship::getScanStrength()
{
	Float maxStrength = -1;
	AttributeID attributes[] = {AttributeID::scanRadarStrength, AttributeID::scanLadarStrength, AttributeID::scanMagnetometricStrength, AttributeID::scanGravimetricStrength};
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
	AttributeID attributes[] = {AttributeID::scanRadarStrength, AttributeID::scanLadarStrength, AttributeID::scanMagnetometricStrength, AttributeID::scanGravimetricStrength};
	ScanType types[] = {ScanType::radar, ScanType::ladar, ScanType::magnetometric, ScanType::gravimetric};
	ScanType scanType = ScanType::multispectral;
	for (int i = 0; i < 4; i++)
	{
		Float strength = getAttribute(attributes[i])->getValue();
		if (strength > maxStrength)
		{
			maxStrength = strength;
			scanType = types[i];
		}
		else if (strength == maxStrength)
			scanType = ScanType::multispectral;
	}
	return scanType;
}

Float Ship::getScanResolution()
{
	return getAttribute(AttributeID::scanResolution)->getValue();
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
		case Drone::FighterSquadron::heavy:
			return getAttribute(AttributeID::fighterHeavySlots)->getValue();
		case Drone::FighterSquadron::light:
			return getAttribute(AttributeID::fighterLightSlots)->getValue();
		case Drone::FighterSquadron::support:
			return getAttribute(AttributeID::fighterSupportSlots)->getValue();
		default:
			auto owner = getOwner();
			return owner ? static_cast<int>(owner->getAttribute(AttributeID::maxActiveDrones)->getValue()) : 0;
	}
}

int Ship::getDroneSquadronUsed(Drone::FighterSquadron squadron)
{
	std::set<std::tuple<TypeID, int, bool>> squadrons;
	int n = 0;
	
	for (const auto& i: drones_)
		if (i->isActive() && i->getSquadron() == squadron) {
			if (squadron != Drone::FighterSquadron::none) {
				auto key = std::make_tuple(i->getTypeID(), i->getSquadronTag(), i->isActive());
				squadrons.insert(key);
			}
			else {
				n++;
			}
		}
	return static_cast<int>(squadrons.size()) + n;
}

int Ship::getTotalFighterLaunchTubes() {
	return getAttribute(AttributeID::fighterTubes)->getValue();
}

int Ship::getFighterLaunchTubesUsed() {
	std::set<std::tuple<TypeID, int, bool>> squadrons;
	for (const auto& i: drones_)
		if (i->isActive() && i->getSquadron() != Drone::FighterSquadron::none) {
			auto key = std::make_tuple(i->getTypeID(), i->getSquadronTag(), i->isActive());
			squadrons.insert(key);
		}
	return static_cast<int>(squadrons.size());
}

//Other

void Ship::updateModulesState()
{
	for (const auto& i: getModules()) {
		Module::State state = i->getState();
		Module::State preferredState = i->getPreferredState();
		Module::State newState;
		for (newState = preferredState != Module::State::unknown ? preferredState : state; newState > Module::State::offline && !i->canHaveState(newState); newState = static_cast<Module::State>(static_cast<int>(newState) - 1));
		if (newState != state)
			i->setInternalState(newState);
	}
}

void Ship::updateEnabledStatus() {
	for (auto slot: {Module::Slot::hi, Module::Slot::med, Module::Slot::low, Module::Slot::rig, Module::Slot::subsystem, Module::Slot::mode, Module::Slot::service}) {
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
	
	for (auto slot: {Module::Slot::hi, Module::Slot::med, Module::Slot::low, Module::Slot::rig, Module::Slot::subsystem, Module::Slot::mode, Module::Slot::service}) {
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
	os << "{\"typeName\":\"" << ship.getTypeName() << "\", \"typeID\":\"" << static_cast<int>(ship.typeID_) << "\", \"groupID\":\"" << static_cast<int>(ship.groupID_) << "\", \"attributes\":[";
	
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

namespace dgmpp2 {
	Module* Ship::add(std::unique_ptr<Module> module) {
		auto state = module->state();
		module->state(dgmpp2::Module::State::unknown);
		
		auto m = Type::add(std::move(module));
		
		if (state == Module::State::unknown) {
			m->state(dgmpp2::Module::State::active);
		}
		else {
			m->state(state);
		}
		return m;
	}
	
	void Ship::remove(Module* module) {
		Type::remove(module);
	}

	Type* Ship::domain(Modifier::MetaInfo::Domain domain) {
		switch (domain) {
			case Modifier::MetaInfo::Domain::self:
				return this;
			case Modifier::MetaInfo::Domain::ship:
			case Modifier::MetaInfo::Domain::character:
				return parent();
			case Modifier::MetaInfo::Domain::gang:
				if (auto parent = this->parent()) {
					return parent->parent();
				}
				return nullptr;
			default:
				return nullptr;
		}
		return nullptr;
	}
	
}
