//
//  factory.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "factory.h"
#include "internal.h"

dgmpp_schematic_id dgmpp_factory_get_schematic_id (dgmpp_facility_ptr facility) {
	if (auto schematic = facility_cast<Factory*>(facility)->schematic())
		return static_cast<dgmpp_schematic_id>(schematic->schematicID);
	else
		return static_cast<dgmpp_schematic_id>(SchematicID::none);
}

BOOL dgmpp_factory_set_schematic_id (dgmpp_facility_ptr facility, dgmpp_schematic_id schematic_id) {
	try {
		facility_cast<Factory*>(facility)->schematic(static_cast<SchematicID>(schematic_id));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_seconds dgmpp_factory_get_launch_time (dgmpp_facility_ptr facility) {
	return dgmpp_make_seconds(facility_cast<Factory*>(facility)->launchTime());
}

void dgmpp_factory_set_launch_time (dgmpp_facility_ptr facility, dgmpp_seconds launch_time) {
	facility_cast<Factory*>(facility)->launchTime(std::chrono::seconds(std::chrono::seconds::rep(launch_time)));
}

dgmpp_seconds dgmpp_factory_get_cycle_time (dgmpp_facility_ptr facility) {
	if (auto cycleTime = facility_cast<Factory*>(facility)->cycleTime())
		return dgmpp_make_seconds(*cycleTime);
	else
		return 0;
}

BOOL dgmpp_factory_get_output (dgmpp_facility_ptr facility, dgmpp_commodity* commodity) {
	if (auto output = facility_cast<Factory*>(facility)->output()) {
		*commodity = dgmpp_commodity_impl(*output);
		return true;
	}
	else
		return false;
}

dgmpp_array_ptr dgmpp_factory_get_states (dgmpp_facility_ptr facility) {
	return dgmpp_make_array<dgmpp_state_impl*>(facility_cast<Factory*>(facility)->states());
}

dgmpp_array_ptr dgmpp_factory_get_cycles (dgmpp_facility_ptr facility) {
	return dgmpp_make_array<dgmpp_production_cycle_impl>(facility_cast<Factory*>(facility)->cycles());
}
