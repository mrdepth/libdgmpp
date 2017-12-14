//
//  structure.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef structure_h
#define structure_h

#include "type.h"

dgmpp_type_ptr dgmpp_structure_create (dgmpp_type_id type_id);

dgmpp_type_id 				dgmpp_structure_get_fuel_block_type_id	(dgmpp_type_ptr structure);
dgmpp_fuel_units_per_hour	dgmpp_structure_get_fuel_use			(dgmpp_type_ptr structure);
#endif /* structure_h */
