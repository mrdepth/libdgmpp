//
//  ProductionCycle.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Commodity.hpp"

namespace dgmpp {
	
	struct ProductionCycle {
		std::chrono::seconds start;
		std::chrono::seconds duration;
		std::chrono::seconds end() const noexcept { return start + duration; }
		Commodity yield;
		Commodity waste;
	};
}
