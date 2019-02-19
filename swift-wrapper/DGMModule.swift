//
//  DGMModule.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMModule: DGMType, Codable {
	
	public enum State: Int, Codable {
		case unknown = -1
		case offline
		case online
		case active
		case overloaded
	}
	
	public enum Slot: Int, Codable {
		case none = 0
		case hi
		case med
		case low
		case rig
		case subsystem
		case mode
		case service
		case starbaseStructure
	}
	
	public enum Hardpoint: Int {
		case none
		case launcher
		case turret
	}
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_module_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}

	public convenience init(_ other: DGMModule) {
		self.init(dgmpp_module_copy(other.handle), owned: true)
	}

	public func canHaveState(_ state: State) -> Bool {
		return dgmpp_module_can_have_state(handle, DGMPP_MODULE_STATE(Int32(state.rawValue))) != 0
	}
	
	public var availableStates: [State] {
		return DGMArray<Int>(dgmpp_module_copy_available_states(handle)).array.compactMap {State(rawValue: $0)}
	}
	
	public var state: State {
		get {
			return State(dgmpp_module_get_state(handle)) ?? .unknown
		}
		set {
			dgmpp_module_set_state(handle, DGMPP_MODULE_STATE(newValue))
		}
	}
	
	public var preferredState: State {
		get {
			return State(dgmpp_module_get_preferred_state(handle)) ?? .unknown
		}
	}
	
	public var target: DGMShip? {
		get {
			guard let target = dgmpp_module_get_target(handle) else {return nil}
			return DGMShip(target)
		}
		set {
			dgmpp_module_set_target(handle, newValue?.handle)
		}
	}
	
	public var slot: Slot {
		get {
			return Slot(dgmpp_module_get_slot(handle)) ?? .none
		}
	}

	public var hardpoint: Hardpoint {
		get {
			return Hardpoint(dgmpp_module_get_hardpoint(handle)) ?? .none
		}
	}

	public var socket: Int {
		get {
			return dgmpp_module_get_socket(handle)
		}
	}
	
	public var charge: DGMCharge? {
		guard let charge = dgmpp_module_get_charge(handle) else {return nil}
		return DGMCharge(charge)
	}
	
	public func setCharge(_ charge: DGMCharge?) throws {
		if let charge = charge {
			guard dgmpp_module_set_charge(handle, charge.handle) != 0 else {throw DGMError.cannotFit(charge)}
		}
		else {
			dgmpp_module_set_charge(handle, nil)
		}
	}
	
	public func canFit(_ charge: DGMCharge) -> Bool {
		return dgmpp_module_can_fit_charge(handle, charge.handle) != 0
	}
	
	public var chargeGroups: [DGMGroupID] {
		return DGMArray<Int>(dgmpp_module_copy_charge_groups(handle)).array.map {DGMGroupID($0)}
	}

	public var chargeSize: DGMCharge.Size {
		return DGMCharge.Size(dgmpp_module_get_charge_size(handle)) ?? .none
	}
	
	public var isFail: Bool {
		return dgmpp_module_is_fail(handle) != 0
	}

	public var requireTarget: Bool {
		return dgmpp_module_require_target(handle) != 0
	}

	public var reloadTime: TimeInterval {
		return dgmpp_module_get_reload_time(handle)
	}

	public var cycleTime: TimeInterval {
		return dgmpp_module_get_cycle_time(handle)
	}

	public var rawCycleTime: TimeInterval {
		return dgmpp_module_get_raw_cycle_time(handle)
	}

	public var charges: Int {
		return dgmpp_module_get_charges(handle)
	}

	public var shots: Int {
		return dgmpp_module_get_shots(handle)
	}
	
	public var capUse: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_module_get_cap_use(handle))
	}

	public var cpuUse: DGMTeraflops {
		return dgmpp_module_get_cpu_use(handle)
	}
	
	public var powerGridUse: DGMMegaWatts {
		return dgmpp_module_get_power_grid_use(handle)
	}
	
	public var calibrationUse: DGMCalibrationPoints {
		return dgmpp_module_get_calibration_use(handle)
	}
	
	public var accuracyScore: DGMPoints {
		return dgmpp_module_get_accuracy_score(handle)
	}
	
	public var signatureResolution: DGMMeter {
		return dgmpp_module_get_signature_resolution(handle)
	}
	
	public var miningYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_module_get_mining_yield(handle))
	}

	public var volley: DGMDamageVector {
		return DGMDamageVector(dgmpp_module_get_volley(handle))
	}
	
	public func dps(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_module_get_dps_v2(handle, dgmpp_hostile_target(target))))
	}

	public var optimal: DGMMeter {
		return dgmpp_module_get_optimal(handle)
	}
	
	public var falloff: DGMMeter {
		return dgmpp_module_get_falloff(handle)
	}
	
	public var lifeTime: TimeInterval {
		return dgmpp_module_get_life_time(handle)
	}

	public func angularVelocity(targetSignature: DGMMeter, hitChance: DGMPercent = 0.75) -> DGMRadiansPerSecond {
		return DGMRadiansPerSecond(dgmpp_module_get_angular_velocity(handle, targetSignature, hitChance))
	}

	
	public required init(_ handle: dgmpp_handle, owned: Bool) {
		super.init(handle, owned: owned)
	}
	
	public convenience required init(from decoder: Decoder) throws {
		let container = try decoder.container(keyedBy: CodingKeys.self)
		let typeID = try container.decode(DGMTypeID.self, forKey: .typeID)
		
		try self.init(typeID: typeID)

		state = try container.decode(State.self, forKey: .state)
		try setCharge(try container.decodeIfPresent(DGMCharge.self, forKey: .charge))
		
		if let identifier = try container.decodeIfPresent(Int.self, forKey: .identifier) {
			self.identifier = identifier
		}
	}
	
	public func encode(to encoder: Encoder) throws {
		var container = encoder.container(keyedBy: CodingKeys.self)
		try container.encode(typeID, forKey: .typeID)
		try container.encode(state, forKey: .state)
		try container.encodeIfPresent(charge, forKey: .charge)
		try container.encode(identifier, forKey: .identifier)
	}
	
	enum CodingKeys: String, CodingKey {
		case typeID
		case state
		case charge
		case identifier
	}

}

