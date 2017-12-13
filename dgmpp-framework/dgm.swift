//
//  dgm.swift
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

import Foundation

public protocol TimeRate {
	typealias Value = Int
	var value: Value {get set}
	static var rate: (Int, Int) {get}
}

public extension TimeRate {
}

public struct Seconds: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}
	
	public static let rate = (1, 1)
}

public struct Milliseconds: TimeRate {
	public var value: Value

	public init(_ value: Value) {
		self.value = value
	}

	public static let rate = (1, 1000)
}

public struct Minutes: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}

	public static let rate = (60, 1)
}

public struct Hours: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}

	public static let rate = (3600, 1)
}

public protocol Scalable {
	func scale(_ s: Double) -> Self
}

extension Int: Scalable {
	public func scale(_ s: Double) -> Int {
		return self * Int(s)
	}
}

extension Double: Scalable {
	public func scale(_ s: Double) -> Double {
		return self * s
	}
}

extension Float: Scalable {
	public func scale(_ s: Double) -> Float {
		return self * Float(s)
	}
}

public struct Rate<Value, Ratio> where Value: Scalable, Ratio: TimeRate {
	public var value: Value
	
	public init(_ value: Value) {
		self.value = value
	}
	
	public init<Ratio2>(_ rate: Rate<Value, Ratio2>) {
		value = rate.value.scale(Double(Ratio.rate.0 * Ratio2.rate.1) / Double(Ratio.rate.1 * Ratio2.rate.0))
	}
	
	public static func*<Ratio2>(lhs: Rate<Value, Ratio>, rhs: Ratio2) -> Value where Ratio2: TimeRate{
		return lhs.value.scale(Double(rhs.value) * Double(Ratio.rate.1 * Ratio2.rate.0) / Double(Ratio.rate.0 * Ratio2.rate.1))
	}
}

extension DGMDamageVector: Scalable {
	public func scale(_ s: Double) -> DGMDamageVector {
		return DGMDamageVector(em: em * s, thermal: thermal * s, kinetic: kinetic * s, explosive: explosive * s)
	}
}

public typealias DGMGigaJoulePerSecond = Rate<DGMGigaJoule, Seconds>
public typealias DGMCubicMeterPerSecond = Rate<DGMCubicMeter, Seconds>
public typealias DGMRadiansPerSecond = Rate<DGMRadians, Seconds>
public typealias DGMMetersPerSecond = Rate<DGMMeter, Seconds>
public typealias DGMAstronomicalUnitsPerSecond = Rate<DGMAstronomicalUnit, Seconds>
public typealias DGMHPPerSecond = Rate<DGMHP, Seconds>
public typealias DGMFuelUnitsPerHour = Rate<Float, Hours>
public typealias DGMDamagePerSecond = Rate<DGMDamageVector, Seconds>

public struct DGMTank {
	var passiveShield: DGMHPPerSecond
	var shieldRepair: DGMHPPerSecond
	var armorRepair: DGMHPPerSecond
	var hullRepair: DGMHPPerSecond
	
	init(_ tank: __DGMTank) {
		passiveShield = DGMHPPerSecond(tank.passiveShield)
		shieldRepair = DGMHPPerSecond(tank.shieldRepair)
		armorRepair = DGMHPPerSecond(tank.armorRepair)
		hullRepair = DGMHPPerSecond(tank.hullRepair)
	}
}

public struct DGMHostileTarget {
	var angularVelocity: DGMRadiansPerSecond
	var velocity: DGMMetersPerSecond
	var signature: DGMMeter
	var range: DGMMeter
}

extension __DGMHostileTarget {
	init(_ target: DGMHostileTarget) {
		angularVelocity = target.angularVelocity.value
		velocity = target.velocity.value
		signature = target.signature
		range = target.range
	}
}

public extension DGMCapacitor {
	var use: DGMGigaJoulePerSecond { return DGMGigaJoulePerSecond(__use) }
	var recharge: DGMGigaJoulePerSecond { return DGMGigaJoulePerSecond(__recharge) }
}


public extension DGMShip {
	public var supportedDroneCategories: [DGMCategoryID] {
		return __supportedDroneCategories.map {$0.intValue as DGMCategoryID}
	}

	var turretsDPS: DGMDamagePerSecond { return DGMDamagePerSecond(__turretsDPS) }
	var launchersDPS: DGMDamagePerSecond { return DGMDamagePerSecond(__turretsDPS) }
	var dronesDPS: DGMDamagePerSecond { return DGMDamagePerSecond(__turretsDPS) }
	func turretsDPS(target: DGMHostileTarget) -> DGMDamagePerSecond { return DGMDamagePerSecond(__turretsDPS(target: __DGMHostileTarget(target))) }
	func launchersDPS(target: DGMHostileTarget) -> DGMDamagePerSecond { return DGMDamagePerSecond(__launchersDPS(target: __DGMHostileTarget(target))) }
	func dronesDPS(target: DGMHostileTarget) -> DGMDamagePerSecond { return DGMDamagePerSecond(__dronesDPS(target: __DGMHostileTarget(target))) }
	var minerYield: DGMCubicMeterPerSecond { return DGMCubicMeterPerSecond(__minerYield) }
	var droneYield: DGMCubicMeterPerSecond { return DGMCubicMeterPerSecond(__droneYield) }
	var warpSpeed: DGMAstronomicalUnitsPerSecond { return DGMAstronomicalUnitsPerSecond(__warpSpeed) }
	var velocity: DGMMetersPerSecond { return DGMMetersPerSecond(__velocity) }
	func maxVelocity(orbit: DGMMeter) -> DGMMetersPerSecond { return DGMMetersPerSecond(__maxVelocity(orbit: orbit)) }
	func orbitRadius(transverseVelocity: DGMMetersPerSecond) -> DGMMeter { return DGMMeter(__orbitRadius(transverseVelocity: transverseVelocity.value)) }
	func orbitRadius(angularVelocity: DGMRadiansPerSecond) -> DGMMeter { return DGMMeter(__orbitRadius(angularVelocity: angularVelocity.value)) }
	var tank: DGMTank { return DGMTank(__tank) }
	var effectiveTank: DGMTank { return DGMTank(__effectiveTank) }
	var sustainableTank: DGMTank { return DGMTank(__sustainableTank) }
	var effectiveSustainableTank: DGMTank { return DGMTank(__effectiveSustainableTank) }
}

public extension DGMModule {
	@nonobjc public var availableStates: [DGMModuleState] {
		return __availableStates.flatMap {DGMModuleState(rawValue: $0.intValue)}
	}
	
	@nonobjc public var chargeGroups: [DGMGroupID] {
		return __chargeGroups.map {$0.intValue as DGMGroupID}
	}
	var capUse: DGMGigaJoulePerSecond { return DGMGigaJoulePerSecond(__capUse) }
	var miningYield: DGMCubicMeterPerSecond { return DGMCubicMeterPerSecond(__miningYield) }
	var dps: DGMDamagePerSecond { return DGMDamagePerSecond(__dps) }
	func dps(target: DGMHostileTarget) -> DGMDamagePerSecond { return DGMDamagePerSecond(__dps(target: __DGMHostileTarget(target))) }

}

public extension DGMDrone {
	var dps: DGMDamagePerSecond { return DGMDamagePerSecond(__dps) }
	func dps(target: DGMHostileTarget) -> DGMDamagePerSecond { return DGMDamagePerSecond(__dps(target: __DGMHostileTarget(target))) }
	var miningYield: DGMCubicMeterPerSecond { return DGMCubicMeterPerSecond(__miningYield) }
	var velocity: DGMMetersPerSecond { return DGMMetersPerSecond(__velocity) }
}

