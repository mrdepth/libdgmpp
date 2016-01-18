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
	if (cycles_.size() > 0) {
		auto lastCycle = std::dynamic_pointer_cast<StorageCycle>(cycles_.back());
		const auto& lastCycleCommodities = lastCycle->getCommodities();
		const auto& commodities = getCommodities();

		bool equals = false;
		if (lastCycleCommodities.size() == commodities.size()) {
			bool e = true;
			for (const auto& a: commodities) {
				for (const auto& b: lastCycleCommodities) {
					if (a != b) {
						e = false;
						break;
					}
				}
				if (!e)
					break;
			}
			equals = e;
		}

		lastCycle->setCycleTime(cycleTime - lastCycle->getLaunchTime());
		
		if (!equals)
			cycles_.push_back(std::make_shared<StorageCycle>(cycleTime, cycleTime, getCommodities()));
	}
	else
		cycles_.push_back(std::make_shared<StorageCycle>(cycleTime, cycleTime, getCommodities()));
}

std::shared_ptr<const StorageCycle> StorageFacility::getCycle(size_t index) const {
	return std::dynamic_pointer_cast<const StorageCycle>(Facility::getCycle(index));
}

std::shared_ptr<const StorageCycle> StorageFacility::getCycle(double timeStamp) const {
	return std::dynamic_pointer_cast<const StorageCycle>(Facility::getCycle(timeStamp));
}
