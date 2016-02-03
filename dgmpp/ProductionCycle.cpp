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

ProductionCycle::ProductionCycle(double launchTime, double cycleTime, const Commodity& yield, const Commodity& waste): Cycle(launchTime, cycleTime) {
	yield_ = std::make_shared<const Commodity>(yield);
	waste_ = std::make_shared<const Commodity>(waste);
}
