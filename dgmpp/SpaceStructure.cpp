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
