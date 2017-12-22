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

	public var launchTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_ecu_get_launch_time(opaque))
		}
		set {
			dgmpp_ecu_set_launch_time(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	public var installTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_ecu_get_install_time(opaque))
		}
		set {
			dgmpp_ecu_set_install_time(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}

	public var expiryTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_ecu_get_expiry_time(opaque))
		}
		set {
			dgmpp_ecu_set_expiry_time(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	public var cycleTime: TimeInterval {
		get {
			return dgmpp_ecu_get_cycle_time(opaque)
		}
		set {
			dgmpp_ecu_set_cycle_time(opaque, newValue)
		}
	}
	
	public var quantityPerCycle: Int {
		get {
			return dgmpp_ecu_get_quantity_per_cycle(opaque)
		}
		set {
			dgmpp_ecu_set_quantity_per_cycle(opaque, newValue)
		}
	}
	
	public var output: DGMCommodity? {
		var commodity = dgmpp_commodity()
		guard dgmpp_ecu_get_output(opaque, &commodity) else {return nil}
		return DGMCommodity(commodity)
	}
	
	public var states: [DGMProductionState] {
		return DGMArray<DGMProductionState>(dgmpp_ecu_get_states(opaque)).array
	}
	
	public var cycles: [DGMProductionCycle] {
		return DGMArray<DGMProductionCycle>(dgmpp_ecu_get_cycles(opaque)).array
	}

}
