//
//  drone.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef drone_h
#define drone_h

#include "type.h"

DGMPP_EXTERN dgmpp_type_ptr dgmpp_drone_create (dgmpp_type_id type_id);

DGMPP_EXTERN BOOL					dgmpp_drone_is_active					(dgmpp_type_ptr drone);
DGMPP_EXTERN void					dgmpp_drone_set_active				(dgmpp_type_ptr drone, BOOL active);
DGMPP_EXTERN dgmpp_type_ptr			dgmpp_drone_get_charge			(dgmpp_type_ptr drone);
DGMPP_EXTERN DGMPP_DRONE_SQUADRON	dgmpp_drone_get_squadron		(dgmpp_type_ptr drone);
DGMPP_EXTERN size_t					dgmpp_drone_get_squadron_size	(dgmpp_type_ptr drone);
DGMPP_EXTERN int						dgmpp_drone_get_squadron_tag	(dgmpp_type_ptr drone);

DGMPP_EXTERN dgmpp_type_ptr	dgmpp_drone_get_target	(dgmpp_type_ptr drone);
DGMPP_EXTERN BOOL			dgmpp_drone_set_target	(dgmpp_type_ptr drone, dgmpp_type_ptr target);

DGMPP_EXTERN dgmpp_seconds					dgmpp_drone_get_cycle_time		(dgmpp_type_ptr drone);
DGMPP_EXTERN dgmpp_damage_vector				dgmpp_drone_get_volley			(dgmpp_type_ptr drone);
DGMPP_EXTERN dgmpp_damage_per_second			dgmpp_drone_get_dps				(dgmpp_type_ptr drone);
DGMPP_EXTERN dgmpp_damage_per_second			dgmpp_drone_get_dps_v2			(dgmpp_type_ptr drone, dgmpp_hostile_target target);
DGMPP_EXTERN dgmpp_meter						dgmpp_drone_get_optimal			(dgmpp_type_ptr drone);
DGMPP_EXTERN dgmpp_meter						dgmpp_drone_get_falloff			(dgmpp_type_ptr drone);
DGMPP_EXTERN dgmpp_points					dgmpp_drone_get_accuracy_score	(dgmpp_type_ptr drone);
DGMPP_EXTERN dgmpp_cubic_meter_per_second	dgmpp_drone_get_mining_yield	(dgmpp_type_ptr drone);
DGMPP_EXTERN dgmpp_meters_per_second			dgmpp_drone_get_velocity		(dgmpp_type_ptr drone);


#endif /* drone_h */
