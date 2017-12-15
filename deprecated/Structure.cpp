//
//  Structure.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 11.03.16.
//
//

#include "Structure.h"
#include "Attribute.h"

using namespace dgmpp;

Structure::Structure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner) : Ship(engine, typeID, owner)
{
	
}

Structure::~Structure()
{
	
}

std::vector<CategoryID> Structure::getSupportedModuleCategories() const {
	return {CategoryID::structureModule};
}

std::vector<CategoryID> Structure::getSupportedDroneCategories() const {
	return {CategoryID::fighter};
}

Float Structure::getTotalDroneBay() {
	return getAttribute(AttributeID::fighterCapacity)->getValue();
}

TypeID Structure::getFuelBlockTypeID() {
	RaceID raceID = static_cast<RaceID>(getAttribute(AttributeID::raceID)->getValue());
	
	switch (raceID) {
		case RaceID::caldari:
			return TypeID::nitrogenFuelBlock;
		case RaceID::minmatar:
			return TypeID::hydrogenFuelBlock;
		case RaceID::amarr:
			return TypeID::heliumFuelBlock;
		case RaceID::gallente:
			return TypeID::oxygenFuelBlock;
		default:
			return TypeID::none;
	}
}

Float Structure::getCycleFuelNeed() {
	Float fuel = 0;
	for (const auto& module: getModules())
		if (module->hasAttribute(AttributeID::serviceModuleFuelAmount))
			fuel += module->getAttribute(AttributeID::serviceModuleFuelAmount)->getValue();
	return fuel;
}

Float Structure::getCycleTime() {
	return 3600;
}

/*int Structure::getDroneSquadronLimit(Fighter::Squadron squadron) {
	switch (squadron) {
		case Fighter::SQUADRON_HEAVY:
			return getAttribute(FIGHTER_HEAVY_SLOTS_ATTRIBUTE_ID)->getValue();
		case Fighter::SQUADRON_LIGHT:
			return getAttribute(FIGHTER_LIGHT_SLOTS_ATTRIBUTE_ID)->getValue();
		case Fighter::SQUADRON_SUPPORT:
			return getAttribute(FIGHTER_SUPPORT_SLOTS_ATTRIBUTE_ID)->getValue();
		default:
			return 0;
	}
}

int Structure::getDroneSquadronUsed(Fighter::Squadron squadron) {
	int n = 0;
	for (const auto& drone: getDrones()) {
		if (std::dynamic_pointer_cast<Fighter>(drone)->getSquadron() == squadron)
			n++;
	}
	return n;
}

int Structure::getTotalDroneLaunchTubes() {
	return getAttribute(FIGHTER_TUBES_ATTRIBUTE_ID)->getValue();
}

int Structure::getUsedDroneLaunchTubes() {
	int n = 0;
	for (const auto& drone: getDrones())
		if (drone->isActive())
			n++;
	return n;
}*/
