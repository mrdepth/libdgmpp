//
//  Spaceport.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Spaceport.h"

using namespace dgmpp;

Spaceport::Spaceport(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : StorageFacility(typeID, typeName, capacity, owner, identifier) {
}


