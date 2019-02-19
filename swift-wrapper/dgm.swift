//
//  dgm.swift
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

import Foundation
import cwrapper

extension DGMModule.State {
	init?(_ state: DGMPP_MODULE_STATE) {
		guard let value = DGMModule.State(rawValue: Int(state.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_MODULE_STATE {
	init(_ state: DGMModule.State) {
		self = DGMPP_MODULE_STATE(Int32(state.rawValue))
	}
}

extension DGMModule.Slot {
	init?(_ slot: DGMPP_MODULE_SLOT) {
		guard let value = DGMModule.Slot(rawValue: Int(slot.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_MODULE_SLOT {
	init(_ slot: DGMModule.Slot) {
		self = DGMPP_MODULE_SLOT(Int32(slot.rawValue))
	}
}

extension DGMModule.Hardpoint {
	init?(_ hardpoint: DGMPP_MODULE_HARDPOINT) {
		guard let value = DGMModule.Hardpoint(rawValue: Int(hardpoint.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_MODULE_HARDPOINT {
	init(_ hardpoint: DGMModule.Hardpoint) {
		self = DGMPP_MODULE_HARDPOINT(UInt32(hardpoint.rawValue))
	}
}

extension DGMDrone.Squadron {
	init?(_ squadron: DGMPP_DRONE_SQUADRON) {
		guard let value = DGMDrone.Squadron(rawValue: Int(squadron.rawValue)) else {return nil}
		self = value
	}
}

extension DGMPP_DRONE_SQUADRON {
	init(_ squadron: DGMDrone.Squadron) {
		self = DGMPP_DRONE_SQUADRON(UInt32(squadron.rawValue))
	}
}

extension DGMCharge.Size {
	init?(_ size: DGMPP_CHARGE_SIZE) {
		guard let value = DGMCharge.Size(rawValue: Int(size.rawValue)) else {return nil}
		self = value
	}
}

extension DGMShip.ScanType {
	init?(_ scanType: DGMPP_SCAN_TYPE) {
		guard let value = DGMShip.ScanType(rawValue: Int(scanType.rawValue)) else {return nil}
		self = value
	}
}

extension DGMShip.RigSize {
	init?(_ rigSize: DGMPP_RIG_SIZE) {
		guard let value = DGMShip.RigSize(rawValue: Int(rigSize.rawValue)) else {return nil}
		self = value
	}
}

extension DGMRaceID {
	init?(_ raceID: DGMPP_RACE_ID) {
		guard let value = DGMRaceID(rawValue: Int(raceID.rawValue)) else {return nil}
		self = value
	}
}

extension DGMCommodity.Tier {
	init?(_ tier: DGMPP_COMMODITY_TIER) {
		guard let value = DGMCommodity.Tier(rawValue: Int(tier.rawValue)) else {return nil}
		self = value
	}
}

class DGMArray<T>: DGMObject {
	
	convenience init(_ handle: dgmpp_array) {
		self.init(handle, owned: true)
	}
	
}

extension DGMArray where T: DGMType {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: dgmpp_type.self, capacity: size)
		return (0..<size).compactMap {
			return T.type(ptr[$0]) as? T
//			return T(ptr[$0], owned: false)
		}
	}
}

extension DGMArray where T == DGMAttribute {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: dgmpp_attribute.self, capacity: size)
		return (0..<size).map {
			return T(ptr[$0], owned: false)
		}
	}
}

extension DGMArray where T == Int {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: Int32.self, capacity: size)
		return (0..<size).map {Int(ptr[$0])}
	}
}

extension DGMArray where T: DGMState {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: dgmpp_state.self, capacity: size)
		return (0..<size).map {
			return T(ptr[$0], owned: false)
		}
	}
}

extension DGMArray where T == DGMFacility {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: dgmpp_facility.self, capacity: size)
		return (0..<size).map {
			return DGMFacility.facility(ptr[$0])
		}
	}
}

extension DGMArray where T == DGMCommodity {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: dgmpp_commodity.self, capacity: size)
		return (0..<size).map {
			return T(ptr[$0])
		}
	}
}

extension DGMArray where T == DGMProductionCycle {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: dgmpp_production_cycle.self, capacity: size)
		return (0..<size).map {
			return T(ptr[$0])
		}
	}
}

extension DGMArray where T == DGMRoute {
	var array: [T] {
		let size = dgmpp_array_get_size(handle)
		guard size > 0 else {return []}
		let ptr = dgmpp_array_get_values(handle).bindMemory(to: dgmpp_route.self, capacity: size)
		return (0..<size).map {
			return T(ptr[$0])
		}
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
		self.init(em: damageVector.em,
				  thermal: damageVector.thermal,
				  kinetic: damageVector.kinetic,
				  explosive: damageVector.explosive)
	}
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
		self.init(angular_velocity: target.angularVelocity.value,
				  velocity: target.velocity.value,
				  signature: target.signature,
				  range: target.range)
	}
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

extension DGMHitPoints {
	init(_ hitPoints: dgmpp_hit_points) {
		shield = hitPoints.shield
		armor = hitPoints.armor
		hull = hitPoints.hull
	}
}

extension DGMCommodity {
	init(_ commodity: dgmpp_commodity) {
		typeID = DGMTypeID(commodity.type_id)
		tier = Tier(commodity.tier) ?? .unknown
		volume = commodity.volume
		quantity = commodity.quantity
	}
}

extension dgmpp_commodity {
	init(_ commodity: DGMCommodity) {
		self.init(type_id: dgmpp_type_id(commodity.typeID),
				  tier: DGMPP_COMMODITY_TIER(Int32(commodity.tier.rawValue)),
				  volume: commodity.volume,
				  quantity: commodity.quantity)
	}
}

extension DGMProductionCycle {
	init(_ cycle: dgmpp_production_cycle) {
		start = Date(timeIntervalSinceReferenceDate: cycle.start)
		duration = cycle.duration
		yield = DGMCommodity(cycle.yield)
		waste = DGMCommodity(cycle.waste)
	}
}

extension DGMRoute {
	init(_ route: dgmpp_route) {
		from = DGMFacility.facility(route.from)
		to = DGMFacility.facility(route.to)
		commodity = DGMCommodity(route.commodity)
	}
}

extension DGMType.MetaGroup {
	init?(_ metaGroup: DGMPP_META_GROUP) {
		guard let value = DGMType.MetaGroup(rawValue: Int(metaGroup.rawValue)) else {return nil}
		self = value
	}
}
