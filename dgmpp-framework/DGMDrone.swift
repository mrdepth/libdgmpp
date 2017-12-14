//
//  DGMDrone.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMDrone: DGMType {
	
	override init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}

	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_drone_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
	
	public var isActive: Bool {
		get {
			return dgmpp_drone_is_active(opaque)
		}
		set {
			dgmpp_drone_set_active(opaque, newValue)
		}
	}
	
	public var charge: DGMCharge? {
		guard let charge = dgmpp_drone_get_charge(opaque) else {return nil}
		return DGMCharge(charge)
	}
	
	public var squadronSize: Int {
		return dgmpp_drone_get_squadron_size(opaque)
	}
	
	public var squadronTag: Int {
		return Int(dgmpp_drone_get_squadron_tag(opaque))
	}
	
	public var target: DGMShip? {
		get {
			guard let target = dgmpp_drone_get_target(opaque) else {return nil}
			return DGMShip(target)
		}
		set {
			dgmpp_drone_set_target(opaque, newValue?.opaque)
		}
	}
	
	var cycleTime: TimeInterval {
		return dgmpp_drone_get_cycle_time(opaque)
	}
	
	var volley: DGMDamageVector {
		return DGMDamageVector(dgmpp_drone_get_volley(opaque))
	}
	
	func dps(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_drone_get_dps_v2(opaque, dgmpp_hostile_target(target))))
	}
	
}
