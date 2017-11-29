//
//  ProductionState.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "ProductionCycle.hpp"

namespace dgmpp2 {
	
	struct State {
		std::chrono::seconds timestamp;
		std::vector<Commodity> commodities;
	};
	
	struct ProductionState: State {
		ProductionCycle cycle;
		Percent efficiency;
	};
}

