//
//  ProductionCycle.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Commodity.hpp"

namespace dgmpp2 {
	
	struct Cycle {
		std::chrono::seconds launchTime;
		std::chrono::seconds cycleTime;
	};
	
	struct ProductionCycle: Cycle {
		Commodity yield;
		Commodity waste;
	};
}
