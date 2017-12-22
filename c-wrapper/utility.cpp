//
//  utility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "utility.h"
#include "internal.h"

const dgmpp_hostile_target dgmpp_hostile_target_default = {0, 0, 0, 0};

void dgmpp_delete	(dgmpp_handle handle) {
	reinterpret_cast<dgmpp_handle_impl*>(&handle)->destroy();
}

size_t dgmpp_get_hash	(dgmpp_handle handle) {
	return 0;
//	return reinterpret_cast<dgmpp_t_impl*>(ptr)->hash();
}

size_t dgmpp_array_get_size (dgmpp_array array) {
	return dgmpp_cast<dgmpp_array_impl_base>(array).size;
}
const void* dgmpp_array_get_values (dgmpp_array array) {
	return dgmpp_cast<dgmpp_array_impl_base>(array).ptr();
}

dgmpp_commodity dgmpp_commodity_create(dgmpp_type_id type_id, size_t quantity) {
	return dgmpp_commodity_impl(Commodity(static_cast<TypeID>(type_id), quantity));
}
