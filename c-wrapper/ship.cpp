//
//  ship.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "ship.h"
#include "internal.h"

dgmpp_type dgmpp_ship_create (dgmpp_type_id type_id) {
	try {
        return new_handle(std::make_shared<Ship>(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_ship_copy (dgmpp_type ship) {
	try {
        return new_handle(std::make_shared<Ship>(*get<Ship>(ship)));
	}
	catch (...) {
		return nullptr;
	}
}

const char*	dgmpp_ship_get_name (dgmpp_type ship) {
    return get<Ship>(ship)->name().c_str();
}

void dgmpp_ship_set_name (dgmpp_type ship, const char* name) {
    get<Ship>(ship)->name(name);
}


dgmpp_array dgmpp_ship_copy_supported_drone_categories (dgmpp_type ship) {
    auto groups = get<Ship>(ship)->supportedDroneCategories();
    std::vector<dgmpp_group_id> result;
    std::transform(groups.begin(), groups.end(), std::back_inserter(result), [](const auto& i) {
        return static_cast<dgmpp_group_id>(i);
    });
    return dgmpp_make_array<dgmpp_group_id>(std::move(result));
}

DGMPP_RACE_ID dgmpp_ship_get_race_id (dgmpp_type ship) {
	return static_cast<DGMPP_RACE_ID>(get<Ship>(ship)->raceID());
}

DGMPP_RIG_SIZE dgmpp_ship_get_rig_size (dgmpp_type ship) {
    return static_cast<DGMPP_RIG_SIZE>(get<Ship>(ship)->rigSize());
}

dgmpp_damage_vector dgmpp_ship_get_damage_pattern (dgmpp_type ship) {
	return dgmpp_damage_vector_make(get<Ship>(ship)->damagePattern());
}

void dgmpp_ship_set_damage_pattern (dgmpp_type ship, dgmpp_damage_vector damage_pattern) {
    get<Ship>(ship)->damagePattern(damage_vector_make(damage_pattern));
}

dgmpp_bool dgmpp_ship_add_module (dgmpp_type ship, dgmpp_type module) {
	return dgmpp_ship_add_module_v2(ship, module, -1, false);
}

dgmpp_bool dgmpp_ship_add_module_v2 (dgmpp_type ship, dgmpp_type module, int socket, dgmpp_bool ignoring_requirements) {
	try {
        get<Ship>(ship)->add(get<Module>(module), socket, ignoring_requirements);
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_bool dgmpp_ship_add_drone (dgmpp_type ship, dgmpp_type drone) {
	return dgmpp_ship_add_drone_v2(ship, drone, -1);
}

dgmpp_bool dgmpp_ship_add_drone_v2 (dgmpp_type ship, dgmpp_type drone, int squadron_tag) {
	try {
        get<Ship>(ship)->add(get<Drone>(drone), squadron_tag);
		return true;
	}
	catch(...) {
		return false;
	}
}

void dgmpp_ship_remove_module (dgmpp_type ship, dgmpp_type module) {
	get<Ship>(ship)->remove(get<Module>(module).get());
}

void dgmpp_ship_remove_drone (dgmpp_type ship, dgmpp_type drone) {
    get<Ship>(ship)->remove(get<Drone>(drone).get());
}

dgmpp_bool dgmpp_ship_can_fit_module (dgmpp_type ship, dgmpp_type module) {
    return get<Ship>(ship)->canFit(get<Module>(module).get());
}

dgmpp_bool dgmpp_ship_can_fit_drone (dgmpp_type ship, dgmpp_type drone) {
    return get<Ship>(ship)->canFit(get<Drone>(drone).get());
}

dgmpp_array dgmpp_ship_copy_modules (dgmpp_type ship) {
    auto modules = get<Ship>(ship)->modules();
    std::vector<dgmpp_handle> result;
    std::transform(modules.begin(), modules.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    return dgmpp_make_array<dgmpp_handle>(std::move(result));
}

dgmpp_array dgmpp_ship_copy_drones (dgmpp_type ship) {
    auto drones = get<Ship>(ship)->drones();
    std::vector<dgmpp_handle> result;
    std::transform(drones.begin(), drones.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    return dgmpp_make_array<dgmpp_handle>(std::move(result));
}

dgmpp_array dgmpp_ship_copy_modules_slot (dgmpp_type ship, DGMPP_MODULE_SLOT slot) {
    auto modules = get<Ship>(ship)->modules(static_cast<Module::Slot>(slot));
    std::vector<dgmpp_handle> result;
    std::transform(modules.begin(), modules.end(), std::back_inserter(result), [](const auto& i) {
        return new_handle(i);
    });
    return dgmpp_make_array<dgmpp_handle>(std::move(result));
}

size_t dgmpp_ship_get_total_drone_squadron (dgmpp_type ship, DGMPP_DRONE_SQUADRON squadron) {
	return get<Ship>(ship)->totalDroneSquadron(static_cast<Drone::Squadron>(squadron));
}

size_t dgmpp_ship_get_used_drone_squadron (dgmpp_type ship, DGMPP_DRONE_SQUADRON squadron) {
	return get<Ship>(ship)->usedDroneSquadron(static_cast<Drone::Squadron>(squadron));
}

size_t dgmpp_ship_get_total_fighter_launch_tubes (dgmpp_type ship) {
	return get<Ship>(ship)->totalFighterLaunchTubes();
}

size_t dgmpp_ship_get_used_fighter_launch_tubes (dgmpp_type ship) {
	return get<Ship>(ship)->usedFighterLaunchTubes();
}

size_t dgmpp_ship_get_total_slots (dgmpp_type ship, DGMPP_MODULE_SLOT slot) {
	return get<Ship>(ship)->totalSlots(static_cast<Module::Slot>(slot));
}

size_t dgmpp_ship_get_free_slots (dgmpp_type ship, DGMPP_MODULE_SLOT slot) {
	return get<Ship>(ship)->freeSlots(static_cast<Module::Slot>(slot));
}

size_t dgmpp_ship_get_used_slots (dgmpp_type ship, DGMPP_MODULE_SLOT slot) {
	return get<Ship>(ship)->usedSlots(static_cast<Module::Slot>(slot));
}

size_t dgmpp_ship_get_total_hardpoints (dgmpp_type ship, DGMPP_MODULE_HARDPOINT hardpoint) {
	return get<Ship>(ship)->totalHardpoints(static_cast<Module::Hardpoint>(hardpoint));
}

size_t dgmpp_ship_get_free_hardpoints (dgmpp_type ship, DGMPP_MODULE_HARDPOINT hardpoint) {
	return get<Ship>(ship)->freeHardpoints(static_cast<Module::Hardpoint>(hardpoint));
}

size_t dgmpp_ship_get_used_hardpoints (dgmpp_type ship, DGMPP_MODULE_HARDPOINT hardpoint) {
	return get<Ship>(ship)->usedHardpoints(static_cast<Module::Hardpoint>(hardpoint));
}


dgmpp_capacitor dgmpp_ship_get_capacitor (dgmpp_type ship) {
	return &get<Ship>(ship)->capacitor();
}

dgmpp_calibration_points dgmpp_ship_get_used_calibration (dgmpp_type ship) {
	return get<Ship>(ship)->usedCalibration();
}

dgmpp_calibration_points dgmpp_ship_get_total_calibration (dgmpp_type ship) {
	return get<Ship>(ship)->totalCalibration();
}

dgmpp_giga_joule dgmpp_ship_get_used_power_grid (dgmpp_type ship) {
	return get<Ship>(ship)->usedPowerGrid();
}

dgmpp_giga_joule dgmpp_ship_get_total_power_grid (dgmpp_type ship) {
	return get<Ship>(ship)->totalPowerGrid();
}

dgmpp_teraflops dgmpp_ship_get_used_cpu (dgmpp_type ship) {
	return get<Ship>(ship)->usedCPU();
}

dgmpp_teraflops dgmpp_ship_get_total_cpu (dgmpp_type ship) {
	return get<Ship>(ship)->totalCPU();
}

dgmpp_megabits_per_second dgmpp_ship_get_used_drone_bandwidth (dgmpp_type ship) {
	return get<Ship>(ship)->usedDroneBandwidth();
}

dgmpp_megabits_per_second dgmpp_ship_get_total_drone_bandwidth (dgmpp_type ship) {
	return get<Ship>(ship)->totalDroneBandwidth();
}

dgmpp_cubic_meter dgmpp_ship_get_used_drone_bay (dgmpp_type ship) {
	return get<Ship>(ship)->usedDroneBay();
}

dgmpp_cubic_meter dgmpp_ship_get_total_drone_bay (dgmpp_type ship) {
	return get<Ship>(ship)->totalDroneBay();
}

dgmpp_cubic_meter dgmpp_ship_get_used_fighter_hangar (dgmpp_type ship) {
	return get<Ship>(ship)->usedFighterHangar();
}

dgmpp_cubic_meter dgmpp_ship_get_total_fighter_hangar (dgmpp_type ship) {
	return get<Ship>(ship)->totalFighterHangar();
}

dgmpp_cubic_meter dgmpp_ship_get_cargo_capacity (dgmpp_type ship) {
	return get<Ship>(ship)->cargoCapacity();
}

dgmpp_cubic_meter dgmpp_ship_get_special_hold_capacity (dgmpp_type ship) {
	return get<Ship>(ship)->specialHoldCapacity();
}

dgmpp_resistances dgmpp_ship_get_resistances (dgmpp_type ship) {
	return dgmpp_resistances_make(get<Ship>(ship)->resistances());
}

dgmpp_tank dgmpp_ship_get_tank (dgmpp_type ship) {
	return dgmpp_tank_make(get<Ship>(ship)->tank());
}

dgmpp_tank dgmpp_ship_get_effective_tank (dgmpp_type ship) {
	return dgmpp_tank_make(get<Ship>(ship)->effectiveTank());
}

dgmpp_tank dgmpp_ship_get_sustainable_tank (dgmpp_type ship) {
	return dgmpp_tank_make(get<Ship>(ship)->sustainableTank());
}

dgmpp_tank dgmpp_ship_get_effective_sustainable_tank (dgmpp_type ship) {
	return dgmpp_tank_make(get<Ship>(ship)->effectiveSustainableTank());
}

dgmpp_hit_points dgmpp_ship_get_hit_points (dgmpp_type ship) {
	return dgmpp_hit_points_make(get<Ship>(ship)->hitPoints());
}

dgmpp_hit_points dgmpp_ship_get_effective_hit_points (dgmpp_type ship) {
	return dgmpp_hit_points_make(get<Ship>(ship)->effectiveHitPoints());
}

dgmpp_damage_vector dgmpp_ship_get_turrets_volley (dgmpp_type ship) {
	return dgmpp_damage_vector_make(get<Ship>(ship)->turretsVolley());
}

dgmpp_damage_vector dgmpp_ship_get_launchers_volley (dgmpp_type ship) {
	return dgmpp_damage_vector_make(get<Ship>(ship)->launchersVolley());
}

dgmpp_damage_vector dgmpp_ship_get_drones_volley (dgmpp_type ship) {
	return dgmpp_damage_vector_make(get<Ship>(ship)->dronesVolley());
}

dgmpp_damage_per_second	dgmpp_ship_get_turrets_dps (dgmpp_type ship) {
	return dgmpp_ship_get_turrets_dps_v2(ship, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second	dgmpp_ship_get_launchers_dps (dgmpp_type ship) {
	return dgmpp_ship_get_launchers_dps_v2(ship, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second	dgmpp_ship_get_drones_dps (dgmpp_type ship) {
	return dgmpp_ship_get_drones_dps_v2(ship, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second dgmpp_ship_get_turrets_dps_v2 (dgmpp_type ship, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(get<Ship>(ship)->turretsDPS(hostile_target_make(target)));
}

dgmpp_damage_per_second dgmpp_ship_get_launchers_dps_v2 (dgmpp_type ship, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(get<Ship>(ship)->launchersDPS(hostile_target_make(target)));
}

dgmpp_damage_per_second dgmpp_ship_get_drones_dps_v2 (dgmpp_type ship, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(get<Ship>(ship)->dronesDPS(hostile_target_make(target)));
}

dgmpp_cubic_meter_per_second dgmpp_ship_get_miner_yield (dgmpp_type ship) {
	return get<Ship>(ship)->minerYield() * 1s;
}

dgmpp_cubic_meter_per_second dgmpp_ship_get_drone_yield (dgmpp_type ship) {
	return get<Ship>(ship)->droneYield() * 1s;
}

dgmpp_seconds dgmpp_ship_get_align_time (dgmpp_type ship) {
	return dgmpp_make_seconds(get<Ship>(ship)->alignTime());
}

dgmpp_astronomical_units_per_second dgmpp_ship_get_warp_speed (dgmpp_type ship) {
	return get<Ship>(ship)->warpSpeed() * 1s;
}

dgmpp_astronomical_unit dgmpp_ship_get_max_warp_distance (dgmpp_type ship) {
	return get<Ship>(ship)->maxWarpDistance();
}

dgmpp_meters_per_second dgmpp_ship_get_velocity (dgmpp_type ship) {
	return get<Ship>(ship)->velocity() * 1s;
}

dgmpp_meter dgmpp_ship_get_signature_radius (dgmpp_type ship) {
	return get<Ship>(ship)->signatureRadius();
}

dgmpp_kilogram dgmpp_ship_get_mass (dgmpp_type ship) {
	return get<Ship>(ship)->mass();
}

dgmpp_cubic_meter dgmpp_ship_get_volume (dgmpp_type ship) {
	return get<Ship>(ship)->volume();
}

dgmpp_multiplier dgmpp_ship_get_agility (dgmpp_type ship) {
	return get<Ship>(ship)->agility();
}

dgmpp_meters_per_second dgmpp_ship_get_max_velocity_in_orbit (dgmpp_type ship, dgmpp_meter r) {
	return get<Ship>(ship)->maxVelocityInOrbit(r) * 1s;
}

dgmpp_meter dgmpp_ship_get_orbit_radius_with_transverse_velocity (dgmpp_type ship, dgmpp_meters_per_second v) {
	return get<Ship>(ship)->orbitRadiusWithTransverseVelocity(make_rate(v, 1s));
}

dgmpp_meter dgmpp_ship_get_orbit_radius_with_angular_velocity (dgmpp_type ship, dgmpp_radians_per_second v) {
	return get<Ship>(ship)->orbitRadiusWithAngularVelocity(make_rate(v, 1s));
}

size_t dgmpp_ship_get_max_targets (dgmpp_type ship) {
	return get<Ship>(ship)->maxTargets();
}

dgmpp_meter dgmpp_ship_get_max_target_range (dgmpp_type ship) {
	return get<Ship>(ship)->maxTargetRange();
}

dgmpp_points dgmpp_ship_get_scan_strength (dgmpp_type ship) {
	return get<Ship>(ship)->scanStrength();
}

DGMPP_SCAN_TYPE dgmpp_ship_get_scan_type (dgmpp_type ship) {
	return static_cast<DGMPP_SCAN_TYPE>(get<Ship>(ship)->scanType());
}

dgmpp_meter dgmpp_ship_get_probe_size (dgmpp_type ship) {
	return get<Ship>(ship)->probeSize();
}

dgmpp_millimeter dgmpp_ship_get_scan_resolution (dgmpp_type ship) {
	return get<Ship>(ship)->scanResolution();
}

dgmpp_giga_joule dgmpp_capacitor_get_capacity (dgmpp_capacitor capacitor) {
    return reinterpret_cast<Capacitor*>(capacitor)->capacity();
}

dgmpp_seconds dgmpp_capacitor_get_recharge_time (dgmpp_capacitor capacitor) {
	return dgmpp_make_seconds(reinterpret_cast<Capacitor*>(capacitor)->rechargeTime());
}

dgmpp_seconds dgmpp_capacitor_get_lasts_time (dgmpp_capacitor capacitor) {
	return dgmpp_make_seconds(reinterpret_cast<Capacitor*>(capacitor)->lastsTime());
}

dgmpp_bool dgmpp_capacitor_is_stable (dgmpp_capacitor capacitor) {
	return reinterpret_cast<Capacitor*>(capacitor)->isStable();
}

dgmpp_percent dgmpp_capacitor_get_stable_level (dgmpp_capacitor capacitor) {
	return reinterpret_cast<Capacitor*>(capacitor)->stableLevel();
}

dgmpp_giga_joule_per_second dgmpp_capacitor_get_use (dgmpp_capacitor capacitor) {
	return reinterpret_cast<Capacitor*>(capacitor)->use() * 1s;
}

dgmpp_giga_joule_per_second dgmpp_capacitor_get_recharge (dgmpp_capacitor capacitor) {
	return reinterpret_cast<Capacitor*>(capacitor)->recharge() * 1s;
}
