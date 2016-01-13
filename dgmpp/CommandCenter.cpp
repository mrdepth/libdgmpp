//
//  CommandCenter.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "CommandCenter.h"

using namespace dgmpp;

CommandCenter::CommandCenter(std::shared_ptr<Engine> const& engine, TypeID typeID): Facility(engine, typeID) {
}

std::shared_ptr<Facility> CommandCenter::addFacility(TypeID typeID) {
	//return facilities_.push_back(std::make_shared<Facility>(getEngine(), typeID, shared_from_this()));
}

void CommandCenter::removeFacility(std::shared_ptr<Facility> const& facility) {
	
}

std::shared_ptr<Route> CommandCenter::addRoute(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID) {
	
}

void CommandCenter::removeRoute(std::shared_ptr<Route> const& route) {
	
}
