//
//  SpaceStructure.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 11.03.16.
//
//

#include "SpaceStructure.h"
#include "Fighter.h"
#include "Attribute.h"

using namespace dgmpp;

SpaceStructure::SpaceStructure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner) : Ship(engine, typeID, owner)
{
	
}

SpaceStructure::~SpaceStructure()
{
	
}

std::vector<TypeID> SpaceStructure::getSupportedModuleCategories() const {
	return {STRUCTURE_MODULE_CATEGORY_ID};
}

std::vector<TypeID> SpaceStructure::getSupportedDroneCategories() const {
	return {FIGHTER_CATEGORY_ID};
}

float SpaceStructure::getTotalDroneBay() {
	return getAttribute(FIGHTER_CAPACITY_ATTRIBUTE_ID)->getValue();
}

TypeID SpaceStructure::getFuelBlockTypeID() {
	TypeID raceID = getAttribute(RACE_ID_ATTRIBUTE_ID)->getValue();
	if (raceID == CALDARI_RACE_ID)
		return NITROGEN_FUEL_BLOCK_TYPE_ID;
	else if (raceID == MINMATAR_RACE_ID)
		return HYDROGEN_FUEL_BLOCK_TYPE_ID;
	else if (raceID == AMARR_RACE_ID)
		return HELIUM_FUEL_BLOCK_TYPE_ID;
	else if (raceID == GALLENTE_RACE_ID)
		return OXYGEN_FUEL_BLOCK_TYPE_ID;
	else
		return 0;
}

/*int SpaceStructure::getDroneSquadronLimit(Fighter::Squadron squadron) {
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

int SpaceStructure::getDroneSquadronUsed(Fighter::Squadron squadron) {
	int n = 0;
	for (const auto& drone: getDrones()) {
		if (std::dynamic_pointer_cast<Fighter>(drone)->getSquadron() == squadron)
			n++;
	}
	return n;
}

int SpaceStructure::getTotalDroneLaunchTubes() {
	return getAttribute(FIGHTER_TUBES_ATTRIBUTE_ID)->getValue();
}

int SpaceStructure::getUsedDroneLaunchTubes() {
	int n = 0;
	for (const auto& drone: getDrones())
		if (drone->isActive())
			n++;
	return n;
}*/
