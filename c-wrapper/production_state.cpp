//
//  production_state.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "production_state.h"
#include "internal.h"

dgmpp_seconds dgmpp_state_get_timestamp (dgmpp_state_ptr state) {
	return dgmpp_make_seconds(reinterpret_cast<dgmpp_state_impl*>(state)->state->timestamp);
}

dgmpp_array dgmpp_state_get_commodities (dgmpp_state_ptr state) {
	return dgmpp_make_array<dgmpp_commodity_impl>(reinterpret_cast<dgmpp_state_impl*>(state)->state->commodities);
}

dgmpp_cubic_meter dgmpp_state_get_volume (dgmpp_state_ptr state) {
	return reinterpret_cast<dgmpp_state_impl*>(state)->state->volume();
}

BOOL dgmpp_production_state_get_cycle (dgmpp_state_ptr state, dgmpp_production_cycle* cycle) {
	if (auto c = reinterpret_cast<ProductionState*>(reinterpret_cast<dgmpp_state_impl*>(state)->state)->cycle) {
		*cycle = dgmpp_production_cycle_impl(*c);
		return true;
	}
	else
		return false;
}

dgmpp_percent dgmpp_production_state_get_efficiency (dgmpp_state_ptr state) {
	return reinterpret_cast<ProductionState*>(reinterpret_cast<dgmpp_state_impl*>(state)->state)->efficiency;
}
