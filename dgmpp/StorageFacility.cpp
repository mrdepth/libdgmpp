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
	double maxVolume = 0;
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
		full_ = false;
}