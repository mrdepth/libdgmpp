//
//  production_state.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef production_state_h
#define production_state_h

#include "utility.h"
#include <stdio.h>

DGMPP_EXTERN dgmpp_seconds		dgmpp_state_get_timestamp		(dgmpp_state state);
DGMPP_EXTERN dgmpp_array		dgmpp_state_copy_commodities	(dgmpp_state state);
DGMPP_EXTERN dgmpp_cubic_meter	dgmpp_state_get_volume			(dgmpp_state state);

DGMPP_EXTERN BOOL				dgmpp_production_state_get_cycle		(dgmpp_state state, dgmpp_production_cycle* cycle);
DGMPP_EXTERN dgmpp_percent		dgmpp_production_state_get_efficiency	(dgmpp_state state);

#endif /* production_state_h */
