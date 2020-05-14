//
//  DGMShip.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMCapacitor {
    private var handle: dgmpp_capacitor
    
    init(_ handle: dgmpp_capacitor) {
        self.handle = handle
    }
	
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
		return dgmpp_capacitor_is_stable(handle) != 0
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

public class DGMShip: DGMType, Codable {
	
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
	
    required init(_ handle: dgmpp_type) {
        super.init(handle)
    }

	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_ship_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type)
	}
	
	public convenience init(_ other: DGMShip) {
		self.init(dgmpp_ship_copy(other.handle))
	}

	public var name: String {
		get {
			return String(cString: dgmpp_ship_get_name(handle));
		}
		set {
			guard let string = newValue.cString(using: .utf8) else {return}
            willChange()
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
	
	public var damagePattern: DGMDamageVector {
		get {
			return DGMDamageVector(dgmpp_ship_get_damage_pattern(handle))
		}
		set {
            willChange()
			dgmpp_ship_set_damage_pattern(handle, dgmpp_damage_vector(newValue))
		}
	}
	
	public func add(_ module: DGMModule, socket: Int = -1, ignoringRequirements: Bool = false) throws {
        willChange()
		guard dgmpp_ship_add_module_v2(handle, module.handle, Int32(socket), ignoringRequirements ? 1 : 0) != 0 else { throw DGMError.cannotFit(module)}
	}
	
	public func add(_ drone: DGMDrone, squadronTag: Int = -1) throws {
        willChange()
		guard dgmpp_ship_add_drone_v2(handle, drone.handle, Int32(squadronTag)) != 0 else { throw DGMError.cannotFit(drone)}
	}
    
    public func add(_ cargo: DGMCargo) throws {
        willChange()
        guard dgmpp_ship_add_cargo(handle, cargo.handle) != 0 else { throw DGMError.cannotFit(cargo)}
    }
	
	public func remove(_ module: DGMModule) {
        willChange()
		dgmpp_ship_remove_module(handle, module.handle)
	}
	
	public func remove(_ drone: DGMDrone) {
        willChange()
		dgmpp_ship_remove_drone(handle, drone.handle)
	}

    public func remove(_ cargo: DGMCargo) {
        willChange()
        dgmpp_ship_remove_cargo(handle, cargo.handle)
    }

	public func canFit(_ module: DGMModule) -> Bool {
		return dgmpp_ship_can_fit_module(handle, module.handle) != 0
	}
	
	public func canFit(_ drone: DGMDrone) -> Bool {
		return dgmpp_ship_can_fit_drone(handle, drone.handle) != 0
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

    public var cargo: [DGMCargo] {
        return DGMArray<DGMCargo>(dgmpp_ship_copy_cargo(handle)).array
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
        let capacitor = dgmpp_ship_get_capacitor(handle)!
        return DGMCapacitor(capacitor)
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

    public var usedCargoCapacity: DGMCubicMeter {
        return dgmpp_ship_get_used_cargo_capacity(handle)
    }

	public var specialHoldCapacity: DGMCubicMeter {
		return dgmpp_ship_get_special_hold_capacity(handle)
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
		return DGMDamageVector(dgmpp_ship_get_turrets_volley(handle))
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
	

    public required init(from decoder: Decoder) throws {

		let container = try decoder.container(keyedBy: CodingKeys.self)
		let typeID = try container.decode(DGMTypeID.self, forKey: .typeID)

        guard let type = dgmpp_ship_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
        super.init(type)

        try decodeLoadout(from: decoder)
	}
    
    func decodeLoadout(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        
        let modules = try container.nestedContainer(keyedBy: DGMModule.Slot.self, forKey: .modules)
        try modules.allKeys.sorted {$0.rawValue > $1.rawValue}.map { slot -> [(DGMModule, Int)] in
            let array = try modules.nestedContainer(keyedBy: DGMSocketKey.self, forKey: slot)
            return try array.allKeys.map { (socket) -> (DGMModule, Int) in
                return (try array.decode(DGMModule.self, forKey: socket), socket.intValue!)
            }
            }.joined().forEach { (module, socket) in
                try add(module, socket: socket)
        }

        var drones = try container.nestedUnkeyedContainer(forKey: .drones)

        for _ in (0..<(drones.count ?? 0)) {
            do {
                let c = try drones.nestedContainer(keyedBy: AdditionalDroneKeys.self)
                let count = try c.decode(Int.self, forKey: .count)
                let squadronTag = try c.decode(Int.self, forKey: .squadronTag)
                for _ in 0..<count {
                    try add(c.decode(DGMDrone.self, forKey: .drone), squadronTag: squadronTag)
                }
            }
            catch {
            }
        }
        if let identifier = try container.decodeIfPresent(Int.self, forKey: .identifier) {
            self.identifier = identifier
        }
        
        try container.decode([DGMCargo].self, forKey: .cargo).forEach {
            try add($0)
        }
        name = try container.decode(String.self, forKey: .name)
    }
	
	public func encode(to encoder: Encoder) throws {
		var container = encoder.container(keyedBy: CodingKeys.self)
		try container.encode(typeID, forKey: .typeID)
		
		var modulesMap: [DGMModule.Slot: [DGMModule]] = [:]
		
		for module in self.modules {
			modulesMap[module.slot, default: []].append(module)
		}

		var modules = container.nestedContainer(keyedBy: DGMModule.Slot.self, forKey: .modules)
		for (key, value) in modulesMap {
			var array = modules.nestedContainer(keyedBy: DGMSocketKey.self, forKey: key)
			for module in value {
				try array.encode(module, forKey: DGMSocketKey(intValue: module.socket)!)
			}
		}
		
		
		var drones = container.nestedUnkeyedContainer(forKey: .drones)
		var dronesMap = [DGMTypeID: [Int: [DGMDrone]]]()
		self.drones.forEach { i in
			dronesMap[i.typeID, default: [:]][i.squadronTag, default: []].append(i)
		}
		try dronesMap.values.forEach {
			try $0.forEach { i in
				guard let drone = i.value.first else {return}
				var c = drones.nestedContainer(keyedBy: AdditionalDroneKeys.self)
				try c.encode(i.key, forKey: .squadronTag)
				try c.encode(i.value.count, forKey: .count)
				try c.encode(drone, forKey: .drone)
			}
		}
        
        try container.encode(cargo, forKey: .cargo)
		
		try container.encode(identifier, forKey: .identifier)
        try container.encode(name, forKey: .name)
	}
	
	enum CodingKeys: String, CodingKey {
        case name
		case typeID
		case modules
		case drones
		case identifier
        case cargo
	}
	
	enum AdditionalDroneKeys: String, CodingKey {
		case drone
		case squadronTag
		case count
	}
    
    override func sendChange() {
        super.sendChange()
        modules.forEach{
            $0.sendChange()
        }
        drones.forEach {
            $0.sendChange()
        }
        cargo.forEach {
            $0.sendChange()
        }
    }

}

extension DGMModule.Slot: CodingKey {
}

struct DGMSocketKey: CodingKey {
	var intValue: Int?
	var stringValue: String
	
	init?(intValue: Int) {
		self.intValue = intValue
		self.stringValue = "\(intValue)"
	}
	
	init?(stringValue: String) {
		guard let i = Int(stringValue) else {return nil}
		intValue = i
		self.stringValue = stringValue
	}
}
