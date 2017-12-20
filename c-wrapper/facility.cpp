//
//  facility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "facility.h"
#include "internal.h"

DGMPP_FACILITY_CATEGORY dgmpp_facility_get_category (dgmpp_facility_ptr facility) {
	switch (facility_cast<Facility*>(facility)->metaInfo().groupID) {
		case GroupID::commandCenters:
			return DGMPP_FACILITY_CATEGORY_COMMAND_CENTER;
		case GroupID::processors:
			return DGMPP_FACILITY_CATEGORY_FACTORY;
		case GroupID::storageFacilities:
			return DGMPP_FACILITY_CATEGORY_STORAGE;
		case GroupID::spaceports:
			return DGMPP_FACILITY_CATEGORY_SPACEPORT;
		case GroupID::extractorControlUnits:
			return DGMPP_FACILITY_CATEGORY_ECU;
		default:
			return DGMPP_FACILITY_CATEGORY_NONE;
			break;
	}
}

dgmpp_type_id dgmpp_facility_get_type_id (dgmpp_facility_ptr facility) {
	return static_cast<dgmpp_type_id>(facility_cast<Facility*>(facility)->metaInfo().typeID);
}

dgmpp_group_id dgmpp_facility_get_group_id (dgmpp_facility_ptr facility) {
	return static_cast<dgmpp_type_id>(facility_cast<Facility*>(facility)->metaInfo().groupID);
}

int64_t dgmpp_facility_get_identifier (dgmpp_facility_ptr facility) {
	return (facility_cast<Facility*>(facility)->identifier());
}

dgmpp_cubic_meter dgmpp_facility_get_capacity (dgmpp_facility_ptr facility) {
	return facility_cast<Facility*>(facility)->capacity();
}

dgmpp_cubic_meter dgmpp_facility_get_free_volume (dgmpp_facility_ptr facility) {
	return facility_cast<Facility*>(facility)->freeVolume();
}

dgmpp_cubic_meter dgmpp_facility_get_used_volume (dgmpp_facility_ptr facility) {
	return facility_cast<Facility*>(facility)->usedVolume();
}

dgmpp_commodity dgmpp_facility_get_free (dgmpp_facility_ptr facility, dgmpp_type_id commodity_id) {
	return dgmpp_commodity_impl(facility_cast<Facility*>(facility)->free(dgmpp::Commodity(static_cast<TypeID>(commodity_id))));
}

void dgmpp_facility_add_commodity (dgmpp_facility_ptr facility, dgmpp_commodity commodity) {
	facility_cast<Facility*>(facility)->add(dgmpp::Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity));
}

BOOL dgmpp_facility_extract_commodity (dgmpp_facility_ptr facility, dgmpp_commodity commodity) {
	try {
		facility_cast<Facility*>(facility)->extract(dgmpp::Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_array_ptr dgmpp_facility_get_commodities (dgmpp_facility_ptr facility) {
	return dgmpp_make_array<dgmpp_commodity_impl>(facility_cast<Facility*>(facility)->commodities());
}

dgmpp_commodity dgmpp_facility_get_commodity (dgmpp_facility_ptr facility, dgmpp_type_id commodity_id) {
	return dgmpp_commodity_impl((*facility_cast<Facility*>(facility))[static_cast<TypeID>(commodity_id)]);
}

dgmpp_commodity dgmpp_facility_get_income (dgmpp_facility_ptr facility, dgmpp_type_id commodity_id) {
	return dgmpp_commodity_impl(facility_cast<Facility*>(facility)->income(static_cast<TypeID>(commodity_id)));
}

BOOL dgmpp_facility_is_configured (dgmpp_facility_ptr facility) {
	return facility_cast<Facility*>(facility)->configured();
}
