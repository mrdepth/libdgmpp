//
//  ship.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "ship.h"
#include "internal.h"

void dgmpp_capacitor_free (dgmpp_capacitor_ptr capacitor) {
	if (capacitor)
		delete reinterpret_cast<dgmpp_capacitor_impl*>(capacitor);
}

dgmpp_type_ptr dgmpp_ship_create (dgmpp_type_id type_id) {
	try {
		return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_ship_impl(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

const char*	dgmpp_ship_get_name (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->name().c_str();
}

void dgmpp_ship_set_name (dgmpp_type_ptr ship, const char* name) {
	type_cast<Ship*>(ship)->name(name);
}


dgmpp_array_ptr dgmpp_ship_get_supported_drone_categories (dgmpp_type_ptr ship) {
	return dgmpp_make_array<int>(type_cast<Ship*>(ship)->supportedDroneCategories());
}

DGMPP_RACE_ID dgmpp_ship_get_race_id (dgmpp_type_ptr ship) {
	return static_cast<DGMPP_RACE_ID>(type_cast<Ship*>(ship)->raceID());
}

dgmpp_type_ptr dgmpp_ship_get_area (dgmpp_type_ptr ship) {
	return dgmpp_make_type(type_cast<Ship*>(ship)->area());
}

void dgmpp_ship_set_area (dgmpp_type_ptr ship, dgmpp_type_ptr area) {
	type_cast<Ship*>(ship)->area(std::move(reinterpret_cast<dgmpp_area_impl*>(area)->area));
}

DGMPP_RIG_SIZE dgmpp_ship_get_rig_size (dgmpp_type_ptr ship) {
	return static_cast<DGMPP_RIG_SIZE>(type_cast<Ship*>(ship)->rigSize());
}

dgmpp_damage_vector dgmpp_ship_get_damage_pattern (dgmpp_type_ptr ship) {
	return dgmpp_damage_vector_make(type_cast<Ship*>(ship)->damagePattern());
}

void dgmpp_ship_set_damage_pattern (dgmpp_type_ptr ship, dgmpp_damage_vector damage_pattern) {
	type_cast<Ship*>(ship)->damagePattern(damage_vector_make(damage_pattern));
}

BOOL dgmpp_ship_add_module (dgmpp_type_ptr ship, dgmpp_type_ptr module) {
	return dgmpp_ship_add_module_v2(ship, module, -1, false);
}

BOOL dgmpp_ship_add_module_v2 (dgmpp_type_ptr ship, dgmpp_type_ptr module, int socket, BOOL ignoring_requirements) {
	try {
		type_cast<Ship*>(ship)->add(std::move(reinterpret_cast<dgmpp_module_impl*>(module)->module), socket, ignoring_requirements);
		return true;
	}
	catch(...) {
		return false;
	}
}

BOOL dgmpp_ship_add_drone (dgmpp_type_ptr ship, dgmpp_type_ptr drone) {
	return dgmpp_ship_add_drone_v2(ship, drone, -1);
}

BOOL dgmpp_ship_add_drone_v2 (dgmpp_type_ptr ship, dgmpp_type_ptr drone, int squadron_tag) {
	try {
		type_cast<Ship*>(ship)->add(std::move(reinterpret_cast<dgmpp_drone_impl*>(drone)->drone), squadron_tag);
		return true;
	}
	catch(...) {
		return false;
	}
}

void dgmpp_ship_remove_module (dgmpp_type_ptr ship, dgmpp_type_ptr module) {
	type_cast<Ship*>(ship)->remove(type_cast<Module*>(module));
}

void dgmpp_ship_remove_drone (dgmpp_type_ptr ship, dgmpp_type_ptr drone) {
	type_cast<Ship*>(ship)->remove(type_cast<Drone*>(drone));
}

BOOL dgmpp_ship_can_fit_module (dgmpp_type_ptr ship, dgmpp_type_ptr module) {
	return type_cast<Ship*>(ship)->canFit(type_cast<Module*>(module));
}

BOOL dgmpp_ship_can_fit_drone (dgmpp_type_ptr ship, dgmpp_type_ptr drone) {
	return type_cast<Ship*>(ship)->canFit(type_cast<Drone*>(drone));
}

dgmpp_array_ptr dgmpp_ship_get_modules (dgmpp_type_ptr ship) {
	return dgmpp_make_array<dgmpp_type_impl*>(type_cast<Ship*>(ship)->modules());
}

dgmpp_array_ptr dgmpp_ship_get_drones (dgmpp_type_ptr ship) {
	return dgmpp_make_array<dgmpp_type_impl*>(type_cast<Ship*>(ship)->drones());
}

dgmpp_array_ptr dgmpp_ship_get_modules_slot (dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot) {
	return dgmpp_make_array<dgmpp_type_impl*>(type_cast<Ship*>(ship)->modules(static_cast<Module::Slot>(slot)));
}

size_t dgmpp_ship_get_total_drone_squadron (dgmpp_type_ptr ship, DGMPP_DRONE_SQUADRON squadron) {
	return type_cast<Ship*>(ship)->totalDroneSquadron(static_cast<Drone::Squadron>(squadron));
}

size_t dgmpp_ship_get_used_drone_squadron (dgmpp_type_ptr ship, DGMPP_DRONE_SQUADRON squadron) {
	return type_cast<Ship*>(ship)->usedDroneSquadron(static_cast<Drone::Squadron>(squadron));
}

size_t dgmpp_ship_get_total_fighter_launch_tubes (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->totalFighterLaunchTubes();
}

size_t dgmpp_ship_get_used_fighter_launch_tubes (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->usedFighterLaunchTubes();
}

size_t dgmpp_ship_get_total_slots (dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot) {
	return type_cast<Ship*>(ship)->totalSlots(static_cast<Module::Slot>(slot));
}

size_t dgmpp_ship_get_free_slots (dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot) {
	return type_cast<Ship*>(ship)->freeSlots(static_cast<Module::Slot>(slot));
}

size_t dgmpp_ship_get_used_slots (dgmpp_type_ptr ship, DGMPP_MODULE_SLOT slot) {
	return type_cast<Ship*>(ship)->usedSlots(static_cast<Module::Slot>(slot));
}

size_t dgmpp_ship_get_total_hardpoints (dgmpp_type_ptr ship, DGMPP_MODULE_HARDPOINT hardpoint) {
	return type_cast<Ship*>(ship)->totalHardpoints(static_cast<Module::Hardpoint>(hardpoint));
}

size_t dgmpp_ship_get_free_hardpoints (dgmpp_type_ptr ship, DGMPP_MODULE_HARDPOINT hardpoint) {
	return type_cast<Ship*>(ship)->freeHardpoints(static_cast<Module::Hardpoint>(hardpoint));
}

size_t dgmpp_ship_get_used_hardpoints (dgmpp_type_ptr ship, DGMPP_MODULE_HARDPOINT hardpoint) {
	return type_cast<Ship*>(ship)->usedHardpoints(static_cast<Module::Hardpoint>(hardpoint));
}


dgmpp_capacitor_ptr dgmpp_ship_get_capacitor (dgmpp_type_ptr ship) {
	return reinterpret_cast<dgmpp_capacitor_ptr>(new dgmpp_capacitor_impl{&type_cast<Ship*>(ship)->capacitor()});
}

dgmpp_calibration_points dgmpp_ship_get_used_calibration (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->usedCalibration();
}

dgmpp_calibration_points dgmpp_ship_get_total_calibration (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->totalCalibration();
}

dgmpp_giga_joule dgmpp_ship_get_used_power_grid (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->usedPowerGrid();
}

dgmpp_giga_joule dgmpp_ship_get_total_power_grid (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->totalPowerGrid();
}

dgmpp_teraflops dgmpp_ship_get_used_cpu (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->usedCPU();
}

dgmpp_teraflops dgmpp_ship_get_total_cpu (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->totalCPU();
}

dgmpp_megabits_per_second dgmpp_ship_get_used_drone_bandwidth (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->usedDroneBandwidth();
}

dgmpp_megabits_per_second dgmpp_ship_get_total_drone_bandwidth (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->totalDroneBandwidth();
}

dgmpp_cubic_meter dgmpp_ship_get_used_drone_bay (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->usedDroneBay();
}

dgmpp_cubic_meter dgmpp_ship_get_total_drone_bay (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->totalDroneBay();
}

dgmpp_cubic_meter dgmpp_ship_get_used_fighter_hangar (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->usedFighterHangar();
}

dgmpp_cubic_meter dgmpp_ship_get_total_fighter_hangar (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->totalFighterHangar();
}

dgmpp_cubic_meter dgmpp_ship_get_cargo_capacity (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->cargoCapacity();
}

dgmpp_cubic_meter dgmpp_ship_get_ore_hold_capacity (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->oreHoldCapacity();
}

dgmpp_resistances dgmpp_ship_get_resistances (dgmpp_type_ptr ship) {
	return dgmpp_resistances_make(type_cast<Ship*>(ship)->resistances());
}

dgmpp_tank dgmpp_ship_get_tank (dgmpp_type_ptr ship) {
	return dgmpp_tank_make(type_cast<Ship*>(ship)->tank());
}

dgmpp_tank dgmpp_ship_get_effective_tank (dgmpp_type_ptr ship) {
	return dgmpp_tank_make(type_cast<Ship*>(ship)->effectiveTank());
}

dgmpp_tank dgmpp_ship_get_sustainable_tank (dgmpp_type_ptr ship) {
	return dgmpp_tank_make(type_cast<Ship*>(ship)->sustainableTank());
}

dgmpp_tank dgmpp_ship_get_effective_sustainable_tank (dgmpp_type_ptr ship) {
	return dgmpp_tank_make(type_cast<Ship*>(ship)->effectiveSustainableTank());
}

dgmpp_hit_points dgmpp_ship_get_hit_points (dgmpp_type_ptr ship) {
	return dgmpp_hit_points_make(type_cast<Ship*>(ship)->hitPoints());
}

dgmpp_hit_points dgmpp_ship_get_effective_hit_points (dgmpp_type_ptr ship) {
	return dgmpp_hit_points_make(type_cast<Ship*>(ship)->effectiveHitPoints());
}

dgmpp_damage_vector dgmpp_ship_get_turrets_volley (dgmpp_type_ptr ship) {
	return dgmpp_damage_vector_make(type_cast<Ship*>(ship)->turretsVolley());
}

dgmpp_damage_vector dgmpp_ship_get_launchers_volley (dgmpp_type_ptr ship) {
	return dgmpp_damage_vector_make(type_cast<Ship*>(ship)->launchersVolley());
}

dgmpp_damage_vector dgmpp_ship_get_drones_volley (dgmpp_type_ptr ship) {
	return dgmpp_damage_vector_make(type_cast<Ship*>(ship)->dronesVolley());
}

dgmpp_damage_per_second	dgmpp_ship_get_turrets_dps (dgmpp_type_ptr ship) {
	return dgmpp_ship_get_turrets_dps_v2(ship, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second	dgmpp_ship_get_launchers_dps (dgmpp_type_ptr ship) {
	return dgmpp_ship_get_launchers_dps_v2(ship, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second	dgmpp_ship_get_drones_dps (dgmpp_type_ptr ship) {
	return dgmpp_ship_get_drones_dps_v2(ship, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second dgmpp_ship_get_turrets_dps_v2 (dgmpp_type_ptr ship, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(type_cast<Ship*>(ship)->turretsDPS(hostile_target_make(target)));
}

dgmpp_damage_per_second dgmpp_ship_get_launchers_dps_v2 (dgmpp_type_ptr ship, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(type_cast<Ship*>(ship)->launchersDPS(hostile_target_make(target)));
}

dgmpp_damage_per_second dgmpp_ship_get_drones_dps_v2 (dgmpp_type_ptr ship, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(type_cast<Ship*>(ship)->dronesDPS(hostile_target_make(target)));
}

dgmpp_cubic_meter_per_second dgmpp_ship_get_miner_yield (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->minerYield() * 1s;
}

dgmpp_cubic_meter_per_second dgmpp_ship_get_drone_yield (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->droneYield() * 1s;
}

dgmpp_seconds dgmpp_ship_get_align_time (dgmpp_type_ptr ship) {
	return dgmpp_make_seconds(type_cast<Ship*>(ship)->alignTime());
}

dgmpp_astronomical_units_per_second dgmpp_ship_get_warp_speed (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->warpSpeed() * 1s;
}

dgmpp_astronomical_unit dgmpp_ship_get_max_warp_distance (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->maxWarpDistance();
}

dgmpp_meters_per_second dgmpp_ship_get_velocity (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->velocity() * 1s;
}

dgmpp_meter dgmpp_ship_get_signature_radius (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->signatureRadius();
}

dgmpp_kilogram dgmpp_ship_get_mass (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->mass();
}

dgmpp_cubic_meter dgmpp_ship_get_volume (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->volume();
}

dgmpp_multiplier dgmpp_ship_get_agility (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->agility();
}

dgmpp_meters_per_second dgmpp_ship_get_max_velocity_in_orbit (dgmpp_type_ptr ship, dgmpp_meter r) {
	return type_cast<Ship*>(ship)->maxVelocityInOrbit(r) * 1s;
}

dgmpp_meter dgmpp_ship_get_orbit_radius_with_transverse_velocity (dgmpp_type_ptr ship, dgmpp_meters_per_second v) {
	return type_cast<Ship*>(ship)->orbitRadiusWithTransverseVelocity(make_rate(v, 1s));
}

dgmpp_meter dgmpp_ship_get_orbit_radius_with_angular_velocity (dgmpp_type_ptr ship, dgmpp_radians_per_second v) {
	return type_cast<Ship*>(ship)->orbitRadiusWithAngularVelocity(make_rate(v, 1s));
}

size_t dgmpp_ship_get_max_targets (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->maxTargets();
}

dgmpp_meter dgmpp_ship_get_max_target_range (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->maxTargetRange();
}

dgmpp_points dgmpp_ship_get_scan_strength (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->scanStrength();
}

DGMPP_SCAN_TYPE dgmpp_ship_get_scan_type (dgmpp_type_ptr ship) {
	return static_cast<DGMPP_SCAN_TYPE>(type_cast<Ship*>(ship)->scanType());
}

dgmpp_meter dgmpp_ship_get_probe_size (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->probeSize();
}

dgmpp_millimeter dgmpp_ship_get_scan_resolution (dgmpp_type_ptr ship) {
	return type_cast<Ship*>(ship)->scanResolution();
}

dgmpp_giga_joule dgmpp_capacitor_get_capacity (dgmpp_capacitor_ptr capacitor) {
	return reinterpret_cast<dgmpp_capacitor_impl*>(capacitor)->capacitor->capacity();
}

dgmpp_seconds dgmpp_capacitor_get_recharge_time (dgmpp_capacitor_ptr capacitor) {
	return dgmpp_make_seconds(reinterpret_cast<dgmpp_capacitor_impl*>(capacitor)->capacitor->rechargeTime());
}

dgmpp_seconds dgmpp_capacitor_get_lasts_time (dgmpp_capacitor_ptr capacitor) {
	return dgmpp_make_seconds(reinterpret_cast<dgmpp_capacitor_impl*>(capacitor)->capacitor->lastsTime());
}

BOOL dgmpp_capacitor_is_stable (dgmpp_capacitor_ptr capacitor) {
	return reinterpret_cast<dgmpp_capacitor_impl*>(capacitor)->capacitor->isStable();
}

dgmpp_percent dgmpp_capacitor_get_stable_level (dgmpp_capacitor_ptr capacitor) {
	return reinterpret_cast<dgmpp_capacitor_impl*>(capacitor)->capacitor->stableLevel();
}

dgmpp_giga_joule_per_second dgmpp_capacitor_get_use (dgmpp_capacitor_ptr capacitor) {
	return reinterpret_cast<dgmpp_capacitor_impl*>(capacitor)->capacitor->use() * 1s;
}

dgmpp_giga_joule_per_second dgmpp_capacitor_get_recharge (dgmpp_capacitor_ptr capacitor) {
	return reinterpret_cast<dgmpp_capacitor_impl*>(capacitor)->capacitor->recharge() * 1s;
}
