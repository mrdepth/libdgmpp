//
//  planet.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "planet.h"
#include "internal.h"

dgmpp_planet_ptr dgmpp_planet_create() {
	return reinterpret_cast<dgmpp_planet_ptr>(new dgmpp_planet_impl());
}

dgmpp_facility_ptr dgmpp_planet_add_facility (dgmpp_planet_ptr planet, dgmpp_type_id type_id, int64_t identifier) {
	try {
		return dgmpp_make_facility(reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.add(static_cast<TypeID>(type_id), identifier));
	}
	catch(...) {
		return nullptr;
	}
}
void dgmpp_planet_remove_facility (dgmpp_planet_ptr planet, dgmpp_facility_ptr facility) {
	reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.remove(facility_cast<Facility*>(facility));
}

dgmpp_facility_ptr dgmpp_planet_get_facility (dgmpp_planet_ptr planet, int64_t identifier) {
	return dgmpp_make_facility(reinterpret_cast<dgmpp_planet_impl*>(planet)->planet[identifier]);
}

dgmpp_array dgmpp_planet_get_facilities (dgmpp_planet_ptr planet) {
	return dgmpp_make_array<dgmpp_facility_impl*>(reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.facilities());
}

void dgmpp_planet_add_route (dgmpp_planet_ptr planet, dgmpp_facility_ptr from, dgmpp_facility_ptr to, dgmpp_commodity commodity) {
	reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.add(Route{
		facility_cast<Facility*>(from),
		facility_cast<Facility*>(to),
		Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity)});
}
void dgmpp_planet_remove_route (dgmpp_planet_ptr planet, dgmpp_facility_ptr from, dgmpp_facility_ptr to, dgmpp_commodity commodity) {
	reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.remove(Route{
		facility_cast<Facility*>(from),
		facility_cast<Facility*>(to),
		Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity)});
}

dgmpp_seconds dgmpp_planet_get_last_update (dgmpp_planet_ptr planet) {
	return dgmpp_make_seconds(reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.lastUpdate());
}

void dgmpp_planet_set_last_update (dgmpp_planet_ptr planet, dgmpp_seconds last_update) {
	reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.lastUpdate(std::chrono::seconds(std::chrono::seconds::rep(last_update)));
}

dgmpp_seconds dgmpp_planet_run (dgmpp_planet_ptr planet) {
	return dgmpp_make_seconds(reinterpret_cast<dgmpp_planet_impl*>(planet)->planet.run());
}
