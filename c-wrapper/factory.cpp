//
//  factory.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "factory.h"
#include "internal.h"

dgmpp_schematic_id dgmpp_factory_get_schematic_id (dgmpp_facility facility) {
	if (auto schematic = get<Factory>(facility)->schematic())
		return static_cast<dgmpp_schematic_id>(schematic->schematicID);
	else
		return static_cast<dgmpp_schematic_id>(SchematicID::none);
}

dgmpp_bool dgmpp_factory_set_schematic_id (dgmpp_facility facility, dgmpp_schematic_id schematic_id) {
	try {
		get<Factory>(facility)->schematic(static_cast<SchematicID>(schematic_id));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_seconds dgmpp_factory_get_launch_time (dgmpp_facility facility) {
	return dgmpp_make_seconds(get<Factory>(facility)->launchTime());
}

void dgmpp_factory_set_launch_time (dgmpp_facility facility, dgmpp_seconds launch_time) {
	get<Factory>(facility)->launchTime(std::chrono::seconds(std::chrono::seconds::rep(launch_time)));
}

dgmpp_seconds dgmpp_factory_get_cycle_time (dgmpp_facility facility) {
	if (auto cycleTime = get<Factory>(facility)->cycleTime())
		return dgmpp_make_seconds(*cycleTime);
	else
		return 0;
}

dgmpp_bool dgmpp_factory_get_output (dgmpp_facility facility, dgmpp_commodity* commodity) {
	if (auto output = get<Factory>(facility)->output()) {
		*commodity = dgmpp_commodity_make(*output);
		return true;
	}
	else
		return false;
}

dgmpp_array dgmpp_factory_copy_states (dgmpp_facility facility) {
    const auto& states = get<Factory>(facility)->states();
    std::vector<ProductionState*> result;
    std::transform(states.begin(), states.end(), std::back_inserter(result), [](const auto& i) {
        return i.get();
    });
    return dgmpp_make_array<ProductionState*>(std::move(result));
}

dgmpp_array dgmpp_factory_copy_cycles (dgmpp_facility facility) {
    const auto& cycles = get<Factory>(facility)->cycles();
    std::vector<dgmpp_production_cycle> result;
    std::transform(cycles.begin(), cycles.end(), std::back_inserter(result), [](const auto& i) {
        return dgmpp_production_cycle_make(*i);
    });
    return dgmpp_make_array<dgmpp_production_cycle>(std::move(result));
}
