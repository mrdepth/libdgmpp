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
		dgmpp_type_free(opaque)
	}
	
	var capacity: DGMGigaJoule {
		return dgmpp_capacitor_get_capacity(opaque)
	}
	
	var rechargeTime: TimeInterval {
		return dgmpp_capacitor_get_recharge(opaque)
	}

	var lastsTime: TimeInterval {
		return dgmpp_capacitor_get_lasts_time(opaque)
	}

	var isStable: Bool {
		return dgmpp_capacitor_is_stable(opaque)
	}

	var stableLevel: DGMPercent {
		return dgmpp_capacitor_get_stable_level(opaque)
	}

	var use: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_capacitor_get_use(opaque))
	}

	var recharge: DGMGigaJoulePerSecond {
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
	
	override init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}

	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_ship_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
	
	var raceID: DGMRaceID {
		return DGMRaceID(dgmpp_ship_get_race_id(opaque)) ?? .none
	}
	
	var supportedDroneCategories: [DGMCategoryID] {
		return dgmpp_ship_get_supported_drone_categories(opaque).array.map {DGMCategoryID($0)}
	}
	
	var rigSize: RigSize {
		return RigSize(dgmpp_ship_get_rig_size(opaque)) ?? .none
	}
	
	var damagePattern: DGMDamageVector {
		get {
			return DGMDamageVector(dgmpp_ship_get_damage_pattern(opaque))
		}
		set {
			dgmpp_ship_set_damage_pattern(opaque, dgmpp_damage_vector(newValue))
		}
	}
	
	func add(_ module: DGMModule, socket: Int = -1, ignoringRequirements: Bool = false) throws {
		guard dgmpp_ship_add_module_v2(opaque, module.opaque, Int32(socket), ignoringRequirements) else { throw DGMError.cannotFit(module)}
	}
	
	func add(_ drone: DGMDrone, squadronTag: Int = -1) throws {
		guard dgmpp_ship_add_drone_v2(opaque, drone.opaque, Int32(squadronTag)) else { throw DGMError.cannotFit(drone)}
	}
	
	func remove(_ module: DGMModule) {
		dgmpp_ship_remove_module(opaque, module.opaque)
	}
	
	func remove(_ drone: DGMDrone) {
		dgmpp_ship_remove_drone(opaque, drone.opaque)
	}

	func canFit(_ module: DGMModule) -> Bool {
		return dgmpp_ship_can_fit_module(opaque, module.opaque)
	}
	
	func canFit(_ drone: DGMDrone) -> Bool {
		return dgmpp_ship_can_fit_drone(opaque, drone.opaque)
	}
	
	var modules: [DGMModule] {
		return dgmpp_ship_get_modules(opaque).array.map {DGMModule($0.opaque)}
	}

	var drones: [DGMDrone] {
		return dgmpp_ship_get_drones(opaque).array.map {DGMDrone($0.opaque)}
	}
	
	func modules(slot: DGMModule.Slot) -> [DGMModule] {
		return dgmpp_ship_get_modules_slot(opaque, DGMPP_MODULE_SLOT(slot)).array.map {DGMModule($0.opaque)}
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
	
	func totalDroneSquadron(_ squadron: DGMDrone.Squadron = .none) -> Int {
		return dgmpp_ship_get_total_drone_squadron(opaque, DGMPP_DRONE_SQUADRON(squadron))
	}

	func usedDroneSquadron(_ squadron: DGMDrone.Squadron = .none) -> Int {
		return dgmpp_ship_get_used_drone_squadron(opaque, DGMPP_DRONE_SQUADRON(squadron))
	}

	var totalFighterLaunchTubes: Int {
		return dgmpp_ship_get_total_fighter_launch_tubes(opaque)
	}

	var usedFighterLaunchTubes: Int {
		return dgmpp_ship_get_used_fighter_launch_tubes(opaque)
	}

	func totalSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_total_slots(opaque, DGMPP_MODULE_SLOT(slot))
	}

	func freeSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_free_slots(opaque, DGMPP_MODULE_SLOT(slot))
	}

	func usedSlots(_ slot: DGMModule.Slot) -> Int {
		return dgmpp_ship_get_used_slots(opaque, DGMPP_MODULE_SLOT(slot))
	}

	func totalHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_total_hardpoints(opaque, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	func freeHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_free_hardpoints(opaque, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	func usedHardpoints(_ hardpoint: DGMModule.Hardpoint) -> Int {
		return dgmpp_ship_get_used_hardpoints(opaque, DGMPP_MODULE_HARDPOINT(hardpoint))
	}

	var capacitor: DGMCapacitor {
		return DGMCapacitor(dgmpp_ship_get_capacitor(opaque))
	}
	
	var usedCalibration: DGMCalibrationPoints {
		return dgmpp_ship_get_used_calibration(opaque)
	}
	
	var totalCalibration: DGMCalibrationPoints {
		return dgmpp_ship_get_total_calibration(opaque)
	}
	
	var usedPowerGrid: DGMGigaJoule {
		return dgmpp_ship_get_used_power_grid(opaque)
	}
	
	var totalPowerGrid: DGMGigaJoule {
		return dgmpp_ship_get_total_power_grid(opaque)
	}
	
	var usedCPU: DGMTeraflops {
		return dgmpp_ship_get_used_cpu(opaque)
	}
	
	var totalCPU: DGMTeraflops {
		return dgmpp_ship_get_total_cpu(opaque)
	}
	
	var usedDroneBandwidth: DGMMegabitsPerSecond {
		return dgmpp_ship_get_used_drone_bandwidth(opaque)
	}
	
	var totalDroneBandwidth: DGMMegabitsPerSecond {
		return dgmpp_ship_get_total_drone_bandwidth(opaque)
	}
	
	var usedDroneBay: DGMCubicMeter {
		return dgmpp_ship_get_used_drone_bay(opaque)
	}
	
	var totalDroneBay: DGMCubicMeter {
		return dgmpp_ship_get_total_drone_bay(opaque)
	}
	
	var usedFighterHangar: DGMCubicMeter {
		return dgmpp_ship_get_used_fighter_hangar(opaque)
	}
	
	var totalFighterHangar: DGMCubicMeter {
		return dgmpp_ship_get_total_fighter_hangar(opaque)
	}
	
	var cargoCapacity: DGMCubicMeter {
		return dgmpp_ship_get_cargo_capacity(opaque)
	}
	
	var oreHoldCapacity: DGMCubicMeter {
		return dgmpp_ship_get_ore_hold_capacity(opaque)
	}
	
	var resistances: DGMResistances {
		return DGMResistances(dgmpp_ship_get_resistances(opaque))
	}
	
	var tank: DGMTank {
		return DGMTank(dgmpp_ship_get_tank(opaque))
	}
	
	var effectiveTank: DGMTank {
		return DGMTank(dgmpp_ship_get_effective_tank(opaque))
	}
	
	var sustainableTank: DGMTank {
		return DGMTank(dgmpp_ship_get_sustainable_tank(opaque))
	}
	
	var effectiveSustainableTank: DGMTank {
		return DGMTank(dgmpp_ship_get_effective_sustainable_tank(opaque))
	}

	var hitPoints: DGMHitPoints {
		return DGMHitPoints(dgmpp_ship_get_hit_points(opaque))
	}

	var effectiveHitPoints: DGMHitPoints {
		return DGMHitPoints(dgmpp_ship_get_effective_hit_points(opaque))
	}


}
