//
//  structure.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "structure.h"
#include "internal.h"

dgmpp_type_ptr dgmpp_structure_create (dgmpp_type_id type_id) {
	try {
		return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_structure_impl(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type_id dgmpp_structure_get_fuel_block_type_id (dgmpp_type_ptr structure) {
	return static_cast<dgmpp_type_id>(type_cast<Structure*>(structure)->fuelBlockTypeID());
}

dgmpp_fuel_units_per_hour dgmpp_structure_get_fuel_use (dgmpp_type_ptr structure) {
	return type_cast<Structure*>(structure)->fuelUse() * 1h;
}
