//
//  gang.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef gang_h
#define gang_h

#include "type.h"

dgmpp_type_ptr dgmpp_gang_create();

void 					dgmpp_gang_add_pilot	(dgmpp_type_ptr gang, dgmpp_type_ptr pilot);
void 					dgmpp_gang_remove_pilot (dgmpp_type_ptr gang, dgmpp_type_ptr pilot);
dgmpp_types_array_ptr	dgmpp_gang_get_pilots	(dgmpp_type_ptr gang);

#endif /* gang_h */
