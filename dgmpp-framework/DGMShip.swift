//
//  DGMShip.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMCapacitor: DGMObject {
	
	public var capacity: DGMGigaJoule {
		return dgmpp_capacitor_get_capacity(handle)
	}
	
	public var rechargeTime: TimeInterval {
		return dgmpp_capacitor_get_recharge(handle)
	}

	public var lastsTime: TimeInterval {
		return dgmpp_capacitor_get_lasts_time(handle)
	}

	public var isStable: Bool {
		return dgmpp_capacitor_is_stable(handle)
	}

	public var stableLevel: DGMPercent {
		return dgmpp_capacitor_get_stable_level(handle)
	}

	public var use: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_capacitor_get_use(handle))
	}

	public var recharge: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_capacitor_get_recharge(handle))
	}

}

public class DGMShip: DGMType {
	
	public enum ScanType: Int {
		case radar
		case ladar
		case magnetometric
		case gravimetric
		case multispectral
	}

	public enum RigSize: Int {
		case none = 0
		case small = 1
		case medium = 2
		case large = 3
		case xLarge = 4
	}
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_ship_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}
	
	public convenience init(_ other: DGMShip) {
		self.init(dgmpp_ship_copy(other.handle), owned: true)
	}

	public var name: String {
		get {
			return String(cString: dgmpp_ship_get_name(handle));
		}
		set {
			guard let string = newValue.cString(using: .utf8) else {return}
			dgmpp_ship_set_name(handle, string)
		}
	}
	
	public var raceID: DGMRaceID {
		return DGMRaceID(dgmpp_ship_get_race_id(handle)) ?? .none
	}
	
	public var supportedDroneCategories: [DGMCategoryID] {
		return DGMArray<Int>(dgmpp_ship_copy_supported_drone_categories(handle)).array.map {DGMCategoryID($0)}
	}
	
	public var rigSize: RigSize {
		return RigSize(dgmpp_ship_get_rig_size(handle)) ?? .none
	}
	
	public var factorReload: Bool {
		return dgmpp_ship_get_factor_reload(handle)
	}
	
	public var damagePattern: DGMDamageVector {
		get {
			return DGMDamageVector(dgmpp_ship_get_damage_pattern(handle))
		}
		set {
			dgmpp_ship_set_damage_pattern(handle, dgmpp_damage_vector(newValue))
		}
	}
	
	public func add(_ module: DGMModule, socket: Int = -1, ignoringRequirements: Bool = false) throws {
		guard dgmpp_ship_add_module_v2(handle, module.handle, Int32(socket), ignoringRequirements) else { throw DGMError.cannotFit(module)}
	}
	
	public func add(_ drone: DGMDrone, squadronTag: Int = -1) throws {
		guard dgmpp_ship_add_drone_v2(handle, drone.handle, Int32(squadronTag)) else { throw DGMError.cannotFit(drone)}
	}
	
	public func remove(_ module: DGMModule) {
		dgmpp_ship_remove_module(handle, module.handle)
	}
	
	public func remove(_ drone: DGMDrone) {
		dgmpp_ship_remove_drone(handle, drone.handle)
	}

	public func canFit(_ module: DGMModule) -> Bool {
		return dgmpp_ship_can_fit_module(handle, module.handle)
	}
	
	public func canFit(_ drone: DGMDrone) -> Bool {
		return dgmpp_ship_can_fit_drone(handle, drone.handle)
	}
	
	public var modules: [DGMModule] {
		return DGMArray<DGMModule>(dgmpp_ship_copy_modules(handle)).array
	}

	public var drones: [DGMDrone] {
		return DGMArray<DGMDrone>(dgmpp_ship_copy_drones(handle)).array
	}
	
	public func modules(slot: DGMModule.Slot) -> [DGMModule] {
		return DGMArray<DGMModule>(dgmpp_ship_copy_modules_slot(handle, DGMPP_MODULE_SLOT(slot))).array
	}
	
	public func totalDroneSquadron(_ squadron: DGMDrone.Squadron = .none) -> Int {
		return dgmpp_ship_get_total_drone_squadron(handle, DGMPP_DRONE_SQUADRON(squadron))
	}

	public func usedDroneSquadron(_ squadron: DGMDrone.Squadron = .none) -> Int {
		return dgmpp_ship_get_used_drone_squadron(handle, DGMPP_DRONE_SQUADRON(squadron))
	}

	public var totalFighterLaunchTubes: Int {
		return dgmpp_ship_get_total_fighter_launch_tubes(handle)
	}

	public var usedFighterLaunchTubes: Int {
		return dgmpp_ship_get_used_fighter_launch_tubes(handle)
	}

	public func totalSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_total_slots(handle, DGMPP_MODULE_SLOT(slot))
	}

	public func freeSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_free_slots(handle, DGMPP_MODULE_SLOT(slot))
	}

	public func usedSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_used_slots(handle, DGMPP_MODULE_SLOT(slot))
	}

	public func totalHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_total_hardpoints(handle, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	public func freeHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_free_hardpoints(handle, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	public func usedHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_used_hardpoints(handle, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	public var capacitor: DGMCapacitor {
		return DGMCapacitor(dgmpp_ship_get_capacitor(handle), owned: false)
	}
	
	public var usedCalibration: DGMCalibrationPoints {
		return dgmpp_ship_get_used_calibration(handle)
	}
	
	public var totalCalibration: DGMCalibrationPoints {
		return dgmpp_ship_get_total_calibration(handle)
	}
	
	public var usedPowerGrid: DGMGigaJoule {
		return dgmpp_ship_get_used_power_grid(handle)
	}
	
	public var totalPowerGrid: DGMGigaJoule {
		return dgmpp_ship_get_total_power_grid(handle)
	}
	
	public var usedCPU: DGMTeraflops {
		return dgmpp_ship_get_used_cpu(handle)
	}
	
	public var totalCPU: DGMTeraflops {
		return dgmpp_ship_get_total_cpu(handle)
	}
	
	public var usedDroneBandwidth: DGMMegabitsPerSecond {
		return dgmpp_ship_get_used_drone_bandwidth(handle)
	}
	
	public var totalDroneBandwidth: DGMMegabitsPerSecond {
		return dgmpp_ship_get_total_drone_bandwidth(handle)
	}
	
	public var usedDroneBay: DGMCubicMeter {
		return dgmpp_ship_get_used_drone_bay(handle)
	}
	
	public var totalDroneBay: DGMCubicMeter {
		return dgmpp_ship_get_total_drone_bay(handle)
	}
	
	public var usedFighterHangar: DGMCubicMeter {
		return dgmpp_ship_get_used_fighter_hangar(handle)
	}
	
	public var totalFighterHangar: DGMCubicMeter {
		return dgmpp_ship_get_total_fighter_hangar(handle)
	}
	
	public var cargoCapacity: DGMCubicMeter {
		return dgmpp_ship_get_cargo_capacity(handle)
	}
	
	public var oreHoldCapacity: DGMCubicMeter {
		return dgmpp_ship_get_ore_hold_capacity(handle)
	}
	
	public var resistances: DGMResistances {
		return DGMResistances(dgmpp_ship_get_resistances(handle))
	}
	
	public var tank: DGMTank {
		return DGMTank(dgmpp_ship_get_tank(handle))
	}
	
	public var effectiveTank: DGMTank {
		return DGMTank(dgmpp_ship_get_effective_tank(handle))
	}
	
	public var sustainableTank: DGMTank {
		return DGMTank(dgmpp_ship_get_sustainable_tank(handle))
	}
	
	public var effectiveSustainableTank: DGMTank {
		return DGMTank(dgmpp_ship_get_effective_sustainable_tank(handle))
	}

	public var hitPoints: DGMHitPoints {
		return DGMHitPoints(dgmpp_ship_get_hit_points(handle))
	}

	public var effectiveHitPoints: DGMHitPoints {
		return DGMHitPoints(dgmpp_ship_get_effective_hit_points(handle))
	}
	
	public var turretsVolley: DGMDamageVector {
		return DGMDamageVector(dgmpp_ship_get_turrets_dps(handle))
	}
	
	public var launchersVolley: DGMDamageVector {
		return DGMDamageVector(dgmpp_ship_get_launchers_volley(handle))
	}

	public var dronesVolley: DGMDamageVector {
		return DGMDamageVector(dgmpp_ship_get_drones_volley(handle))
	}
	
	public func turretsDPS(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_ship_get_turrets_dps_v2(handle, dgmpp_hostile_target(target))))
	}

	public func launchersDPS(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_ship_get_launchers_dps_v2(handle, dgmpp_hostile_target(target))))
	}

	public func dronesDPS(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_ship_get_drones_dps_v2(handle, dgmpp_hostile_target(target))))
	}

	public var minerYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_ship_get_miner_yield(handle))
	}

	public var droneYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_ship_get_drone_yield(handle))
	}
	
	public var alignTime: TimeInterval {
		return dgmpp_ship_get_align_time(handle)
	}

	public var warpSpeed: DGMAstronomicalUnitsPerSecond {
		return DGMAstronomicalUnitsPerSecond(dgmpp_ship_get_warp_speed(handle))
	}

	public var maxWarpDistance: DGMAstronomicalUnit {
		return dgmpp_ship_get_max_warp_distance(handle)
	}
	
	public var velocity: DGMMetersPerSecond {
		return DGMMetersPerSecond(dgmpp_ship_get_velocity(handle))
	}
	
	public var signatureRadius: DGMMeter {
		return dgmpp_ship_get_signature_radius(handle)
	}
	
	public var mass: DGMKilogram {
		return dgmpp_ship_get_mass(handle)
	}
	
	public var volume: DGMCubicMeter {
		return dgmpp_ship_get_volume(handle)
	}
	
	public var agility: DGMMultiplier {
		return dgmpp_ship_get_agility(handle)
	}
	
	public func maxVelocityInOrbit(_ radius: DGMMeter) -> DGMMetersPerSecond {
		return DGMMetersPerSecond(dgmpp_ship_get_max_velocity_in_orbit(handle, radius))
	}
	
	public func orbitRadius(transverseVelocity: DGMMetersPerSecond) -> DGMMeter {
		return dgmpp_ship_get_orbit_radius_with_transverse_velocity(handle, transverseVelocity.value)
	}

	public func orbitRadius(angularVelocity: DGMRadiansPerSecond) -> DGMMeter {
		return dgmpp_ship_get_orbit_radius_with_angular_velocity(handle, angularVelocity.value)
	}

	public var maxTargets: Int {
		return dgmpp_ship_get_max_targets(handle)
	}
	
	public var maxTargetRange: DGMMeter {
		return dgmpp_ship_get_max_target_range(handle)
	}
	
	public var scanStrength: DGMPoints {
		return dgmpp_ship_get_scan_strength(handle)
	}
	
	public var scanType: DGMShip.ScanType {
		return DGMShip.ScanType(dgmpp_ship_get_scan_type(handle)) ?? .multispectral
	}
	
	public var probeSize: DGMMeter {
		return dgmpp_ship_get_probe_size(handle)
	}
	
	public var scanResolution: DGMMillimeter {
		return dgmpp_ship_get_scan_resolution(handle)
	}
	

}
