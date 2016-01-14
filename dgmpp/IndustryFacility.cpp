//
//  IndustryFacility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "IndustryFacility.h"
#include "Planet.h"
#include "Engine.h"

using namespace dgmpp;

IndustryFacility::IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), lastLaunchTime_(0) {
}

std::shared_ptr<Schematic> IndustryFacility::setSchematic(TypeID schematicID) {
	schematic_ = schematicID > 0 ? std::make_shared<Schematic>(getOwner()->getEngine(), schematicID) : nullptr;
	return schematic_;
}
