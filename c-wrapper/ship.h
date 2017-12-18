//
//  ship.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef ship_h
#define ship_h

#include "type.h"

typedef struct dgmpp_capacitor dgmpp_capacitor;
typedef dgmpp_capacitor* dgmpp_capacitor_ptr;
DGMPP_EXTERN void dgmpp_capacitor_free (dgmpp_capacitor_ptr capacitor);

DGMPP_EXTERN dgmpp_type_ptr dgmpp_ship_create (dgmpp_type_id type_id);

DGMPP_EXTERN dgmpp_ints_array_ptr	dgmpp_ship_get_supported_drone_categories	(dgmpp_type_ptr ship);
DGMPP_EXTERN DGMPP_RACE_ID			dgmpp_ship_get_race_id						(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_type_ptr			dgmpp_ship_get_area							(dgmpp_type_ptr ship);
DGMPP_EXTERN void					dgmpp_ship_set_area							(dgmpp_type_ptr ship, dgmpp_type_ptr area);
DGMPP_EXTERN DGMPP_RIG_SIZE			dgmpp_ship_get_rig_size						(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_damage_vector		dgmpp_ship_get_damage_pattern				(dgmpp_type_ptr ship);
DGMPP_EXTERN void					dgmpp_ship_set_damage_pattern				(dgmpp_type_ptr ship, dgmpp_damage_vector damage_pattern);

DGMPP_EXTERN BOOL dgmpp_ship_add_module		(dgmpp_type_ptr ship, dgmpp_type_ptr module);
DGMPP_EXTERN BOOL dgmpp_ship_add_module_v2	(dgmpp_type_ptr ship, dgmpp_type_ptr module, int socket, BOOL ignoring_requirements);
DGMPP_EXTERN BOOL dgmpp_ship_add_drone		(dgmpp_type_ptr ship, dgmpp_type_ptr drone);
DGMPP_EXTERN BOOL dgmpp_ship_add_drone_v2	(dgmpp_type_ptr ship, dgmpp_type_ptr drone, int squadron_tag);
DGMPP_EXTERN void dgmpp_ship_remove_module	(dgmpp_type_ptr ship, dgmpp_type_ptr module);
DGMPP_EXTERN void dgmpp_ship_remove_drone	(dgmpp_type_ptr ship, dgmpp_type_ptr drone);
DGMPP_EXTERN BOOL dgmpp_ship_can_fit_module	(dgmpp_type_ptr ship, dgmpp_type_ptr module);
DGMPP_EXTERN BOOL dgmpp_ship_can_fit_drone	(dgmpp_type_ptr ship, dgmpp_type_ptr drone);

DGMPP_EXTERN dgmpp_types_array_ptr dgmpp_ship_get_modules		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_types_array_ptr dgmpp_ship_get_drones			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_types_array_ptr dgmpp_ship_get_modules_slot	(dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot);


DGMPP_EXTERN size_t dgmpp_ship_get_total_drone_squadron			(dgmpp_type_ptr ship, DGMPP_DRONE_SQUADRON squadron);
DGMPP_EXTERN size_t dgmpp_ship_get_used_drone_squadron			(dgmpp_type_ptr ship, DGMPP_DRONE_SQUADRON squadron);
DGMPP_EXTERN size_t dgmpp_ship_get_total_fighter_launch_tubes	(dgmpp_type_ptr ship);
DGMPP_EXTERN size_t dgmpp_ship_get_used_fighter_launch_tubes		(dgmpp_type_ptr ship);

DGMPP_EXTERN size_t dgmpp_ship_get_total_slots		(dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot);
DGMPP_EXTERN size_t dgmpp_ship_get_free_slots		(dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot);
DGMPP_EXTERN size_t dgmpp_ship_get_used_slots		(dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot);
DGMPP_EXTERN size_t dgmpp_ship_get_total_hardpoints	(dgmpp_type_ptr ship, DGMPP_MODULE_HARDPOINT hardpoint);
DGMPP_EXTERN size_t dgmpp_ship_get_free_hardpoints	(dgmpp_type_ptr ship, DGMPP_MODULE_HARDPOINT hardpoint);
DGMPP_EXTERN size_t dgmpp_ship_get_used_hardpoints	(dgmpp_type_ptr ship, DGMPP_MODULE_HARDPOINT hardpoint);

DGMPP_EXTERN dgmpp_capacitor_ptr dgmpp_ship_get_capacitor (dgmpp_type_ptr ship);

DGMPP_EXTERN dgmpp_calibration_points	dgmpp_ship_get_used_calibration			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_calibration_points	dgmpp_ship_get_total_calibration		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_giga_joule			dgmpp_ship_get_used_power_grid			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_giga_joule			dgmpp_ship_get_total_power_grid			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_teraflops				dgmpp_ship_get_used_cpu					(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_teraflops				dgmpp_ship_get_total_cpu				(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_megabits_per_second	dgmpp_ship_get_used_drone_bandwidth		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_megabits_per_second	dgmpp_ship_get_total_drone_bandwidth	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_used_drone_bay			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_total_drone_bay			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_used_fighter_hangar		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_total_fighter_hangar		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_cargo_capacity			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter			dgmpp_ship_get_ore_hold_capacity		(dgmpp_type_ptr ship);

DGMPP_EXTERN dgmpp_resistances	dgmpp_ship_get_resistances					(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_tank							(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_effective_tank				(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_sustainable_tank				(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_tank			dgmpp_ship_get_effective_sustainable_tank	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_hit_points	dgmpp_ship_get_hit_points					(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_hit_points	dgmpp_ship_get_effective_hit_points			(dgmpp_type_ptr ship);

DGMPP_EXTERN dgmpp_damage_vector		dgmpp_ship_get_turrets_volley	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_damage_vector		dgmpp_ship_get_launchers_volley	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_damage_vector		dgmpp_ship_get_drones_volley	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_turrets_dps		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_launchers_dps	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_drones_dps		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_turrets_dps_v2	(dgmpp_type_ptr ship, dgmpp_hostile_target target);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_launchers_dps_v2	(dgmpp_type_ptr ship, dgmpp_hostile_target target);
DGMPP_EXTERN dgmpp_damage_per_second	dgmpp_ship_get_drones_dps_v2	(dgmpp_type_ptr ship, dgmpp_hostile_target target);

DGMPP_EXTERN dgmpp_cubic_meter_per_second dgmpp_ship_get_miner_yield (dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter_per_second dgmpp_ship_get_drone_yield (dgmpp_type_ptr ship);

DGMPP_EXTERN dgmpp_seconds						dgmpp_ship_get_align_time			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_astronomical_units_per_second	dgmpp_ship_get_warp_speed			(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_astronomical_unit				dgmpp_ship_get_max_warp_distance	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_meters_per_second				dgmpp_ship_get_velocity				(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_meter							dgmpp_ship_get_signature_radius		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_kilogram						dgmpp_ship_get_mass 				(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_cubic_meter					dgmpp_ship_get_volume 				(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_multiplier					dgmpp_ship_get_agility 				(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_meters_per_second				dgmpp_ship_get_max_velocity_in_orbit					(dgmpp_type_ptr ship, dgmpp_meter r);
DGMPP_EXTERN dgmpp_meter							dgmpp_ship_get_orbit_radius_with_transverse_velocity	(dgmpp_type_ptr ship, dgmpp_meters_per_second v);
DGMPP_EXTERN dgmpp_meter							dgmpp_ship_get_orbit_radius_with_angular_velocity		(dgmpp_type_ptr ship, dgmpp_radians_per_second v);

DGMPP_EXTERN size_t 				dgmpp_ship_get_max_targets		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_meter			dgmpp_ship_get_max_target_range	(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_points		dgmpp_ship_get_scan_strength	(dgmpp_type_ptr ship);
DGMPP_EXTERN DGMPP_SCAN_TYPE		dgmpp_ship_get_scan_type		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_meter			dgmpp_ship_get_probe_size		(dgmpp_type_ptr ship);
DGMPP_EXTERN dgmpp_millimeter	dgmpp_ship_get_scan_resolution	(dgmpp_type_ptr ship);


DGMPP_EXTERN dgmpp_giga_joule			dgmpp_capacitor_get_capacity			(dgmpp_capacitor_ptr capacitor);
DGMPP_EXTERN dgmpp_seconds				dgmpp_capacitor_get_recharge_time	(dgmpp_capacitor_ptr capacitor);
DGMPP_EXTERN dgmpp_seconds				dgmpp_capacitor_get_lasts_time		(dgmpp_capacitor_ptr capacitor);
DGMPP_EXTERN BOOL						dgmpp_capacitor_is_stable			(dgmpp_capacitor_ptr capacitor);
DGMPP_EXTERN dgmpp_percent				dgmpp_capacitor_get_stable_level		(dgmpp_capacitor_ptr capacitor);
DGMPP_EXTERN dgmpp_giga_joule_per_second	dgmpp_capacitor_get_use				(dgmpp_capacitor_ptr capacitor);
DGMPP_EXTERN dgmpp_giga_joule_per_second	dgmpp_capacitor_get_recharge			(dgmpp_capacitor_ptr capacitor);

#endif /* ship_h */
