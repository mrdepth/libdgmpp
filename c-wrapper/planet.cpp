//
//  planet.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "planet.h"
#include "internal.h"

dgmpp_planet dgmpp_planet_create() {
	return new_handle(std::make_shared<Planet>());
}

dgmpp_facility dgmpp_planet_add_facility (dgmpp_planet planet, dgmpp_type_id type_id, int64_t identifier) {
	try {
		return new_handle(get<Planet>(planet)->add(static_cast<TypeID>(type_id), identifier));
	}
	catch(...) {
		return nullptr;
	}
}
void dgmpp_planet_remove_facility (dgmpp_planet planet, dgmpp_facility facility) {
	get<Planet>(planet)->remove(get<Facility>(facility).get());
}

dgmpp_facility dgmpp_planet_get_facility (dgmpp_planet planet, int64_t identifier) {
	return new_handle((*get<Planet>(planet))[identifier]);
}

dgmpp_array dgmpp_planet_copy_facilities (dgmpp_planet planet) {
    const auto& facilities = get<Planet>(planet)->facilities();
    std::vector<dgmpp_handle> result;
    std::transform(facilities.begin(), facilities.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    return dgmpp_make_array<dgmpp_handle>(std::move(result));
}

void dgmpp_planet_add_route (dgmpp_planet planet, dgmpp_facility from, dgmpp_facility to, dgmpp_commodity commodity) {
	get<Planet>(planet)->add(Route{
		get<Facility>(from).get(),
		get<Facility>(to).get(),
		Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity)});
}
void dgmpp_planet_remove_route (dgmpp_planet planet, dgmpp_facility from, dgmpp_facility to, dgmpp_commodity commodity) {
	get<Planet>(planet)->remove(Route{
		get<Facility>(from).get(),
		get<Facility>(to).get(),
		Commodity(static_cast<TypeID>(commodity.type_id), commodity.quantity)});
}

dgmpp_seconds dgmpp_planet_get_last_update (dgmpp_planet planet) {
	return dgmpp_make_seconds(get<Planet>(planet)->lastUpdate());
}

void dgmpp_planet_set_last_update (dgmpp_planet planet, dgmpp_seconds last_update) {
	get<Planet>(planet)->lastUpdate(std::chrono::seconds(std::chrono::seconds::rep(last_update)));
}

dgmpp_seconds dgmpp_planet_run (dgmpp_planet planet) {
	return dgmpp_make_seconds(get<Planet>(planet)->run());
}
