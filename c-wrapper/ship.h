//
//  ship.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef ship_h
#define ship_h

#include "type.h"

DGMPP_EXTERN dgmpp_type dgmpp_ship_create 	(dgmpp_type_id type_id);
DGMPP_EXTERN dgmpp_type dgmpp_ship_copy		(dgmpp_type ship);

DGMPP_EXTERN const char*	dgmpp_ship_get_name (dgmpp_type ship);
DGMPP_EXTERN void			dgmpp_ship_set_name (dgmpp_type ship, const char* name);

DGMPP_EXTERN dgmpp_array			dgmpp_ship_copy_supported_drone_categories	(dgmpp_type ship);
DGMPP_EXTERN DGMPP_RACE_ID			dgmpp_ship_get_race_id						(dgmpp_type ship);
DGMPP_EXTERN DGMPP_RIG_SIZE			dgmpp_ship_get_rig_size						(dgmpp_type ship);
DGMPP_EXTERN dgmpp_damage_vector	dgmpp_ship_get_damage_pattern				(dgmpp_type ship);
DGMPP_EXTERN void					dgmpp_ship_set_damage_pattern				(dgmpp_type ship, dgmpp_damage_vector damage_pattern);

DGMPP_EXTERN BOOL dgmpp_ship_add_module		(dgmpp_type ship, dgmpp_type module);
DGMPP_EXTERN BOOL dgmpp_ship_add_module_v2	(dgmpp_type ship, dgmpp_type module, int socket, BOOL ignoring_requirements);
DGMPP_EXTERN BOOL dgmpp_ship_add_drone		(dgmpp_type ship, dgmpp_type drone);
DGMPP_EXTERN BOOL dgmpp_ship_add_drone_v2	(dgmpp_type ship, dgmpp_type drone, int squadron_tag);
DGMPP_EXTERN void dgmpp_ship_remove_module	(dgmpp_type ship, dgmpp_type module);
DGMPP_EXTERN void dgmpp_ship_remove_drone	(dgmpp_type ship, dgmpp_type drone);
DGMPP_EXTERN BOOL dgmpp_ship_can_fit_module	(dgmpp_type ship, dgmpp_type module);
DGMPP_EXTERN BOOL dgmpp_ship_can_fit_drone	(dgmpp_type ship, dgmpp_type drone);

DGMPP_EXTERN dgmpp_array dgmpp_ship_copy_modules			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_array dgmpp_ship_copy_drones			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_array dgmpp_ship_copy_modules_slot	(dgmpp_type ship, DGMPP_MODULE_SLOT slot);


DGMPP_EXTERN size_t dgmpp_ship_get_total_drone_squadron			(dgmpp_type ship, DGMPP_DRONE_SQUADRON squadron);
DGMPP_EXTERN size_t dgmpp_ship_get_used_drone_squadron			(dgmpp_type ship, DGMPP_DRONE_SQUADRON squadron);
DGMPP_EXTERN size_t dgmpp_ship_get_total_fighter_launch_tubes	(dgmpp_type ship);
DGMPP_EXTERN size_t dgmpp_ship_get_used_fighter_launch_tubes	(dgmpp_type ship);

DGMPP_EXTERN size_t dgmpp_ship_get_total_slots		(dgmpp_type ship, DGMPP_MODULE_SLOT slot);
DGMPP_EXTERN size_t dgmpp_ship_get_free_slots		(dgmpp_type ship, DGMPP_MODULE_SLOT slot);
DGMPP_EXTERN size_t dgmpp_ship_get_used_slots		(dgmpp_type ship, DGMPP_MODULE_SLOT slot);
DGMPP_EXTERN size_t dgmpp_ship_get_total_hardpoints	(dgmpp_type ship, DGMPP_MODULE_HARDPOINT hardpoint);
DGMPP_EXTERN size_t dgmpp_ship_get_free_hardpoints	(dgmpp_type ship, DGMPP_MODULE_HARDPOINT hardpoint);
DGMPP_EXTERN size_t dgmpp_ship_get_used_hardpoints	(dgmpp_type ship, DGMPP_MODULE_HARDPOINT hardpoint);

DGMPP_EXTERN dgmpp_capacitor			dgmpp_ship_get_capacitor (dgmpp_type ship);

DGMPP_EXTERN dgmpp_calibration_points	dgmpp_ship_get_used_calibration			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_calibration_points	dgmpp_ship_get_total_calibration		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_giga_joule			dgmpp_ship_get_used_power_grid			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_giga_joule			dgmpp_ship_get_total_power_grid			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_teraflops			dgmpp_ship_get_used_cpu					(dgmpp_type ship);
DGMPP_EXTERN dgmpp_teraflops			dgmpp_ship_get_total_cpu				(dgmpp_type ship);
DGMPP_EXTERN dgmpp_megabits_per_second	dgmpp_ship_get_used_drone_bandwidth		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_megabits_per_second	dgmpp_ship_get_total_drone_bandwidth	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_used_drone_bay			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_total_drone_bay			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_used_fighter_hangar		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_total_fighter_hangar		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_cargo_capacity			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_ore_hold_capacity		(dgmpp_type ship);

DGMPP_EXTERN dgmpp_resistances	dgmpp_ship_get_resistances					(dgmpp_type ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_tank							(dgmpp_type ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_effective_tank				(dgmpp_type ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_sustainable_tank				(dgmpp_type ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_effective_sustainable_tank	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_hit_points	dgmpp_ship_get_hit_points					(dgmpp_type ship);
DGMPP_EXTERN dgmpp_hit_points	dgmpp_ship_get_effective_hit_points			(dgmpp_type ship);

DGMPP_EXTERN dgmpp_damage_vector		dgmpp_ship_get_turrets_volley	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_damage_vector		dgmpp_ship_get_launchers_volley	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_damage_vector		dgmpp_ship_get_drones_volley	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_turrets_dps		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_launchers_dps	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_drones_dps		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_turrets_dps_v2	(dgmpp_type ship, dgmpp_hostile_target target);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_launchers_dps_v2	(dgmpp_type ship, dgmpp_hostile_target target);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_drones_dps_v2	(dgmpp_type ship, dgmpp_hostile_target target);

DGMPP_EXTERN dgmpp_cubic_meter_per_second dgmpp_ship_get_miner_yield (dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter_per_second dgmpp_ship_get_drone_yield (dgmpp_type ship);

DGMPP_EXTERN dgmpp_seconds							dgmpp_ship_get_align_time			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_astronomical_units_per_second	dgmpp_ship_get_warp_speed			(dgmpp_type ship);
DGMPP_EXTERN dgmpp_astronomical_unit				dgmpp_ship_get_max_warp_distance	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_meters_per_second				dgmpp_ship_get_velocity				(dgmpp_type ship);
DGMPP_EXTERN dgmpp_meter							dgmpp_ship_get_signature_radius		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_kilogram							dgmpp_ship_get_mass 				(dgmpp_type ship);
DGMPP_EXTERN dgmpp_cubic_meter						dgmpp_ship_get_volume 				(dgmpp_type ship);
DGMPP_EXTERN dgmpp_multiplier						dgmpp_ship_get_agility 				(dgmpp_type ship);
DGMPP_EXTERN dgmpp_meters_per_second				dgmpp_ship_get_max_velocity_in_orbit (dgmpp_type ship, dgmpp_meter r);
DGMPP_EXTERN dgmpp_meter	dgmpp_ship_get_orbit_radius_with_transverse_velocity	(dgmpp_type ship, dgmpp_meters_per_second v);
DGMPP_EXTERN dgmpp_meter	dgmpp_ship_get_orbit_radius_with_angular_velocity		(dgmpp_type ship, dgmpp_radians_per_second v);

DGMPP_EXTERN size_t 				dgmpp_ship_get_max_targets		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_meter			dgmpp_ship_get_max_target_range	(dgmpp_type ship);
DGMPP_EXTERN dgmpp_points			dgmpp_ship_get_scan_strength	(dgmpp_type ship);
DGMPP_EXTERN DGMPP_SCAN_TYPE		dgmpp_ship_get_scan_type		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_meter			dgmpp_ship_get_probe_size		(dgmpp_type ship);
DGMPP_EXTERN dgmpp_millimeter		dgmpp_ship_get_scan_resolution	(dgmpp_type ship);


DGMPP_EXTERN dgmpp_giga_joule				dgmpp_capacitor_get_capacity		(dgmpp_capacitor capacitor);
DGMPP_EXTERN dgmpp_seconds					dgmpp_capacitor_get_recharge_time	(dgmpp_capacitor capacitor);
DGMPP_EXTERN dgmpp_seconds					dgmpp_capacitor_get_lasts_time		(dgmpp_capacitor capacitor);
DGMPP_EXTERN BOOL							dgmpp_capacitor_is_stable			(dgmpp_capacitor capacitor);
DGMPP_EXTERN dgmpp_percent					dgmpp_capacitor_get_stable_level	(dgmpp_capacitor capacitor);
DGMPP_EXTERN dgmpp_giga_joule_per_second	dgmpp_capacitor_get_use				(dgmpp_capacitor capacitor);
DGMPP_EXTERN dgmpp_giga_joule_per_second	dgmpp_capacitor_get_recharge		(dgmpp_capacitor capacitor);

#endif /* ship_h */
