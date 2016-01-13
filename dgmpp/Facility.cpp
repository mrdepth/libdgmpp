//
//  Facility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Facility.h"

using namespace dgmpp;

Facility::Facility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier): typeID_(typeID), typeName_(typeName), capacity_(capacity), owner_(owner), identifier_(identifier) {
}

void Facility::addInput(const Route* route) {
	inputs_.push_back(route);
}

void Facility::addOutput(const Route* route) {
	outputs_.push_back(route);
}

void Facility::removeInput(const Route* route) {
	inputs_.remove(route);
}

void Facility::removeOutput(const Route* route) {
	outputs_.remove(route);
}
