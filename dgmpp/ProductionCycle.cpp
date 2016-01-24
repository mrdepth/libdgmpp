//
//  ProductionCycle.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.01.16.
//
//

#include "ProductionCycle.h"
#include "Commodity.h"

using namespace dgmpp;

ProductionCycle::ProductionCycle(double launchTime, double cycleTime, const std::list<std::shared_ptr<const Commodity>>& materials, const Commodity& yield, const Commodity& waste): Cycle(launchTime, cycleTime), materials_(materials) {
	yield_ = std::make_shared<const Commodity>(yield);
	waste_ = std::make_shared<const Commodity>(waste);
}

ProductionCycle::ProductionCycle(double launchTime, double cycleTime, const Commodity& yield, const Commodity& waste): ProductionCycle(launchTime, cycleTime, {}, yield, waste) {
}

void ProductionCycle::setMaterials(const std::list<std::shared_ptr<const Commodity>>& materials) {
	materials_ = materials;
}


bool ProductionCycle::isIdle() const {
	return !yield_ || yield_->getQuantity() == 0;
}
