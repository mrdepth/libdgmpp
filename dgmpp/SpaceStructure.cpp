//
//  SpaceStructure.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 11.03.16.
//
//

#include "SpaceStructure.h"

using namespace dgmpp;

SpaceStructure::SpaceStructure(std::shared_ptr<Engine> const& engine, TypeID typeID) : Ship(engine, typeID, nullptr)
{
	
}

SpaceStructure::~SpaceStructure()
{
	
}