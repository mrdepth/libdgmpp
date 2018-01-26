//
//  DGMFactory.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation
import cwrapper

public class DGMFactory: DGMFacility {
	
	public var schematicID: DGMSchematicID {
		get {
			return DGMSchematicID(dgmpp_factory_get_schematic_id(handle))
		}
		set {
			dgmpp_factory_set_schematic_id(handle, dgmpp_schematic_id(newValue))
		}
	}
	
	public var launchTime: Date {
		get {
			return Date(timeIntervalSinceReferenceDate: dgmpp_factory_get_launch_time(handle))
		}
		set {
			dgmpp_factory_set_launch_time(handle, newValue.timeIntervalSinceReferenceDate)
		}
	}
	
	public var cycleTime: TimeInterval? {
		get {
			let cycleTime = dgmpp_factory_get_cycle_time(handle)
			return cycleTime > 0 ? cycleTime : nil
		}
	}
	
	public var output: DGMCommodity? {
		var commodity = dgmpp_commodity()
		guard dgmpp_factory_get_output(handle, &commodity) else {return nil}
		return DGMCommodity(commodity)
	}
	
	public var inputs: [DGMRoute] {
		return DGMArray<DGMRoute>(dgmpp_facility_copy_inputs(handle)).array
	}

	public var outputs: [DGMRoute] {
		return DGMArray<DGMRoute>(dgmpp_facility_copy_outputs(handle)).array
	}

	public var states: [DGMProductionState] {
		return DGMArray<DGMProductionState>(dgmpp_factory_copy_states(handle)).array
	}
	
	public var cycles: [DGMProductionCycle] {
		return DGMArray<DGMProductionCycle>(dgmpp_factory_copy_cycles(handle)).array
	}

}
