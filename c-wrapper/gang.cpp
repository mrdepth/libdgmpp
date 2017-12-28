//
//  gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "gang.h"
#include "internal.h"

dgmpp_type dgmpp_gang_create() {
	return add_unique_ptr_wrapper(Gang::Create());
}

dgmpp_type dgmpp_gang_copy (dgmpp_type gang) {
	try {
		return add_unique_ptr_wrapper(Gang::Create(*reinterpret_cast<Gang*>(gang)));
	}
	catch (...) {
		return nullptr;
	}
}

void dgmpp_gang_add_pilot (dgmpp_type gang, dgmpp_type pilot) {
	reinterpret_cast<Gang*>(gang)->add(get_unique_ptr<Character>(pilot));
}

void dgmpp_gang_remove_pilot (dgmpp_type gang, dgmpp_type pilot) {
	reinterpret_cast<Gang*>(gang)->remove(reinterpret_cast<Character*>(pilot));
}

dgmpp_array dgmpp_gang_copy_pilots (dgmpp_type gang) {
	return dgmpp_make_array<Character*>(reinterpret_cast<Gang*>(gang)->pilots());
}

BOOL dgmpp_gang_get_factor_reload (dgmpp_type gang) {
	return reinterpret_cast<Gang*>(gang)->factorReload();
}

void dgmpp_gang_set_factor_reload (dgmpp_type gang, BOOL factor_reload) {
	reinterpret_cast<Gang*>(gang)->factorReload(factor_reload);
}

dgmpp_type dgmpp_gang_get_area (dgmpp_type gang) {
	return reinterpret_cast<Gang*>(gang)->area();
}

void dgmpp_gang_set_area (dgmpp_type gang, dgmpp_type area) {
	reinterpret_cast<Gang*>(gang)->area(get_unique_ptr<Area>(area));
}
