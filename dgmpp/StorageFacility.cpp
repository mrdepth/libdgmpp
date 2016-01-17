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
	/*double maxVolume = 0;
	for (const auto& input: getInputs())
		maxVolume = std::max(input->getCommodity().getItemVolume(), maxVolume);
	double freeVolume = getFreeVolume();
	if (getFreeVolume() < maxVolume) {
		if (!full_) {
			full_ = true;
			getOwner()->reportWarning(std::make_shared<Warning>(shared_from_this(), Warning::CODE_STORAGE_IS_FULL, cycleTime, 1.0 - freeVolume / getCapacity()));
		}
	}
	else
		full_ = false;*/
	if (cycles_.size() > 0) {
		auto lastCycle = std::dynamic_pointer_cast<StorageCycle>(cycles_.back());
		const auto& lastCycleCommodities = lastCycle->getCommodities();
		const auto& commodities = getCommodities();

		bool equals = false;
		if (lastCycleCommodities.size() == commodities.size()) {
			bool e = false;
			for (const auto& a: commodities) {
				for (const auto& b: lastCycleCommodities) {
					if (a == b) {
						e = true;
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