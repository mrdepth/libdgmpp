//
//  ProductionCycle.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Commodity.hpp"

namespace dgmpp {
	
//	struct Cycle {
//		virtual ~Cycle() = default;
//
//		Cycle(std::chrono::seconds start, std::chrono::seconds duration) : start(start), duration(duration) {}
//		
//	};
	
	struct ProductionCycle {
//		ProductionCycle(std::chrono::seconds start, std::chrono::seconds duration, const Commodity& yield, const Commodity& waste)
//		: Cycle(start, duration), yield(yield), waste(waste) {}

		std::chrono::seconds end() const noexcept { return start + duration; }

		std::chrono::seconds start;
		std::chrono::seconds duration;
		Commodity yield;
		Commodity waste;
	};
}
