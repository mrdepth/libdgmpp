//
//  extractor_control_unit.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "extractor_control_unit.h"
#include "internal.h"

dgmpp_seconds dgmpp_ecu_get_launch_time (dgmpp_facility facility) {
	return dgmpp_make_seconds(get<ExtractorControlUnit>(facility)->launchTime());
}

void dgmpp_ecu_set_launch_time (dgmpp_facility facility, dgmpp_seconds launch_time) {
	get<ExtractorControlUnit>(facility)->launchTime(std::chrono::seconds(std::chrono::seconds::rep(launch_time)));
}

dgmpp_seconds dgmpp_ecu_get_install_time (dgmpp_facility facility) {
	return dgmpp_make_seconds(get<ExtractorControlUnit>(facility)->installTime());
}

void dgmpp_ecu_set_install_time (dgmpp_facility facility, dgmpp_seconds install_time) {
	get<ExtractorControlUnit>(facility)->installTime(std::chrono::seconds(std::chrono::seconds::rep(install_time)));
}

dgmpp_seconds dgmpp_ecu_get_expiry_time (dgmpp_facility facility) {
	return dgmpp_make_seconds(get<ExtractorControlUnit>(facility)->expiryTime());
}

void dgmpp_ecu_set_expiry_time (dgmpp_facility facility, dgmpp_seconds expiry_time) {
	get<ExtractorControlUnit>(facility)->expiryTime(std::chrono::seconds(std::chrono::seconds::rep(expiry_time)));
}

dgmpp_seconds dgmpp_ecu_get_cycle_time (dgmpp_facility facility) {
	return dgmpp_make_seconds(get<ExtractorControlUnit>(facility)->cycleTime());
}

void dgmpp_ecu_set_cycle_time (dgmpp_facility facility, dgmpp_seconds cycle_time) {
	get<ExtractorControlUnit>(facility)->cycleTime(std::chrono::seconds(std::chrono::seconds::rep(cycle_time)));
}

size_t dgmpp_ecu_get_quantity_per_cycle (dgmpp_facility facility) {
	return get<ExtractorControlUnit>(facility)->quantityPerCycle();
}

void dgmpp_ecu_set_quantity_per_cycle (dgmpp_facility facility, size_t quantity_per_cycle) {
	get<ExtractorControlUnit>(facility)->quantityPerCycle(quantity_per_cycle);
}

dgmpp_bool dgmpp_ecu_get_output (dgmpp_facility facility, dgmpp_commodity* commodity) {
	if (auto output = get<ExtractorControlUnit>(facility)->output()) {
		*commodity = dgmpp_commodity_make(*output);
		return true;
	}
	else
		return false;
}

dgmpp_array dgmpp_ecu_copy_states (dgmpp_facility facility) {
    const auto& states = get<ExtractorControlUnit>(facility)->states();
    std::vector<State*> result;
    std::transform(states.begin(), states.end(), std::back_inserter(result), [](const auto& i) {
        return i.get();
    });
	return dgmpp_make_array<State*>(std::move(result));
}

dgmpp_array dgmpp_ecu_copy_cycles (dgmpp_facility facility) {
    const auto& cycles = get<ExtractorControlUnit>(facility)->cycles();
    std::vector<dgmpp_production_cycle> result;
    std::transform(cycles.begin(), cycles.end(), std::back_inserter(result), [](const auto& i) {
        return dgmpp_production_cycle_make(*i);
    });
    return dgmpp_make_array<dgmpp_production_cycle>(std::move(result));
}
