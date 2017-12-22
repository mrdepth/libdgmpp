//
//  DGMFactory.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMFactory: DGMFacility {
	
	public required init(_ opaque: dgmpp_facility_ptr) {
		super.init(opaque)
	}
	
	public var schematicID: DGMSchematicID {
		get {
			return DGMSchematicID(dgmpp_factory_get_schematic_id(opaque))
		}
		set {
			dgmpp_factory_set_schematic_id(opaque, dgmpp_schematic_id(newValue))
		}
	}
	
	public var launchTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_factory_get_launch_time(opaque))
		}
		set {
			dgmpp_factory_set_launch_time(opaque, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	public var cycleTime: TimeInterval? {
		get {
			let cycleTime = dgmpp_factory_get_cycle_time(opaque)
			return cycleTime > 0 ? cycleTime : nil
		}
	}
	
	public var output: DGMCommodity? {
		var commodity = dgmpp_commodity()
		guard dgmpp_factory_get_output(opaque, &commodity) else {return nil}
		return DGMCommodity(commodity)
	}

	public var states: [DGMProductionState] {
		return DGMArray<DGMProductionState>(dgmpp_factory_get_states(opaque)).array
	}
	
	public var cycles: [DGMProductionCycle] {
		return DGMArray<DGMProductionCycle>(dgmpp_factory_get_cycles(opaque)).array
	}

}
