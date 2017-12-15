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
	
	override init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}
	
	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_module_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
	
	func canHaveState(_ state: State) -> Bool {
		return dgmpp_module_can_have_state(opaque, DGMPP_MODULE_STATE(rawValue: Int32(state.rawValue)))
	}
	
	var availableStates: [State] {
		return dgmpp_module_get_available_states(opaque).array.flatMap {State(rawValue: $0)}
	}
	
	var state: State {
		get {
			return State(dgmpp_module_get_state(opaque)) ?? .unknown
		}
		set {
			dgmpp_module_set_state(opaque, DGMPP_MODULE_STATE(newValue))
		}
	}
	
	var preferredState: State {
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
	
	var slot: Slot {
		get {
			return Slot(dgmpp_module_get_slot(opaque)) ?? .none
		}
	}

	var hardpoint: Hardpoint {
		get {
			return Hardpoint(dgmpp_module_get_hardpoint(opaque)) ?? .none
		}
	}

	var socket: Int {
		get {
			return dgmpp_module_get_socket(opaque)
		}
	}
	
	var charge: DGMCharge? {
		guard let charge = dgmpp_module_get_charge(opaque) else {return nil}
		return DGMCharge(charge)
	}
	
	func setCharge(_ charge: DGMCharge?) throws {
		if let charge = charge {
			guard dgmpp_module_set_charge(opaque, charge.opaque) else {throw DGMError.cannotFit(charge)}
		}
		else {
			dgmpp_module_set_charge(opaque, nil)
		}
	}
	
	func canFit(_ charge: DGMCharge) -> Bool {
		return dgmpp_module_can_fit_charge(opaque, charge.opaque)
	}
	
	var chargeGroups: [DGMGroupID] {
		return dgmpp_module_get_charge_groups(opaque).array.map {DGMGroupID($0)}
	}

	var chargeSize: DGMCharge.Size {
		return DGMCharge.Size(dgmpp_module_get_charge_size(opaque)) ?? .none
	}
	
	var isFail: Bool {
		return dgmpp_module_is_fail(opaque)
	}
	
	var reloadTime: TimeInterval {
		return dgmpp_module_get_reload_time(opaque)
	}

	var cycleTime: TimeInterval {
		return dgmpp_module_get_cycle_time(opaque)
	}

	var rawCycleTime: TimeInterval {
		return dgmpp_module_get_raw_cycle_time(opaque)
	}

	var charges: Int {
		return dgmpp_module_get_charges(opaque)
	}

	var shots: Int {
		return dgmpp_module_get_shots(opaque)
	}
	
	var capUse: DGMGigaJoulePerSecond {
		return DGMGigaJoulePerSecond(dgmpp_module_get_cap_use(opaque))
	}

	var cpuUse: DGMTeraflops {
		return dgmpp_module_get_cpu_use(opaque)
	}
	
	var powerGridUse: DGMMegaWatts {
		return dgmpp_module_get_power_grid_use(opaque)
	}
	
	var calibrationUse: DGMCalibrationPoints {
		return dgmpp_module_get_calibration_use(opaque)
	}
	
	var accuracyScore: DGMPoints {
		return dgmpp_module_get_accuracy_score(opaque)
	}
	
	var signatureResolution: DGMMeter {
		return dgmpp_module_get_signature_resolution(opaque)
	}
	
	var miningYield: DGMCubicMeterPerSecond {
		return DGMCubicMeterPerSecond(dgmpp_module_get_mining_yield(opaque))
	}

	var volley: DGMDamageVector {
		return DGMDamageVector(dgmpp_module_get_volley(opaque))
	}
	
	func dps(target: DGMHostileTarget = DGMHostileTarget.default) -> DGMDamagePerSecond {
		return DGMDamagePerSecond(DGMDamageVector(dgmpp_module_get_dps_v2(opaque, dgmpp_hostile_target(target))))
	}

	var optimal: DGMMeter {
		return dgmpp_module_get_optimal(opaque)
	}
	
	var falloff: DGMMeter {
		return dgmpp_module_get_falloff(opaque)
	}
	
	var lifeTime: TimeInterval {
		return dgmpp_module_get_life_time(opaque)
	}


}

