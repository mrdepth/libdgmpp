//
//  factory.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef factory_h
#define factory_h

#include "utility.h"
#include <stdio.h>

DGMPP_EXTERN dgmpp_schematic_id	dgmpp_factory_get_schematic_id	(dgmpp_facility facility);
DGMPP_EXTERN dgmpp_bool				dgmpp_factory_set_schematic_id	(dgmpp_facility facility, dgmpp_schematic_id schematic_id);
DGMPP_EXTERN dgmpp_seconds		dgmpp_factory_get_launch_time	(dgmpp_facility facility);
DGMPP_EXTERN void				dgmpp_factory_set_launch_time	(dgmpp_facility facility, dgmpp_seconds launch_time);
DGMPP_EXTERN dgmpp_seconds		dgmpp_factory_get_cycle_time	(dgmpp_facility facility);
DGMPP_EXTERN dgmpp_bool				dgmpp_factory_get_output		(dgmpp_facility facility, dgmpp_commodity* commodity);
DGMPP_EXTERN dgmpp_array		dgmpp_factory_copy_states		(dgmpp_facility facility);
DGMPP_EXTERN dgmpp_array		dgmpp_factory_copy_cycles		(dgmpp_facility facility);

#endif /* factory_h */
