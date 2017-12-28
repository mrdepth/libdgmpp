//
//  DGMDrone.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMDrone: DGMType {
	
	public enum Squadron: Int {
		case none
		case heavy
		case light
		case support
	}

	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_drone_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}

	public convenience init(_ other: DGMDrone) {
		self.init(dgmpp_drone_copy(other.handle), owned: true)
	}

	public var isActive: Bool {
		get {
			return dgmpp_drone_is_active(handle)
		}
		set {
			dgmpp_drone_set_active(handle, newValue)
		}
	}
	
	public var charge: DGMCharge? {
		guard let charge = dgmpp_drone_get_charge(handle) else {return nil}
		return DGMCharge(charge)
	}
	
	public var squadron: Squadron {
		return Squadron(dgmpp_drone_get_squadron(handle)) ?? .none
	}
	
	public var squadronSize: Int {
		return dgmpp_drone_get_squadron_size(handle)
	}
	
	public var squadronTag: Int {
		return Int(dgmpp_drone_get_squadron_tag(handle))
	}
	
	public var target: DGMShip? {
		get {
			guard let target = dgmpp_drone_get_target(handle) else {return nil}
			return DGMShip(target)
		}
		set {
			dgmpp_drone_set_target(handle, newValue?.handle)
		}
	}
	
	public var cycleTime: TimeInterval {
		return dgmpp_drone_get_cycle_time(handle)
	}
	
	public var volley: DGMDamageVector {
		return DGMDamageVector(dgmpp_drone_get_volley(handle))
	}
	
	public func dps(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_drone_get_dps_v2(handle, dgmpp_hostile_target(target))))
	}
	
	public var optimal: DGMMeter {
		return dgmpp_drone_get_optimal(handle)
	}
	
	public var falloff: DGMMeter {
		return dgmpp_drone_get_falloff(handle)
	}

	public var accuracyScore: DGMPoints {
		return dgmpp_drone_get_accuracy_score(handle)
	}

	public var miningYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_drone_get_mining_yield(handle))
	}

	public var velocity: DGMMetersPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_drone_get_velocity(handle))
	}

}
