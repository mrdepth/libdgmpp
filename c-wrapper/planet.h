//
//  planet.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef planet_h
#define planet_h

#include "utility.h"
#include <stdio.h>

DGMPP_EXTERN dgmpp_planet dgmpp_planet_create();

DGMPP_EXTERN dgmpp_facility	dgmpp_planet_add_facility		(dgmpp_planet planet, dgmpp_type_id type_id, int64_t identifier);
DGMPP_EXTERN void			dgmpp_planet_remove_facility	(dgmpp_planet planet, dgmpp_facility facility);
DGMPP_EXTERN dgmpp_facility	dgmpp_planet_get_facility		(dgmpp_planet planet, int64_t identifier);

DGMPP_EXTERN dgmpp_array dgmpp_planet_copy_facilities (dgmpp_planet planet);

DGMPP_EXTERN void dgmpp_planet_add_route	(dgmpp_planet planet, dgmpp_facility from, dgmpp_facility to, dgmpp_commodity commodity);
DGMPP_EXTERN void dgmpp_planet_remove_route	(dgmpp_planet planet, dgmpp_facility from, dgmpp_facility to, dgmpp_commodity commodity);

DGMPP_EXTERN dgmpp_seconds	dgmpp_planet_get_last_update	(dgmpp_planet planet);
DGMPP_EXTERN void			dgmpp_planet_set_last_update	(dgmpp_planet planet, dgmpp_seconds last_update);
DGMPP_EXTERN dgmpp_seconds	dgmpp_planet_run				(dgmpp_planet planet);

#endif /* planet_h */
