//
//  CommandCenter.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "CommandCenter.h"

using namespace dgmpp;

CommandCenter::CommandCenter(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier) {
}