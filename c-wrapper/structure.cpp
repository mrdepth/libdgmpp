//
//  structure.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "structure.h"
#include "internal.h"

dgmpp_type dgmpp_structure_create (dgmpp_type_id type_id) {
	try {
		return add_unique_ptr_wrapper(Structure::Create(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_structure_copy (dgmpp_type structure) {
	try {
		return add_unique_ptr_wrapper(Structure::Create(*reinterpret_cast<Structure*>(structure)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type_id dgmpp_structure_get_fuel_block_type_id (dgmpp_type structure) {
	return static_cast<dgmpp_type_id>(reinterpret_cast<Structure*>(structure)->fuelBlockTypeID());
}

dgmpp_fuel_units_per_hour dgmpp_structure_get_fuel_use (dgmpp_type structure) {
	return reinterpret_cast<Structure*>(structure)->fuelUse() * 1h;
}
