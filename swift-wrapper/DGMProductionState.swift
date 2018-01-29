//
//  DGMProductionState.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation
import cwrapper

public class DGMState: DGMObject {
	
	public var timestamp: Date {
		return Date(timeIntervalSinceReferenceDate: dgmpp_state_get_timestamp(handle))
	}
	
	public var commodities: [DGMCommodity] {
		return DGMArray<DGMCommodity>(dgmpp_state_copy_commodities(handle)).array
	}
	
	public var volume: DGMCubicMeter {
		return dgmpp_state_get_volume(handle)
	}

}

public class DGMProductionState: DGMState {

	public var cycle: DGMProductionCycle? {
		var cycle = dgmpp_production_cycle()
		guard dgmpp_production_state_get_cycle(handle, &cycle) != 0 else {return nil}
		return DGMProductionCycle(cycle)
	}
	
	public var efficiency: DGMPercent {
		return dgmpp_production_state_get_efficiency(handle)
	}
}
