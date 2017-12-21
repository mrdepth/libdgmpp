//
//  Utility.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public enum DGMError: Error {
	case typeNotFound(DGMTypeID)
	case cannotFit(DGMType)
	case invalidFacility(DGMTypeID)
	case NotEnoughCommodities
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
}
