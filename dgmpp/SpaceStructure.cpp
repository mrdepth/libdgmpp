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

std::vector<AttributeID> SpaceStructure::getSupportedModuleCategories() const {
	return {STRUCTURE_MODULE_CATEGORY_ID};
}

std::shared_ptr<Drone> SpaceStructure::addDrone(TypeID typeID)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;
		std::shared_ptr<Fighter> drone = std::make_shared<Fighter>(engine, typeID, shared_from_this());
		if (drone->getCategoryID() == FIGHTER_CATEGORY_ID) {
			drones_.push_back(drone);
			drone->addEffects(Effect::CATEGORY_GENERIC);
			drone->addEffects(Effect::CATEGORY_TARGET);
			engine->reset();
			return drone;
		}
		else
			return nullptr;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

float SpaceStructure::getTotalDroneBay() {
	return getAttribute(FIGHTER_CAPACITY_ATTRIBUTE_ID)->getValue();
}
