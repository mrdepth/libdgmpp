//
//  area.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "area.h"
#include "internal.h"

BOOL dgmpp_area_create (dgmpp_type_id type_id, dgmpp_type* area) {
	try {
		*area = dgmpp_handle_impl(Area::Create(static_cast<TypeID>(type_id)), dgmpp_handle_tag::unique_ptr_area);
		return true;
	}
	catch (...) {
		return false;
	}
}
