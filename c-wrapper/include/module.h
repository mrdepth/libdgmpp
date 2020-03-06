//
//  module.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef module_h
#define module_h

#include "type.h"

DGMPP_EXTERN dgmpp_type dgmpp_module_create (dgmpp_type_id type_id);
DGMPP_EXTERN dgmpp_type dgmpp_module_copy (dgmpp_type module);

DGMPP_EXTERN DGMPP_MODULE_SLOT		dgmpp_module_get_slot				(dgmpp_type module);
DGMPP_EXTERN DGMPP_MODULE_HARDPOINT	dgmpp_module_get_hardpoint			(dgmpp_type module);
DGMPP_EXTERN size_t					dgmpp_module_get_socket				(dgmpp_type module);
DGMPP_EXTERN DGMPP_MODULE_STATE		dgmpp_module_get_state				(dgmpp_type module);
DGMPP_EXTERN void					dgmpp_module_set_state				(dgmpp_type module, DGMPP_MODULE_STATE state);
DGMPP_EXTERN DGMPP_MODULE_STATE		dgmpp_module_get_preferred_state	(dgmpp_type module);
DGMPP_EXTERN dgmpp_array			dgmpp_module_copy_available_states	(dgmpp_type module);
DGMPP_EXTERN dgmpp_type				dgmpp_module_get_target				(dgmpp_type module);
DGMPP_EXTERN dgmpp_bool				dgmpp_module_set_target				(dgmpp_type module, dgmpp_type target);
DGMPP_EXTERN dgmpp_type				dgmpp_module_get_charge				(dgmpp_type module);
DGMPP_EXTERN dgmpp_bool				dgmpp_module_set_charge				(dgmpp_type module, dgmpp_type charge);
DGMPP_EXTERN dgmpp_array			dgmpp_module_copy_charge_groups		(dgmpp_type module);
DGMPP_EXTERN DGMPP_CHARGE_SIZE		dgmpp_module_get_charge_size		(dgmpp_type module);
DGMPP_EXTERN dgmpp_bool 			dgmpp_module_is_fail				(dgmpp_type module);
DGMPP_EXTERN dgmpp_bool 			dgmpp_module_require_target			(dgmpp_type module);

DGMPP_EXTERN dgmpp_bool dgmpp_module_can_have_state (dgmpp_type module, DGMPP_MODULE_STATE state);
DGMPP_EXTERN dgmpp_bool dgmpp_module_can_fit_charge (dgmpp_type module, dgmpp_type charge);

DGMPP_EXTERN dgmpp_seconds					dgmpp_module_get_reload_time			(dgmpp_type module);
DGMPP_EXTERN dgmpp_seconds					dgmpp_module_get_cycle_time				(dgmpp_type module);
DGMPP_EXTERN dgmpp_seconds					dgmpp_module_get_raw_cycle_time			(dgmpp_type module);
DGMPP_EXTERN size_t							dgmpp_module_get_charges				(dgmpp_type module);
DGMPP_EXTERN size_t							dgmpp_module_get_shots					(dgmpp_type module);
DGMPP_EXTERN dgmpp_giga_joule_per_second	dgmpp_module_get_cap_use				(dgmpp_type module);
DGMPP_EXTERN dgmpp_teraflops				dgmpp_module_get_cpu_use				(dgmpp_type module);
DGMPP_EXTERN dgmpp_mega_watts				dgmpp_module_get_power_grid_use			(dgmpp_type module);
DGMPP_EXTERN dgmpp_calibration_points		dgmpp_module_get_calibration_use		(dgmpp_type module);
DGMPP_EXTERN dgmpp_points					dgmpp_module_get_accuracy_score			(dgmpp_type module);
DGMPP_EXTERN dgmpp_meter					dgmpp_module_get_signature_resolution	(dgmpp_type module);
DGMPP_EXTERN dgmpp_cubic_meter_per_second	dgmpp_module_get_mining_yield			(dgmpp_type module);
DGMPP_EXTERN dgmpp_damage_vector			dgmpp_module_get_volley					(dgmpp_type module);
DGMPP_EXTERN dgmpp_damage_per_second		dgmpp_module_get_dps					(dgmpp_type module);
DGMPP_EXTERN dgmpp_damage_per_second		dgmpp_module_get_dps_v2					(dgmpp_type module, dgmpp_hostile_target target);
DGMPP_EXTERN dgmpp_meter					dgmpp_module_get_optimal				(dgmpp_type module);
DGMPP_EXTERN dgmpp_meter					dgmpp_module_get_falloff				(dgmpp_type module);
DGMPP_EXTERN dgmpp_seconds					dgmpp_module_get_life_time				(dgmpp_type module);

DGMPP_EXTERN dgmpp_radians_per_second dgmpp_module_get_angular_velocity (dgmpp_type module, dgmpp_meter target_signature, dgmpp_percent hit_chance);


#endif /* module_h */
