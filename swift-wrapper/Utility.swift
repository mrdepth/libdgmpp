//
//  Utility.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public enum DGMError: Error {
	case typeNotFound(DGMTypeID)
	case cannotFit(DGMType)
	case invalidFacility(DGMTypeID)
	case notEnoughCommodities
	case invalidFormat
}

public typealias DGMTypeID = Int
public typealias DGMGroupID = Int
public typealias DGMCategoryID = Int
public typealias DGMAttributeID = Int
public typealias DGMSchematicID = Int
public typealias DGMGigaJoule = Double
public typealias DGMTeraflops = Double
public typealias DGMMegaWatts = Double
public typealias DGMCalibrationPoints = Double
public typealias DGMCubicMeter = Double
public typealias DGMMeter = Double
public typealias DGMMillimeter = Double
public typealias DGMMegabitsPerSecond = Double
public typealias DGMKilogram = Double
public typealias DGMPoints = Double
public typealias DGMHP = Double
public typealias DGMRadians = Double
public typealias DGMAstronomicalUnit = Double
public typealias DGMPercent = Double
public typealias DGMMultiplier = Double

public typealias DGMGigaJoulePerSecond = DGMRate<DGMGigaJoule, DGMSeconds>
public typealias DGMCubicMeterPerSecond = DGMRate<DGMCubicMeter, DGMSeconds>
public typealias DGMRadiansPerSecond = DGMRate<DGMRadians, DGMSeconds>
public typealias DGMMetersPerSecond = DGMRate<DGMMeter, DGMSeconds>
public typealias DGMAstronomicalUnitsPerSecond = DGMRate<DGMAstronomicalUnit, DGMSeconds>
public typealias DGMHPPerSecond = DGMRate<DGMHP, DGMSeconds>
public typealias DGMFuelUnitsPerHour = DGMRate<Double, DGMHours>
public typealias DGMDamagePerSecond = DGMRate<DGMDamageVector, DGMSeconds>

public enum DGMRaceID: Int {
	case none = 0
	case caldari = 1
	case minmatar = 2
	case amarr = 4
	case gallente = 8
}


public struct DGMDamageVector: Scalable {
	public var em: DGMHP
	public var thermal: DGMHP
	public var kinetic: DGMHP
	public var explosive: DGMHP
	
	public func scale(_ s: Double) -> DGMDamageVector {
		return DGMDamageVector(em: em * s, thermal: thermal * s, kinetic: kinetic * s, explosive: explosive * s)
	}
	
	public init (em: DGMHP, thermal: DGMHP, kinetic: DGMHP, explosive: DGMHP) {
		self.em = em
		self.thermal = thermal
		self.kinetic = kinetic
		self.explosive = explosive
	}
	
	public var total: Double {
		return em + kinetic + thermal + explosive
	}

	public static func + (lhs: DGMDamageVector, rhs: DGMDamageVector) -> DGMDamageVector {
		return DGMDamageVector(em: lhs.em + rhs.em, thermal: lhs.thermal + rhs.thermal, kinetic: lhs.kinetic + rhs.kinetic, explosive: lhs.explosive + rhs.explosive)
	}

	public static func - (lhs: DGMDamageVector, rhs: DGMDamageVector) -> DGMDamageVector {
		return DGMDamageVector(em: lhs.em - rhs.em, thermal: lhs.thermal - rhs.thermal, kinetic: lhs.kinetic - rhs.kinetic, explosive: lhs.explosive - rhs.explosive)
	}

	public static let omni = DGMDamageVector(em: 0.25, thermal: 0.25, kinetic: 0.25, explosive: 0.25)
	
}

public struct DGMTank {
	public var passiveShield: DGMHPPerSecond
	public var shieldRepair: DGMHPPerSecond
	public var armorRepair: DGMHPPerSecond
	public var hullRepair: DGMHPPerSecond
	
	init(_ tank: dgmpp_tank) {
		passiveShield = DGMHPPerSecond(tank.passive_shield)
		shieldRepair = DGMHPPerSecond(tank.shield_repair)
		armorRepair = DGMHPPerSecond(tank.armor_repair)
		hullRepair = DGMHPPerSecond(tank.hull_repair)
	}
}

public struct DGMHostileTarget {
	public var angularVelocity: DGMRadiansPerSecond = DGMRadiansPerSecond(0)
	public var velocity: DGMMetersPerSecond = DGMMetersPerSecond(0)
	public var signature: DGMMeter = 0
	public var range: DGMMeter = 0
	
	public static let `default` = DGMHostileTarget(dgmpp_hostile_target_default)
	
	public init (angularVelocity: DGMRadiansPerSecond, velocity: DGMMetersPerSecond, signature: DGMMeter, range: DGMMeter) {
		self.angularVelocity = angularVelocity
		self.velocity = velocity
		self.signature = signature
		self.range = range
	}

}

public struct DGMResistances {
	public struct Layer {
		public var em: DGMPercent
		public var thermal: DGMPercent
		public var kinetic: DGMPercent
		public var explosive: DGMPercent
	}
	
	public var shield: Layer
	public var armor: Layer
	public var hull: Layer
}

extension DGMDamageVector {
	public init (_ resistances: DGMResistances.Layer) {
		em = resistances.em
		thermal = resistances.thermal
		kinetic = resistances.kinetic
		explosive = resistances.explosive
	}
}

public struct DGMHitPoints {
	public var shield: DGMHP
	public var armor: DGMHP
	public var hull: DGMHP
}

public struct DGMCommodity {
	public enum Tier: Int {
		case unknown = -1
		case raw
		case tier1
		case tier2
		case tier3
		case tier4
	}
	public var typeID: DGMTypeID
	public var tier: Tier;
	public var volume: DGMCubicMeter;
	public var quantity: Int;
	public var total: DGMCubicMeter {
		return volume * DGMCubicMeter(quantity)
	}
	
	public init(typeID: DGMTypeID, quantity: Int) throws {
		var commodity = dgmpp_commodity()
		guard dgmpp_commodity_create(dgmpp_type_id(typeID), quantity, &commodity) != 0 else { throw DGMError.typeNotFound(typeID)}
		self.init(commodity)
	}
}

public struct DGMProductionCycle{
	public var start: Date;
	public var duration: TimeInterval;
	public var end: Date {
		return start.addingTimeInterval(duration)
	}
	
	public var yield: DGMCommodity;
	public var waste: DGMCommodity;
};

public struct DGMRoute {
	public var from: DGMFacility
	public var to: DGMFacility
	public var commodity: DGMCommodity
	
	public init(from: DGMFacility, to: DGMFacility, commodity: DGMCommodity) {
		self.from = from
		self.to = to
		self.commodity = commodity
	}
}

public struct DGMVersion {
	public struct SDE {
		public var build: Int
		public var version: String
	}

	
	public var major: Int
	public var minor: Int
	public var sde: SDE
	
	public static let current: DGMVersion = {
		let version = dgmpp_get_version()
		return DGMVersion(major: version.major, minor: version.minor, sde: DGMVersion.SDE(build: version.sde.build, version: String(cString: version.sde.version)))
	}()
}

extension DGMShip {
	public convenience init(uniformString: String) throws {
		
		let components = uniformString.components(separatedBy: "|")
		guard components.count == 3 else {throw DGMError.invalidFormat}
		guard let typeID = DGMTypeID(components[0]) else {throw DGMError.invalidFormat}
		
		try self.init(typeID: typeID)
		
		var modules = [DGMModule.Slot: [DGMModule]]()
		
		try components[1].components(separatedBy: ";").forEach { row in
			let components = row.components(separatedBy: ":")
			guard components.count == 3 else {return}
			guard let typeID = Int(components[0]) else {return}
			
			let chargeID = Int(components[1])
			let count = Int(components[2]) ?? 1
			
			for _ in 0..<count {
				let module = try DGMModule(typeID: typeID)
				if let chargeID = chargeID {
					try module.setCharge(DGMCharge(typeID: chargeID))
				}
				modules[module.slot, default : []].append(module)
			}
		}
		try modules.sorted { $0.key.rawValue > $1.key.rawValue }.forEach {
			try $0.value.forEach { i in
				try add(i)
				i.state = .active
				
			}
		}
		
		try components[2].components(separatedBy: ";").forEach { row in
			let components = row.components(separatedBy: ":")
			guard components.count == 2 else {return}
			guard let typeID = Int(components[0]) else {return}
			let count = Int(components[1]) ?? 1
			for _ in 0..<count {
				try add(DGMDrone(typeID: typeID))
			}
		}
	}
	
	public var uniformString: String {
		var string = "\(typeID)|"
		var modulesMap = [DGMTypeID: [DGMTypeID: Int]]()
		
		for module in modules {
			modulesMap[module.typeID, default: [:]][module.charge?.typeID ?? 0, default: 0] += 1
		}
		string += modulesMap.sorted { $0.key < $1.key }
			.map { (key, value) -> [String] in
				return value.sorted {$0.key < $1.key } .map { $0.key == 0 ? "\(key)::\($0.value)" : "\(key):\($0.key):\($0.value)" }
			}.joined().joined(separator: ";")
		
		var dronesMap = [DGMTypeID: Int]()
		drones.filter {$0.isActive}.forEach {
			dronesMap[$0.typeID, default: 0] += 1
		}
		
		string += "|" + dronesMap.sorted {$0.key < $1.key}.map {"\($0.key):\($0.value)"}.joined(separator: ";")
		return string
	}
	
	public convenience init(dna: String) throws {
		let components = dna.components(separatedBy: ":")
		guard !components.isEmpty else {throw DGMError.invalidFormat}
		guard let typeID = DGMTypeID(components[0]) else {throw DGMError.invalidFormat}
		
		try self.init(typeID: typeID)

		var modules = [DGMModule]()
		var charges = [DGMCharge]()

		components.suffix(from: 1).forEach { line in
			let c = line.components(separatedBy: ";")
			guard !c.isEmpty else {return}
			guard let typeID = DGMTypeID(c[0]) else {return}
			let count = c.count > 1 ? Int(c[1]) ?? 1 : 1
			
			
			do {
				for _ in 0..<count {
					let module = try DGMModule(typeID: typeID)
					try add(module)
					if !module.chargeGroups.isEmpty {
						modules.append(module)
					}
				}
			}
			catch {
				do {
					for _ in 0..<count {
						let drone = try DGMDrone(typeID: typeID)
						try add(drone)
					}
				}
				catch {
					do {
						charges.append(try DGMCharge(typeID: typeID))
					}
					catch {
						
					}
				}
			}
		}
		
		for module in modules {
			for charge in charges {
				do {
					try module.setCharge(DGMCharge(charge))
					break
				}
				catch {
					
				}
			}
		}

	}
	
	public var dna: String {
		var modules = [DGMModule.Slot: [DGMTypeID: Int]]()
		var charges = Set<DGMTypeID>()
		var drones = [DGMTypeID: Int]()
		
		self.modules.forEach {
			modules[$0.slot, default: [:]][$0.typeID, default: 0] += 1
			if let charge = $0.charge {
				charges.insert(charge.typeID)
			}
		}
		self.drones.forEach { drones[$0.typeID, default: 0] += 1 }
		
		let slots: [DGMModule.Slot] = [.subsystem, .hi, .med, .low, .rig, .service]
		var array = slots.flatMap { modules[$0] }.joined().map {"\($0.key);\($0.value)"}
		array.append(contentsOf: drones.map {"\($0.key);\($0.value)"})
		array.append(contentsOf: charges.map {"\($0);1"})
		
		return "\(typeID):\(array.joined(separator: ":")):"
	}
}


