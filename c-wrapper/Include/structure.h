//
//  structure.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef structure_h
#define structure_h

#include "type.h"

DGMPP_EXTERN dgmpp_type dgmpp_structure_create (dgmpp_type_id type_id);
DGMPP_EXTERN dgmpp_type dgmpp_structure_copy (dgmpp_type structure);

DGMPP_EXTERN dgmpp_type_id 				dgmpp_structure_get_fuel_block_type_id	(dgmpp_type structure);
DGMPP_EXTERN dgmpp_fuel_units_per_hour	dgmpp_structure_get_fuel_use			(dgmpp_type structure);
#endif /* structure_h */
