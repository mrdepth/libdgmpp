//
//  StorageCycle.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.01.16.
//
//

#include "StorageCycle.h"
#include "Commodity.h"

using namespace dgmpp;

StorageCycle::StorageCycle(double launchTime, double cycleTime, const std::list<std::shared_ptr<const Commodity>>& commodities): Cycle(launchTime, cycleTime), commodities_(commodities) {
}

double StorageCycle::getVolume() const {
	double volume = 0;
	for (auto commodity: commodities_)
		volume += commodity->getVolume();
	return volume;
}
