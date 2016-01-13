//
//  ExtractorControlUnit.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "ExtractorControlUnit.h"

using namespace dgmpp;

ExtractorControlUnit::ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier) {
}