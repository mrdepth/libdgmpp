//
//  ProductionCycle.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.01.16.
//
//

#include "ProductionCycle.h"
#include "Commodity.h"
#include <sstream>

using namespace dgmpp;

ProductionCycle::ProductionCycle(double launchTime, double cycleTime, const Commodity& yield, const Commodity& waste): Cycle(launchTime, cycleTime) {
	yield_ = std::make_shared<const Commodity>(yield);
	waste_ = std::make_shared<const Commodity>(waste);
}

std::ostream& dgmpp::operator<<(std::ostream& os, const ProductionCycle& productionCycle) {
	bool first = true;
	os << "{";
	if (productionCycle.yield_) {
		os << "\"yield\":" << *productionCycle.yield_;
		first = false;
	}
	if (productionCycle.waste_) {
		if (!first)
			os << ",";
		os << "\"waste\":" << *productionCycle.waste_;
	}
	os << "}" << std::endl;
	return os;
}
