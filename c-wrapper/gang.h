//
//  gang.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef gang_h
#define gang_h

#include "type.h"

DGMPP_EXTERN dgmpp_type_ptr dgmpp_gang_create();

DGMPP_EXTERN void 				dgmpp_gang_add_pilot	(dgmpp_type_ptr gang, dgmpp_type_ptr pilot);
DGMPP_EXTERN void 				dgmpp_gang_remove_pilot (dgmpp_type_ptr gang, dgmpp_type_ptr pilot);
DGMPP_EXTERN dgmpp_array_ptr	dgmpp_gang_get_pilots	(dgmpp_type_ptr gang);

#endif /* gang_h */
