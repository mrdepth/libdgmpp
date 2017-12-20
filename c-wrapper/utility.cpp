//
//  utility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "utility.h"
#include "internal.h"

const dgmpp_hostile_target dgmpp_hostile_target_default = {0, 0, 0, 0};

void dgmpp_retain	(dgmpp_ptr ptr) {
	reinterpret_cast<dgmpp_t_impl*>(ptr)->retain();
}

void dgmpp_release	(dgmpp_ptr ptr) {
	reinterpret_cast<dgmpp_t_impl*>(ptr)->release();
}

size_t dgmpp_get_hash	(dgmpp_ptr ptr) {
	return reinterpret_cast<dgmpp_t_impl*>(ptr)->hash();
}

size_t dgmpp_array_get_size (dgmpp_array_ptr ptr) {
	return reinterpret_cast<dgmpp_array_impl_base*>(ptr)->size;
}
const void* dgmpp_array_get_values (dgmpp_array_ptr ptr) {
	return reinterpret_cast<dgmpp_array_impl_base*>(ptr)->ptr();
}
