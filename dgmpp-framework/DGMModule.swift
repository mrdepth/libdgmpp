//
//  DGMModule.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMModule: DGMType {
	
	public enum State: Int {
		case unknown = -1
		case offline
		case online
		case active
		case overloaded
	}
	
	public enum Slot: Int {
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
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}
	
	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_module_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
	
	public func canHaveState(_ state: State) -> Bool {
		return dgmpp_module_can_have_state(opaque, DGMPP_MODULE_STATE(Int32(state.rawValue)))
	}
	
	public var availableStates: [State] {
		return DGMArray<Int>(dgmpp_module_get_available_states(opaque)).array.flatMap {State(rawValue: $0)}
	}
	
	public var state: State {
		get {
			return State(dgmpp_module_get_state(opaque)) ?? .unknown
		}
		set {
			dgmpp_module_set_state(opaque, DGMPP_MODULE_STATE(newValue))
		}
	}
	
	public var preferredState: State {
		get {
			return State(dgmpp_module_get_preferred_state(opaque)) ?? .unknown
		}
	}
	
	public var target: DGMShip? {
		get {
			guard let target = dgmpp_module_get_target(opaque) else {return nil}
			return DGMShip(target)
		}
		set {
			dgmpp_module_set_target(opaque, newValue?.opaque)
		}
	}
	
	public var slot: Slot {
		get {
			return Slot(dgmpp_module_get_slot(opaque)) ?? .none
		}
	}

	public var hardpoint: Hardpoint {
		get {
			return Hardpoint(dgmpp_module_get_hardpoint(opaque)) ?? .none
		}
	}

	public var socket: Int {
		get {
			return dgmpp_module_get_socket(opaque)
		}
	}
	
	public var charge: DGMCharge? {
		guard let charge = dgmpp_module_get_charge(opaque) else {return nil}
		return DGMCharge(charge)
	}
	
	public func setCharge(_ charge: DGMCharge?) throws {
		if let charge = charge {
			guard dgmpp_module_set_charge(opaque, charge.opaque) else {throw DGMError.cannotFit(charge)}
		}
		else {
			dgmpp_module_set_charge(opaque, nil)
		}
	}
	
	public func canFit(_ charge: DGMCharge) -> Bool {
		return dgmpp_module_can_fit_charge(opaque, charge.opaque)
	}
	
	public var chargeGroups: [DGMGroupID] {
		return DGMArray<Int>(dgmpp_module_get_charge_groups(opaque)).array.map {DGMGroupID($0)}
	}

	public var chargeSize: DGMCharge.Size {
		return DGMCharge.Size(dgmpp_module_get_charge_size(opaque)) ?? .none
	}
	
	public var isFail: Bool {
		return dgmpp_module_is_fail(opaque)
	}
	
	public var reloadTime: TimeInterval {
		return dgmpp_module_get_reload_time(opaque)
	}

	public var cycleTime: TimeInterval {
		return dgmpp_module_get_cycle_time(opaque)
	}

	public var rawCycleTime: TimeInterval {
		return dgmpp_module_get_raw_cycle_time(opaque)
	}

	public var charges: Int {
		return dgmpp_module_get_charges(opaque)
	}

	public var shots: Int {
		return dgmpp_module_get_shots(opaque)
	}
	
	public var capUse: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_module_get_cap_use(opaque))
	}

	public var cpuUse: DGMTeraflops {
		return dgmpp_module_get_cpu_use(opaque)
	}
	
	public var powerGridUse: DGMMegaWatts {
		return dgmpp_module_get_power_grid_use(opaque)
	}
	
	public var calibrationUse: DGMCalibrationPoints {
		return dgmpp_module_get_calibration_use(opaque)
	}
	
	public var accuracyScore: DGMPoints {
		return dgmpp_module_get_accuracy_score(opaque)
	}
	
	public var signatureResolution: DGMMeter {
		return dgmpp_module_get_signature_resolution(opaque)
	}
	
	public var miningYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_module_get_mining_yield(opaque))
	}

	public var volley: DGMDamageVector {
		return DGMDamageVector(dgmpp_module_get_volley(opaque))
	}
	
	public func dps(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_module_get_dps_v2(opaque, dgmpp_hostile_target(target))))
	}

	public var optimal: DGMMeter {
		return dgmpp_module_get_optimal(opaque)
	}
	
	public var falloff: DGMMeter {
		return dgmpp_module_get_falloff(opaque)
	}
	
	public var lifeTime: TimeInterval {
		return dgmpp_module_get_life_time(opaque)
	}

	public func angularVelocity(targetSignature: DGMMeter, hitChance: DGMPercent = 0.75) -> DGMRadiansPerSecond {
		return DGMRadiansPerSecond(dgmpp_module_get_angular_velocity(opaque, targetSignature, hitChance))
	}

}

