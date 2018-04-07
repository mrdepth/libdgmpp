//
//  gang.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef gang_h
#define gang_h

#include "type.h"

DGMPP_EXTERN dgmpp_type		dgmpp_gang_create();
DGMPP_EXTERN dgmpp_type		dgmpp_gang_copy (dgmpp_type gang);

DGMPP_EXTERN void 			dgmpp_gang_add_pilot			(dgmpp_type gang, dgmpp_type pilot);
DGMPP_EXTERN void 			dgmpp_gang_remove_pilot			(dgmpp_type gang, dgmpp_type pilot);
DGMPP_EXTERN dgmpp_array	dgmpp_gang_copy_pilots			(dgmpp_type gang);
DGMPP_EXTERN dgmpp_bool		dgmpp_gang_get_factor_reload	(dgmpp_type gang);
DGMPP_EXTERN void			dgmpp_gang_set_factor_reload	(dgmpp_type gang, dgmpp_bool factor_reload);
DGMPP_EXTERN dgmpp_type		dgmpp_gang_get_area				(dgmpp_type gang);
DGMPP_EXTERN void			dgmpp_gang_set_area				(dgmpp_type gang, dgmpp_type area);

#endif /* gang_h */
