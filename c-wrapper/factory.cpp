//
//  factory.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "factory.h"
#include "internal.h"

dgmpp_schematic_id dgmpp_factory_get_schematic_id (dgmpp_facility facility) {
	if (auto schematic = reinterpret_cast<Factory*>(facility)->schematic())
		return static_cast<dgmpp_schematic_id>(schematic->schematicID);
	else
		return static_cast<dgmpp_schematic_id>(SchematicID::none);
}

dgmpp_bool dgmpp_factory_set_schematic_id (dgmpp_facility facility, dgmpp_schematic_id schematic_id) {
	try {
		reinterpret_cast<Factory*>(facility)->schematic(static_cast<SchematicID>(schematic_id));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_seconds dgmpp_factory_get_launch_time (dgmpp_facility facility) {
	return dgmpp_make_seconds(reinterpret_cast<Factory*>(facility)->launchTime());
}

void dgmpp_factory_set_launch_time (dgmpp_facility facility, dgmpp_seconds launch_time) {
	reinterpret_cast<Factory*>(facility)->launchTime(std::chrono::seconds(std::chrono::seconds::rep(launch_time)));
}

dgmpp_seconds dgmpp_factory_get_cycle_time (dgmpp_facility facility) {
	if (auto cycleTime = reinterpret_cast<Factory*>(facility)->cycleTime())
		return dgmpp_make_seconds(*cycleTime);
	else
		return 0;
}

dgmpp_bool dgmpp_factory_get_output (dgmpp_facility facility, dgmpp_commodity* commodity) {
	if (auto output = reinterpret_cast<Factory*>(facility)->output()) {
		*commodity = dgmpp_commodity_impl(*output);
		return true;
	}
	else
		return false;
}

dgmpp_array dgmpp_factory_copy_states (dgmpp_facility facility) {
	return dgmpp_make_array<ProductionState*>(reinterpret_cast<Factory*>(facility)->states());
}

dgmpp_array dgmpp_factory_copy_cycles (dgmpp_facility facility) {
	return dgmpp_make_array<dgmpp_production_cycle_impl>(reinterpret_cast<Factory*>(facility)->cycles());
}
