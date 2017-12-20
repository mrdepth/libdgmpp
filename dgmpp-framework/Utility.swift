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

public typealias DGMGigaJoulePerSecond = Rate<DGMGigaJoule, Seconds>
public typealias DGMCubicMeterPerSecond = Rate<DGMCubicMeter, Seconds>
public typealias DGMRadiansPerSecond = Rate<DGMRadians, Seconds>
public typealias DGMMetersPerSecond = Rate<DGMMeter, Seconds>
public typealias DGMAstronomicalUnitsPerSecond = Rate<DGMAstronomicalUnit, Seconds>
public typealias DGMHPPerSecond = Rate<DGMHP, Seconds>
public typealias DGMFuelUnitsPerHour = Rate<Double, Hours>
public typealias DGMDamagePerSecond = Rate<DGMDamageVector, Seconds>

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
