//
//  area.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "area.h"
#include "internal.h"

dgmpp_type dgmpp_area_create (dgmpp_type_id type_id) {
	try {
		return add_unique_ptr_wrapper(Area::Create(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}
