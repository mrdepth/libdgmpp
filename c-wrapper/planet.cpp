//
//  planet.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "planet.h"
#include "internal.h"

dgmpp_planet dgmpp_planet_create() {
	return reinterpret_cast<dgmpp_planet>(new Planet());
}

dgmpp_facility dgmpp_planet_add_facility (dgmpp_planet planet, dgmpp_type_id type_id, int64_t identifier) {
	try {
		return reinterpret_cast<Planet*>(planet)->add(static_cast<TypeID>(type_id), identifier);
	}
	catch(...) {
		return nullptr;
	}
}
void dgmpp_planet_remove_facility (dgmpp_planet planet, dgmpp_facility facility) {
	reinterpret_cast<Planet*>(planet)->remove(reinterpret_cast<Facility*>(facility));
}

dgmpp_facility dgmpp_planet_get_facility (dgmpp_planet planet, int64_t identifier) {
	return (*reinterpret_cast<Planet*>(planet))[identifier];
}

dgmpp_array dgmpp_planet_copy_facilities (dgmpp_planet planet) {
	return dgmpp_make_array<Facility*>(reinterpret_cast<Planet*>(planet)->facilities());
}

void dgmpp_planet_add_route (dgmpp_planet planet, dgmpp_facility from, dgmpp_facility to, dgmpp_commodity commodity) {
	reinterpret_cast<Planet*>(planet)->add(Route{
		reinterpret_cast<Facility*>(from),
		reinterpret_cast<Facility*>(to),
		Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity)});
}
void dgmpp_planet_remove_route (dgmpp_planet planet, dgmpp_facility from, dgmpp_facility to, dgmpp_commodity commodity) {
	reinterpret_cast<Planet*>(planet)->remove(Route{
		reinterpret_cast<Facility*>(from),
		reinterpret_cast<Facility*>(to),
		Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity)});
}

dgmpp_seconds dgmpp_planet_get_last_update (dgmpp_planet planet) {
	return dgmpp_make_seconds(reinterpret_cast<Planet*>(planet)->lastUpdate());
}

void dgmpp_planet_set_last_update (dgmpp_planet planet, dgmpp_seconds last_update) {
	reinterpret_cast<Planet*>(planet)->lastUpdate(std::chrono::seconds(std::chrono::seconds::rep(last_update)));
}

dgmpp_seconds dgmpp_planet_run (dgmpp_planet planet) {
	return dgmpp_make_seconds(reinterpret_cast<Planet*>(planet)->run());
}
