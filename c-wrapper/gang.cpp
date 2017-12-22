//
//  gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "gang.h"
#include "internal.h"

dgmpp_type dgmpp_gang_create() {
	return reinterpret_cast<dgmpp_type>(new dgmpp_gang_impl());
}

void dgmpp_gang_add_pilot (dgmpp_type gang, dgmpp_type pilot) {
	type_cast<Gang*>(gang)->add(std::move(reinterpret_cast<dgmpp_character_impl*>(pilot)->character));
}

void dgmpp_gang_remove_pilot (dgmpp_type gang, dgmpp_type pilot) {
	type_cast<Gang*>(gang)->remove(type_cast<Character*>(pilot));
}

dgmpp_array dgmpp_gang_get_pilots (dgmpp_type gang) {
	return dgmpp_make_array<dgmpp_type_impl*>(type_cast<Gang*>(gang)->pilots());
}
