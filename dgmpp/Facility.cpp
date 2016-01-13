//
//  Facility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Facility.h"

using namespace dgmpp;

std::shared_ptr<Facility> Construct(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner = std::shared_ptr<Item>(nullptr)) {
	
}


Facility::Facility(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner): Item(engine, typeID, owner) {
}

void Facility::addInput(Route* route) {
	inputs_.push_back(route);
}

void Facility::addOutput(Route* route) {
	outputs_.push_back(route);
}

void Facility::removeInput(Route* route) {
	inputs_.remove(route);
}

void Facility::removeOutput(Route* route) {
	outputs_.remove(route);
}
