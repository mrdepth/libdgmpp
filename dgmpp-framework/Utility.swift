//
//  Utility.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

enum DGMError: Error {
	case typeNotFound(DGMTypeID)
	case cannotFit(DGMType)
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

public class DGMTypes {
	private var opaque: dgmpp_types_array_ptr
	
	init(_ opaque: dgmpp_types_array_ptr) {
		self.opaque = opaque
	}

	deinit {
		dgmpp_types_array_free(opaque)
	}
	
	func array<T:DGMType>() -> [T] {
		return (0..<opaque.pointee.count).map {T(opaque.pointee.types[$0]!)}
	}
	
//	var array: [dgmpp_type_ptr] {
//		return (0..<opaque.pointee.count).map {opaque.pointee.types[$0]!}
//	}
}

public class DGMAttributes {
	private var opaque: dgmpp_attributes_array_ptr
	
	init(_ opaque: dgmpp_attributes_array_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_attributes_array_free(opaque)
	}
	
	var array: [DGMAttribute] {
		return (0..<opaque.pointee.count).map { DGMAttribute(opaque.pointee.attributes[$0]!) }
	}
}

public class DGMInts {
	private var opaque: dgmpp_ints_array_ptr
	
	init(_ opaque: dgmpp_ints_array_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_ints_array_free(opaque)
	}
	
	var array: [Int] {
		return (0..<opaque.pointee.count).map {Int(opaque.pointee.values[$0])}
	}
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

extension DGMDamageVector {
	init(_ damageVector: dgmpp_damage_vector) {
		em = damageVector.em
		thermal = damageVector.thermal
		kinetic = damageVector.kinetic
		explosive = damageVector.explosive
	}
}

extension dgmpp_damage_vector {
	init(_ damageVector: DGMDamageVector) {
		em = damageVector.em
		thermal = damageVector.thermal
		kinetic = damageVector.kinetic
		explosive = damageVector.explosive
	}
}

public struct DGMTank {
	var passiveShield: DGMHPPerSecond
	var shieldRepair: DGMHPPerSecond
	var armorRepair: DGMHPPerSecond
	var hullRepair: DGMHPPerSecond
	
	init(_ tank: dgmpp_tank) {
		passiveShield = DGMHPPerSecond(tank.passive_shield)
		shieldRepair = DGMHPPerSecond(tank.shield_repair)
		armorRepair = DGMHPPerSecond(tank.armor_repair)
		hullRepair = DGMHPPerSecond(tank.hull_repair)
	}
}

public struct DGMHostileTarget {
	var angularVelocity: DGMRadiansPerSecond = DGMRadiansPerSecond(0)
	var velocity: DGMMetersPerSecond = DGMMetersPerSecond(0)
	var signature: DGMMeter = 0
	var range: DGMMeter = 0
	
	public static let `default` = DGMHostileTarget(dgmpp_hostile_target_default)
}

extension DGMHostileTarget {
	init(_ target: dgmpp_hostile_target) {
		angularVelocity = DGMRadiansPerSecond(target.angular_velocity)
		velocity = DGMMetersPerSecond (target.velocity)
		signature = target.signature
		range = target.range
	}
}

extension dgmpp_hostile_target {
	init(_ target: DGMHostileTarget) {
		angular_velocity = target.angularVelocity.value
		velocity = target.velocity.value
		signature = target.signature
		range = target.range
	}
}

public struct DGMResistances {
	public struct Layer {
		var em: DGMPercent
		var thermal: DGMPercent
		var kinetic: DGMPercent
		var explosive: DGMPercent
	}
	
	var shield: Layer
	var armor: Layer
	var hull: Layer
}

extension DGMResistances.Layer {
	init(_ layer: dgmpp_resistances_layer) {
		em = layer.em
		thermal = layer.thermal
		kinetic = layer.kinetic
		explosive = layer.explosive
	}
}

extension DGMResistances {
	init(_ resistances: dgmpp_resistances) {
		shield = Layer(resistances.shield)
		armor = Layer(resistances.armor)
		hull = Layer(resistances.hull)
	}
}

public struct DGMHitPoints {
	public var shield: DGMHP
	public var armor: DGMHP
	public var hull: DGMHP
}

extension DGMHitPoints {
	init(_ hitPoints: dgmpp_hit_points) {
		shield = hitPoints.shield
		armor = hitPoints.armor
		hull = hitPoints.hull
	}
}
