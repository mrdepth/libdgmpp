//
//  DGMDrone.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMDrone: DGMType, Codable {
	
	public enum Squadron: Int {
		case none
		case heavy
		case light
		case support
		case standupHeavy
		case standupLight
		case standupSupport
	}

    required init(_ handle: dgmpp_handle) {
        super.init(handle)
    }

	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_drone_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type)
	}

	public convenience init(_ other: DGMDrone) {
		self.init(dgmpp_drone_copy(other.handle))
	}

	public var isActive: Bool {
		get {
			return dgmpp_drone_is_active(handle) != 0
		}
		set {
            willChange()
			dgmpp_drone_set_active(handle, newValue ? 1 : 0)
		}
	}
	
	public var hasKamikazeAbility: Bool {
		return dgmpp_drone_has_kamikaze_ability(handle) != 0
	}

	public var isKamikaze: Bool {
		get {
			return dgmpp_drone_is_kamikaze(handle) != 0
		}
		set {
            willChange()
			dgmpp_drone_set_kamikaze(handle, newValue ? 1 : 0)
		}
	}

	public var charge: DGMCharge? {
		guard let charge = dgmpp_drone_copy_charge(handle) else {return nil}
        return DGMType.type(charge) as? DGMCharge
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
			guard let target = dgmpp_drone_copy_target(handle) else {return nil}
			return DGMType.type(target) as? DGMShip
		}
		set {
            willChange()
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

		
	public convenience required init(from decoder: Decoder) throws {
		let container = try decoder.container(keyedBy: CodingKeys.self)
		let typeID = try container.decode(DGMTypeID.self, forKey: .typeID)
		
		try self.init(typeID: typeID)

		isActive = try container.decode(Bool.self, forKey: .isActive)
		isKamikaze = try container.decode(Bool.self, forKey: .isKamikaze)
		
		if let identifier = try container.decodeIfPresent(Int.self, forKey: .identifier) {
			self.identifier = identifier
		}

	}
	
	public func encode(to encoder: Encoder) throws {
		var container = encoder.container(keyedBy: CodingKeys.self)
		try container.encode(typeID, forKey: .typeID)
		try container.encode(isActive, forKey: .isActive)
		try container.encode(isKamikaze, forKey: .isKamikaze)
		try container.encode(identifier, forKey: .identifier)
	}
	
	enum CodingKeys: String, CodingKey {
		case typeID
		case isActive
		case isKamikaze
		case identifier
	}

}
