//
//  utility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "utility.h"
#include "internal.h"

std::map<dgmpp_handle, std::unique_ptr<unique_ptr_wrapper_base>> unique_pointers;

const dgmpp_hostile_target dgmpp_hostile_target_default = {0, 0, 0, 0};

void dgmpp_free	(dgmpp_handle handle) {
	unique_pointers.erase(handle);
}

//size_t dgmpp_get_hash	(dgmpp_handle handle) {
//	return 0;
////	return reinterpret_cast<dgmpp_t_impl*>(ptr)->hash();
//}

size_t dgmpp_array_get_size (dgmpp_array array) {
//	return 0;
	return reinterpret_cast<dgmpp_array_impl_base*>(array)->size;
}
const void* dgmpp_array_get_values (dgmpp_array array) {
	return reinterpret_cast<dgmpp_array_impl_base*>(array)->ptr();
}

dgmpp_bool dgmpp_commodity_create(dgmpp_type_id type_id, size_t quantity, dgmpp_commodity* commodity) {
	try {
		*commodity = dgmpp_commodity_impl(Commodity(static_cast<TypeID>(type_id), quantity));
		return true;
	}
	catch (...) {
		return false;
	}
}

dgmpp_version dgmpp_get_version () {
	return {dgmpp::version.major, dgmpp::version.minor, {dgmpp::version.sde.build, dgmpp::version.sde.version}};
}
