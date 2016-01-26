//
//  StorageFacility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "StorageFacility.h"
#include "Route.h"
#include "Planet.h"

using namespace dgmpp;

StorageFacility::StorageFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), full_(false) {
}

void StorageFacility::update(double time) {
	Facility::update(time);

	std::shared_ptr<State> currentState ;
	auto commodities = getCommodities();
	if (states_.size() > 0) {
		currentState = states_.back();
		if (currentState->getTimestamp() < time) {
			if (currentState->getCommodities() == commodities)
				return;
		}
		else {
			currentState->setCommodities(commodities);
			return;
		}
	}
	currentState = std::make_shared<State>(time);
	currentState->setCommodities(commodities);
	states_.push_back(currentState);
}

