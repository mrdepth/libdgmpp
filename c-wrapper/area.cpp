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
		return new_handle(std::make_shared<Area>(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_area_copy (dgmpp_type area) {
	try {
		return new_handle(std::make_shared<Area>(*get<Area>(area)));
	}
	catch (...) {
		return nullptr;
	}
}
