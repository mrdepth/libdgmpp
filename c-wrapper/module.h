//
//  module.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef module_h
#define module_h

#include "type.h"

dgmpp_type_ptr dgmpp_module_create (dgmpp_type_id type_id);

DGMPP_MODULE_SLOT		dgmpp_module_get_slot				(dgmpp_type_ptr module);
DGMPP_MODULE_HARDPOINT	dgmpp_module_get_hardpoint			(dgmpp_type_ptr module);
size_t					dgmpp_module_get_socket				(dgmpp_type_ptr module);
DGMPP_MODULE_STATE		dgmpp_module_get_state				(dgmpp_type_ptr module);
void					dgmpp_module_set_state				(dgmpp_type_ptr module, DGMPP_MODULE_STATE state);
DGMPP_MODULE_STATE		dgmpp_module_get_preferred_state	(dgmpp_type_ptr module);
dgmpp_ints_array_ptr	dgmpp_module_get_available_states	(dgmpp_type_ptr module);
dgmpp_type_ptr			dgmpp_module_get_target				(dgmpp_type_ptr module);
BOOL					dgmpp_module_set_target				(dgmpp_type_ptr module, dgmpp_type_ptr target);
dgmpp_type_ptr			dgmpp_module_get_charge				(dgmpp_type_ptr module);
BOOL					dgmpp_module_set_charge				(dgmpp_type_ptr module, dgmpp_type_ptr charge);
dgmpp_ints_array_ptr	dgmpp_module_get_charge_groups		(dgmpp_type_ptr module);
DGMPP_CHARGE_SIZE		dgmpp_module_get_charge_size		(dgmpp_type_ptr module);
BOOL 					dgmpp_module_is_fail				(dgmpp_type_ptr module);

BOOL dgmpp_module_can_have_state (dgmpp_type_ptr module, DGMPP_MODULE_STATE state);
BOOL dgmpp_module_can_fit_charge (dgmpp_type_ptr module, dgmpp_type_ptr charge);

dgmpp_seconds					dgmpp_module_get_reload_time			(dgmpp_type_ptr module);
dgmpp_seconds					dgmpp_module_get_cycle_time				(dgmpp_type_ptr module);
dgmpp_seconds					dgmpp_module_get_raw_cycle_time			(dgmpp_type_ptr module);
size_t							dgmpp_module_get_charges				(dgmpp_type_ptr module);
size_t							dgmpp_module_get_shots					(dgmpp_type_ptr module);
dgmpp_giga_joule_per_second		dgmpp_module_get_cap_use				(dgmpp_type_ptr module);
dgmpp_teraflops					dgmpp_module_get_cpu_use				(dgmpp_type_ptr module);
dgmpp_mega_watts				dgmpp_module_get_power_grid_use			(dgmpp_type_ptr module);
dgmpp_calibration_points		dgmpp_module_get_calibration_use		(dgmpp_type_ptr module);
dgmpp_points					dgmpp_module_get_accuracy_score			(dgmpp_type_ptr module);
dgmpp_meter						dgmpp_module_get_signature_resolution	(dgmpp_type_ptr module);
dgmpp_cubic_meter_per_second	dgmpp_module_get_mining_yield			(dgmpp_type_ptr module);
dgmpp_damage_vector				dgmpp_module_get_volley					(dgmpp_type_ptr module);
dgmpp_damage_per_second			dgmpp_module_get_dps					(dgmpp_type_ptr module);
dgmpp_damage_per_second			dgmpp_module_get_dps_v2					(dgmpp_type_ptr module, dgmpp_hostile_target target);
dgmpp_meter						dgmpp_module_get_optimal				(dgmpp_type_ptr module);
dgmpp_meter						dgmpp_module_get_falloff				(dgmpp_type_ptr module);
dgmpp_seconds					dgmpp_module_get_lifetime				(dgmpp_type_ptr module);


#endif /* module_h */
