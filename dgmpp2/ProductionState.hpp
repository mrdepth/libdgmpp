//
//  ProductionState.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "ProductionCycle.hpp"

namespace dgmpp2 {
	
	struct State {
		virtual ~State() = default;

		template <typename T>
		State(std::chrono::seconds timestamp, T&& commodities) : timestamp(timestamp), commodities(std::forward<T>(commodities)) {}
		State(std::chrono::seconds timestamp) : timestamp(timestamp) {}

		std::chrono::seconds timestamp;
		std::vector<Commodity> commodities;
	};
	
	struct ProductionState: State {
		template <typename T>
		ProductionState(std::chrono::seconds timestamp, T&& cycle, Percent efficiency)
		: State(timestamp), cycle(std::forward<T>(cycle)), efficiency(efficiency)  {}

		std::unique_ptr<ProductionCycle> cycle;
		Percent efficiency;
	};
}

