//
//  SpaceStructure.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 11.03.16.
//
//

#include "SpaceStructure.h"

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
		std::shared_ptr<Drone> drone = std::make_shared<Drone>(engine, typeID, shared_from_this());
		if (drone->getCategoryID() == DRONE_CATEGORY_ID || drone->getCategoryID() == FIGHTER_CATEGORY_ID) {
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