//
//  DGMShip.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMCapacitor {
	private var opaque: dgmpp_capacitor_ptr
	
	init(_ opaque: dgmpp_capacitor_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_release(opaque)
	}
	
	public var capacity: DGMGigaJoule {
		return dgmpp_capacitor_get_capacity(opaque)
	}
	
	public var rechargeTime: TimeInterval {
		return dgmpp_capacitor_get_recharge(opaque)
	}

	public var lastsTime: TimeInterval {
		return dgmpp_capacitor_get_lasts_time(opaque)
	}

	public var isStable: Bool {
		return dgmpp_capacitor_is_stable(opaque)
	}

	public var stableLevel: DGMPercent {
		return dgmpp_capacitor_get_stable_level(opaque)
	}

	public var use: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_capacitor_get_use(opaque))
	}

	public var recharge: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_capacitor_get_recharge(opaque))
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
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}

	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_ship_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
	
	public var name: String {
		get {
			return String(cString: dgmpp_ship_get_name(opaque));
		}
		set {
			guard let string = newValue.cString(using: .utf8) else {return}
			dgmpp_ship_set_name(opaque, string)
		}
	}
	
	public var raceID: DGMRaceID {
		return DGMRaceID(dgmpp_ship_get_race_id(opaque)) ?? .none
	}
	
	public var supportedDroneCategories: [DGMCategoryID] {
		return DGMArray<Int>(dgmpp_ship_get_supported_drone_categories(opaque)).array.map {DGMCategoryID($0)}
	}
	
	public var rigSize: RigSize {
		return RigSize(dgmpp_ship_get_rig_size(opaque)) ?? .none
	}
	
	public var damagePattern: DGMDamageVector {
		get {
			return DGMDamageVector(dgmpp_ship_get_damage_pattern(opaque))
		}
		set {
			dgmpp_ship_set_damage_pattern(opaque, dgmpp_damage_vector(newValue))
		}
	}
	
	public func add(_ module: DGMModule, socket: Int = -1, ignoringRequirements: Bool = false) throws {
		guard dgmpp_ship_add_module_v2(opaque, module.opaque, Int32(socket), ignoringRequirements) else { throw DGMError.cannotFit(module)}
	}
	
	public func add(_ drone: DGMDrone, squadronTag: Int = -1) throws {
		guard dgmpp_ship_add_drone_v2(opaque, drone.opaque, Int32(squadronTag)) else { throw DGMError.cannotFit(drone)}
	}
	
	public func remove(_ module: DGMModule) {
		dgmpp_ship_remove_module(opaque, module.opaque)
	}
	
	public func remove(_ drone: DGMDrone) {
		dgmpp_ship_remove_drone(opaque, drone.opaque)
	}

	public func canFit(_ module: DGMModule) -> Bool {
		return dgmpp_ship_can_fit_module(opaque, module.opaque)
	}
	
	public func canFit(_ drone: DGMDrone) -> Bool {
		return dgmpp_ship_can_fit_drone(opaque, drone.opaque)
	}
	
	public var modules: [DGMModule] {
		return DGMArray<DGMModule>(dgmpp_ship_get_modules(opaque)).array
	}

	public var drones: [DGMDrone] {
		return DGMArray<DGMDrone>(dgmpp_ship_get_drones(opaque)).array
	}
	
	public func modules(slot: DGMModule.Slot) -> [DGMModule] {
		return DGMArray<DGMModule>(dgmpp_ship_get_modules_slot(opaque, DGMPP_MODULE_SLOT(slot))).array
	}
	
	public var area: DGMArea? {
		get {
			guard let area = dgmpp_ship_get_area(opaque) else {return nil}
			return DGMArea(area)
		}
		set {
			dgmpp_ship_set_area(opaque, newValue?.opaque)
		}
	}
	
	public func totalDroneSquadron(_ squadron: DGMDrone.Squadron = .none) -> Int {
		return dgmpp_ship_get_total_drone_squadron(opaque, DGMPP_DRONE_SQUADRON(squadron))
	}

	public func usedDroneSquadron(_ squadron: DGMDrone.Squadron = .none) -> Int {
		return dgmpp_ship_get_used_drone_squadron(opaque, DGMPP_DRONE_SQUADRON(squadron))
	}

	public var totalFighterLaunchTubes: Int {
		return dgmpp_ship_get_total_fighter_launch_tubes(opaque)
	}

	public var usedFighterLaunchTubes: Int {
		return dgmpp_ship_get_used_fighter_launch_tubes(opaque)
	}

	public func totalSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_total_slots(opaque, DGMPP_MODULE_SLOT(slot))
	}

	public func freeSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_free_slots(opaque, DGMPP_MODULE_SLOT(slot))
	}

	public func usedSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_used_slots(opaque, DGMPP_MODULE_SLOT(slot))
	}

	public func totalHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_total_hardpoints(opaque, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	public func freeHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_free_hardpoints(opaque, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	public func usedHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_used_hardpoints(opaque, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	public var capacitor: DGMCapacitor {
		return DGMCapacitor(dgmpp_ship_get_capacitor(opaque))
	}
	
	public var usedCalibration: DGMCalibrationPoints {
		return dgmpp_ship_get_used_calibration(opaque)
	}
	
	public var totalCalibration: DGMCalibrationPoints {
		return dgmpp_ship_get_total_calibration(opaque)
	}
	
	public var usedPowerGrid: DGMGigaJoule {
		return dgmpp_ship_get_used_power_grid(opaque)
	}
	
	public var totalPowerGrid: DGMGigaJoule {
		return dgmpp_ship_get_total_power_grid(opaque)
	}
	
	public var usedCPU: DGMTeraflops {
		return dgmpp_ship_get_used_cpu(opaque)
	}
	
	public var totalCPU: DGMTeraflops {
		return dgmpp_ship_get_total_cpu(opaque)
	}
	
	public var usedDroneBandwidth: DGMMegabitsPerSecond {
		return dgmpp_ship_get_used_drone_bandwidth(opaque)
	}
	
	public var totalDroneBandwidth: DGMMegabitsPerSecond {
		return dgmpp_ship_get_total_drone_bandwidth(opaque)
	}
	
	public var usedDroneBay: DGMCubicMeter {
		return dgmpp_ship_get_used_drone_bay(opaque)
	}
	
	public var totalDroneBay: DGMCubicMeter {
		return dgmpp_ship_get_total_drone_bay(opaque)
	}
	
	public var usedFighterHangar: DGMCubicMeter {
		return dgmpp_ship_get_used_fighter_hangar(opaque)
	}
	
	public var totalFighterHangar: DGMCubicMeter {
		return dgmpp_ship_get_total_fighter_hangar(opaque)
	}
	
	public var cargoCapacity: DGMCubicMeter {
		return dgmpp_ship_get_cargo_capacity(opaque)
	}
	
	public var oreHoldCapacity: DGMCubicMeter {
		return dgmpp_ship_get_ore_hold_capacity(opaque)
	}
	
	public var resistances: DGMResistances {
		return DGMResistances(dgmpp_ship_get_resistances(opaque))
	}
	
	public var tank: DGMTank {
		return DGMTank(dgmpp_ship_get_tank(opaque))
	}
	
	public var effectiveTank: DGMTank {
		return DGMTank(dgmpp_ship_get_effective_tank(opaque))
	}
	
	public var sustainableTank: DGMTank {
		return DGMTank(dgmpp_ship_get_sustainable_tank(opaque))
	}
	
	public var effectiveSustainableTank: DGMTank {
		return DGMTank(dgmpp_ship_get_effective_sustainable_tank(opaque))
	}

	public var hitPoints: DGMHitPoints {
		return DGMHitPoints(dgmpp_ship_get_hit_points(opaque))
	}

	public var effectiveHitPoints: DGMHitPoints {
		return DGMHitPoints(dgmpp_ship_get_effective_hit_points(opaque))
	}
	
	public var turretsVolley: DGMDamageVector {
		return DGMDamageVector(dgmpp_ship_get_turrets_dps(opaque))
	}
	
	public var launchersVolley: DGMDamageVector {
		return DGMDamageVector(dgmpp_ship_get_launchers_volley(opaque))
	}

	public var dronesVolley: DGMDamageVector {
		return DGMDamageVector(dgmpp_ship_get_drones_volley(opaque))
	}
	
	public func turretsDPS(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_ship_get_turrets_dps_v2(opaque, dgmpp_hostile_target(target))))
	}

	public func launchersDPS(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_ship_get_launchers_dps_v2(opaque, dgmpp_hostile_target(target))))
	}

	public func dronesDPS(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_ship_get_drones_dps_v2(opaque, dgmpp_hostile_target(target))))
	}

	public var minerYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_ship_get_miner_yield(opaque))
	}

	public var droneYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_ship_get_drone_yield(opaque))
	}
	
	public var alignTime: TimeInterval {
		return dgmpp_ship_get_align_time(opaque)
	}

	public var warpSpeed: DGMAstronomicalUnitsPerSecond {
		return DGMAstronomicalUnitsPerSecond(dgmpp_ship_get_warp_speed(opaque))
	}

	public var maxWarpDistance: DGMAstronomicalUnit {
		return dgmpp_ship_get_max_warp_distance(opaque)
	}
	
	public var velocity: DGMMetersPerSecond {
		return DGMMetersPerSecond(dgmpp_ship_get_velocity(opaque))
	}
	
	public var signatureRadius: DGMMeter {
		return dgmpp_ship_get_signature_radius(opaque)
	}
	
	public var mass: DGMKilogram {
		return dgmpp_ship_get_mass(opaque)
	}
	
	public var volume: DGMCubicMeter {
		return dgmpp_ship_get_volume(opaque)
	}
	
	public var agility: DGMMultiplier {
		return dgmpp_ship_get_agility(opaque)
	}
	
	public func maxVelocityInOrbit(_ radius: DGMMeter) -> DGMMetersPerSecond {
		return DGMMetersPerSecond(dgmpp_ship_get_max_velocity_in_orbit(opaque, radius))
	}
	
	public func orbitRadius(transverseVelocity: DGMMetersPerSecond) -> DGMMeter {
		return dgmpp_ship_get_orbit_radius_with_transverse_velocity(opaque, transverseVelocity.value)
	}

	public func orbitRadius(angularVelocity: DGMRadiansPerSecond) -> DGMMeter {
		return dgmpp_ship_get_orbit_radius_with_angular_velocity(opaque, angularVelocity.value)
	}

	public var maxTargets: Int {
		return dgmpp_ship_get_max_targets(opaque)
	}
	
	public var maxTargetRange: DGMMeter {
		return dgmpp_ship_get_max_target_range(opaque)
	}
	
	public var scanStrength: DGMPoints {
		return dgmpp_ship_get_scan_strength(opaque)
	}
	
	public var scanType: DGMShip.ScanType {
		return DGMShip.ScanType(dgmpp_ship_get_scan_type(opaque)) ?? .multispectral
	}
	
	public var probeSize: DGMMeter {
		return dgmpp_ship_get_probe_size(opaque)
	}
	
	public var scanResolution: DGMMillimeter {
		return dgmpp_ship_get_scan_resolution(opaque)
	}
	

}

extension DGMCapacitor: Hashable {
	
	public var hashValue: Int {
		return dgmpp_get_hash(opaque)
	}
	
	public static func ==(lhs: DGMCapacitor, rhs: DGMCapacitor) -> Bool {
		return lhs.hashValue == rhs.hashValue
	}
}

