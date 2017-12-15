//
//  utility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "utility.h"
#include "internal.h"

const dgmpp_hostile_target dgmpp_hostile_target_default = {0, 0, 0, 0};

void dgmpp_types_array_free (dgmpp_types_array_ptr array) {
	if (array)
		delete reinterpret_cast<dgmpp_types_array_impl*> (array);
}

void dgmpp_attributes_array_free (dgmpp_attributes_array_ptr array) {
	if (array)
		delete reinterpret_cast<dgmpp_attributes_array_impl*> (array);
}

void dgmpp_ints_array_free (dgmpp_ints_array_ptr array) {
	if (array)
		delete reinterpret_cast<dgmpp_ints_array_impl*> (array);
}

