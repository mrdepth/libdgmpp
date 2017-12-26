//
//  charge.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "charge.h"
#include "internal.h"

dgmpp_type dgmpp_charge_create (dgmpp_type_id type_id) {
	try {
		return add_unique_ptr_wrapper(Charge::Create(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

DGMPP_CHARGE_SIZE dgmpp_charge_get_charge_size (dgmpp_type charge) {
	return static_cast<DGMPP_CHARGE_SIZE>(reinterpret_cast<Charge*>(charge)->size());
}
