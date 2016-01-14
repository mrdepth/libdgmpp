//
//  StorageFacility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "StorageFacility.h"
#include "Route.h"

using namespace dgmpp;

StorageFacility::StorageFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier) {
}

void StorageFacility::startCycle(double cycleTime) {
	for (auto output: getOutputs()) {
		const auto& commodity = output->getCommodity();
		auto free = output->getDestination()->getFreeStorage(commodity);
		if (free > 0) {
			const auto& c = getCommodity(commodity);
			if (c.getQuantity() >= free) {
				Commodity c = Commodity(commodity, free);
				output->getDestination()->addCommodity(c);
				extractCommodity(c);
			}
			else if (c.getQuantity() > 0) {
				output->getDestination()->addCommodity(c);
				extractCommodity(c);
			}
		}
	}
}