//
//  DGMExtractorControlUnit.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMExtractorControlUnit: DGMFacility {
	
	public required init(_ opaque: dgmpp_facility_ptr) {
		super.init(opaque)
	}

	var launchTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_ecu_get_launch_time(opaque))
		}
		set {
			dgmpp_ecu_set_launch_time(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	var installTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_ecu_get_install_time(opaque))
		}
		set {
			dgmpp_ecu_set_install_time(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}

	var expiryTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_ecu_get_expiry_time(opaque))
		}
		set {
			dgmpp_ecu_set_expiry_time(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	var cycleTime: TimeInterval {
		get {
			return dgmpp_ecu_get_cycle_time(opaque)
		}
		set {
			dgmpp_ecu_set_cycle_time(opaque, newValue)
		}
	}
	
	var quantityPerCycle: Int {
		get {
			return dgmpp_ecu_get_quantity_per_cycle(opaque)
		}
		set {
			dgmpp_ecu_set_quantity_per_cycle(opaque, newValue)
		}
	}
	
	var output: DGMCommodity? {
		var commodity = dgmpp_commodity()
		guard dgmpp_ecu_get_output(opaque, &commodity) else {return nil}
		return DGMCommodity(commodity)
	}
	
	var states: [DGMProductionState] {
		return DGMArray<DGMProductionState>(dgmpp_ecu_get_states(opaque)).array
	}
	
	var cycles: [DGMProductionCycle] {
		return DGMArray<DGMProductionCycle>(dgmpp_ecu_get_cycles(opaque)).array
	}

}
