//
//  ProductionState.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "ProductionCycle.hpp"
#include <numeric>

namespace dgmpp {
	
	struct State {
		virtual ~State() = default;

		template <typename T>
		State(std::chrono::seconds timestamp, T&& commodities) : timestamp(timestamp), commodities(std::forward<T>(commodities)) {}
		State(std::chrono::seconds timestamp) : timestamp(timestamp) {}

		std::chrono::seconds timestamp;
		std::vector<Commodity> commodities;
		
		CubicMeter volume() const {
			return std::accumulate(commodities.begin(), commodities.end(), CubicMeter(0), [](auto sum, const auto& i) {
				return sum + i.volume();
			});
		}
	};
	
	struct ProductionState: State {
		ProductionState(std::chrono::seconds timestamp, ProductionCycle* cycle, Percent efficiency)
		: State(timestamp), cycle(cycle), efficiency(efficiency)  {}

		template <typename T>
		ProductionState(std::chrono::seconds timestamp, ProductionCycle* cycle, T&& commodities, Percent efficiency)
		: State(timestamp, std::forward<T>(commodities)), cycle(cycle), efficiency(efficiency)  {}

		ProductionCycle* cycle;
		Percent efficiency;
	};
}

