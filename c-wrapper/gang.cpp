//
//  gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "gang.h"
#include "internal.h"

dgmpp_type_ptr dgmpp_gang_create() {
	return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_gang_impl());
}

void dgmpp_gang_add_pilot (dgmpp_type_ptr gang, dgmpp_type_ptr pilot) {
	type_cast<Gang*>(gang)->add(std::move(reinterpret_cast<dgmpp_character_impl*>(pilot)->character));
}

void dgmpp_gang_remove_pilot (dgmpp_type_ptr gang, dgmpp_type_ptr pilot) {
	type_cast<Gang*>(gang)->remove(type_cast<Character*>(pilot));
}

dgmpp_types_array_ptr dgmpp_gang_get_pilots (dgmpp_type_ptr gang) {
	return new dgmpp_types_array_impl(type_cast<Gang*>(gang)->pilots());
}
