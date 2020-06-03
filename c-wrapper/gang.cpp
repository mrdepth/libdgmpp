//
//  gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "gang.h"
#include "internal.h"

dgmpp_type dgmpp_gang_create() {
	return new_handle(std::make_shared<Gang>());
}

dgmpp_type dgmpp_gang_copy (dgmpp_type gang) {
	try {
        return new_handle(std::make_shared<Gang>(*get<Gang>(gang)));
	}
	catch (...) {
		return nullptr;
	}
}

void dgmpp_gang_add_pilot (dgmpp_type gang, dgmpp_type pilot) {
    get<Gang>(gang)->add(get<Character>(pilot));
}

void dgmpp_gang_remove_pilot (dgmpp_type gang, dgmpp_type pilot) {
    get<Gang>(gang)->remove(get<Character>(pilot).get());
}

dgmpp_array dgmpp_gang_copy_pilots (dgmpp_type gang) {
    const auto& pilots = get<Gang>(gang)->pilots();
    std::vector<dgmpp_handle> result;
    std::transform(pilots.begin(), pilots.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    return dgmpp_make_array<dgmpp_handle>(std::move(result));
}

dgmpp_bool dgmpp_gang_get_factor_reload (dgmpp_type gang) {
    return get<Gang>(gang)->factorReload();
}

void dgmpp_gang_set_factor_reload (dgmpp_type gang, dgmpp_bool factor_reload) {
    get<Gang>(gang)->factorReload(factor_reload);
}

dgmpp_type dgmpp_gang_copy_area (dgmpp_type gang) {
    return new_handle(get<Gang>(gang)->area());
}

void dgmpp_gang_set_area (dgmpp_type gang, dgmpp_type area) {
    get<Gang>(gang)->area(get<Area>(area));
}
