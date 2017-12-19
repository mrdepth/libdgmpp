//
//  extractor_control_unit.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "extractor_control_unit.h"
#include "internal.h"

dgmpp_seconds dgmpp_ecu_get_launch_time (dgmpp_facility_ptr facility) {
	return dgmpp_make_seconds(facility_cast<ExtractorControlUnit*>(facility)->launchTime());
}

void dgmpp_ecu_set_launch_time (dgmpp_facility_ptr facility, dgmpp_seconds launch_time) {
	facility_cast<ExtractorControlUnit*>(facility)->launchTime(std::chrono::seconds(std::chrono::seconds::rep(launch_time)));
}

dgmpp_seconds dgmpp_ecu_get_install_time (dgmpp_facility_ptr facility) {
	return dgmpp_make_seconds(facility_cast<ExtractorControlUnit*>(facility)->installTime());
}

void dgmpp_ecu_set_install_time (dgmpp_facility_ptr facility, dgmpp_seconds install_time) {
	facility_cast<ExtractorControlUnit*>(facility)->installTime(std::chrono::seconds(std::chrono::seconds::rep(install_time)));
}

dgmpp_seconds dgmpp_ecu_get_expiry_time (dgmpp_facility_ptr facility) {
	return dgmpp_make_seconds(facility_cast<ExtractorControlUnit*>(facility)->expiryTime());
}

void dgmpp_ecu_set_expiry_time (dgmpp_facility_ptr facility, dgmpp_seconds expiry_time) {
	facility_cast<ExtractorControlUnit*>(facility)->expiryTime(std::chrono::seconds(std::chrono::seconds::rep(expiry_time)));
}

dgmpp_seconds dgmpp_ecu_get_cycle_time (dgmpp_facility_ptr facility) {
	return dgmpp_make_seconds(facility_cast<ExtractorControlUnit*>(facility)->cycleTime());
}

void dgmpp_ecu_set_cycle_time (dgmpp_facility_ptr facility, dgmpp_seconds cycle_time) {
	facility_cast<ExtractorControlUnit*>(facility)->cycleTime(std::chrono::seconds(std::chrono::seconds::rep(cycle_time)));
}

size_t dgmpp_ecu_get_quantity_per_cycle (dgmpp_facility_ptr facility) {
	return facility_cast<ExtractorControlUnit*>(facility)->quantityPerCycle();
}

void dgmpp_ecu_set_quantity_per_cycle (dgmpp_facility_ptr facility, size_t quantity_per_cycle) {
	facility_cast<ExtractorControlUnit*>(facility)->quantityPerCycle(quantity_per_cycle);
}

BOOL dgmpp_ecu_get_output (dgmpp_facility_ptr facility, dgmpp_commodity* commodity) {
	if (auto output = facility_cast<ExtractorControlUnit*>(facility)->output()) {
		*commodity = dgmpp_commodity_impl(*output);
		return true;
	}
	else
		return false;
}

dgmpp_array_ptr dgmpp_ecu_get_states (dgmpp_facility_ptr facility) {
	return dgmpp_make_array<dgmpp_state_impl*>(facility_cast<ExtractorControlUnit*>(facility)->states());
}

dgmpp_array_ptr dgmpp_ecu_get_cycles (dgmpp_facility_ptr facility) {
	return dgmpp_make_array<dgmpp_production_cycle_impl>(facility_cast<ExtractorControlUnit*>(facility)->cycles());
}
