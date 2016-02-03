//
//  State.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 26.01.16.
//
//

#include "State.h"

using namespace dgmpp;

State::State(double timestamp) : timestamp_(timestamp) {
	
}

void State::setCommodities(const std::list<const Commodity>& commodities) {
	commodities_.clear();
	std::copy(commodities.begin(), commodities.end(), std::inserter(commodities_, commodities_.begin()));
}

double State::getVolume() const {
	double volume = 0;
	for (auto commodity: commodities_)
		volume += commodity.getVolume();
	return volume;
}
