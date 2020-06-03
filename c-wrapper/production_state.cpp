//
//  production_state.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "production_state.h"
#include "internal.h"

dgmpp_seconds dgmpp_state_get_timestamp (dgmpp_state state) {
	return dgmpp_make_seconds(reinterpret_cast<State*>(state)->timestamp);
}

dgmpp_array dgmpp_state_copy_commodities (dgmpp_state state) {
    auto commodities = reinterpret_cast<State*>(state)->commodities;
    std::vector<dgmpp_commodity> result;
    std::transform(commodities.begin(), commodities.end(), std::back_inserter(result), [](const auto& i) {
        return dgmpp_commodity_make(i);
    });
    return dgmpp_make_array<dgmpp_commodity>(std::move(result));
}

dgmpp_cubic_meter dgmpp_state_get_volume (dgmpp_state state) {
	return reinterpret_cast<State*>(state)->volume();
}

dgmpp_bool dgmpp_production_state_get_cycle (dgmpp_state state, dgmpp_production_cycle* cycle) {
	if (auto c = reinterpret_cast<ProductionState*>(state)->cycle) {
		*cycle = dgmpp_production_cycle_make(*c);
		return true;
	}
	else
		return false;
}

dgmpp_percent dgmpp_production_state_get_efficiency (dgmpp_state state) {
	return reinterpret_cast<ProductionState*>(state)->efficiency;
}
