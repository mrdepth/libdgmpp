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

DGMPP_EXTERN dgmpp_schematic_id	dgmpp_factory_get_schematic_id	(dgmpp_facility_ptr facility);
DGMPP_EXTERN BOOL				dgmpp_factory_set_schematic_id	(dgmpp_facility_ptr facility, dgmpp_schematic_id schematic_id);
DGMPP_EXTERN dgmpp_seconds		dgmpp_factory_get_launch_time	(dgmpp_facility_ptr facility);
DGMPP_EXTERN void				dgmpp_factory_set_launch_time	(dgmpp_facility_ptr facility, dgmpp_seconds launch_time);
DGMPP_EXTERN dgmpp_seconds		dgmpp_factory_get_cycle_time	(dgmpp_facility_ptr facility);
DGMPP_EXTERN BOOL				dgmpp_factory_get_output		(dgmpp_facility_ptr facility, dgmpp_commodity* commodity);
DGMPP_EXTERN dgmpp_array	dgmpp_factory_get_states		(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_array	dgmpp_factory_get_cycles		(dgmpp_facility_ptr facility);

#endif /* factory_h */
