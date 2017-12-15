//
//  area.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "area.h"
#include "internal.h"

dgmpp_type_ptr dgmpp_area_create (dgmpp_type_id type_id) {
	try {
		return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_area_impl(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}
