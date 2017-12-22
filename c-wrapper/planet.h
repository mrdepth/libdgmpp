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

DGMPP_EXTERN dgmpp_planet_ptr dgmpp_planet_create();

DGMPP_EXTERN dgmpp_facility_ptr	dgmpp_planet_add_facility		(dgmpp_planet_ptr planet, dgmpp_type_id type_id, int64_t identifier);
DGMPP_EXTERN void				dgmpp_planet_remove_facility	(dgmpp_planet_ptr planet, dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_facility_ptr	dgmpp_planet_get_facility		(dgmpp_planet_ptr planet, int64_t identifier);

DGMPP_EXTERN dgmpp_array dgmpp_planet_get_facilities (dgmpp_planet_ptr planet);

DGMPP_EXTERN void dgmpp_planet_add_route	(dgmpp_planet_ptr planet, dgmpp_facility_ptr from, dgmpp_facility_ptr to, dgmpp_commodity commodity);
DGMPP_EXTERN void dgmpp_planet_remove_route	(dgmpp_planet_ptr planet, dgmpp_facility_ptr from, dgmpp_facility_ptr to, dgmpp_commodity commodity);

DGMPP_EXTERN dgmpp_seconds	dgmpp_planet_get_last_update	(dgmpp_planet_ptr planet);
DGMPP_EXTERN void			dgmpp_planet_set_last_update	(dgmpp_planet_ptr planet, dgmpp_seconds last_update);
DGMPP_EXTERN dgmpp_seconds	dgmpp_planet_run				(dgmpp_planet_ptr planet);

#endif /* planet_h */
