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
        return new_handle(std::make_shared<Structure>(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_structure_copy (dgmpp_type structure) {
	try {
        return new_handle(std::make_shared<Structure>(*get<Structure>(structure)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type_id dgmpp_structure_get_fuel_block_type_id (dgmpp_type structure) {
	return static_cast<dgmpp_type_id>(get<Structure>(structure)->fuelBlockTypeID());
}

dgmpp_fuel_units_per_hour dgmpp_structure_get_fuel_use (dgmpp_type structure) {
	return get<Structure>(structure)->fuelUse() * 1h;
}

dgmpp_type dgmpp_structure_get_area (dgmpp_type structure) {
	return new_handle(get<Structure>(structure)->area());
}
void dgmpp_structure_set_area (dgmpp_type structure, dgmpp_type area) {
	get<Structure>(structure)->area(get<Area>(area));
}
