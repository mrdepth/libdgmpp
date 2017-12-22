//
//  DGMProductionState.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMState {
	var opaque: dgmpp_state_ptr
	
	public required init(_ opaque: dgmpp_state_ptr) {
		self.opaque = opaque
	}

	deinit {
		dgmpp_release(opaque)
	}
	
	public var timestamp: Date {
		return Date(timeIntervalSinceReferenceDate: dgmpp_state_get_timestamp(opaque))
	}
	
	public var commodities: [DGMCommodity] {
		return DGMArray<DGMCommodity>(dgmpp_state_get_commodities(opaque)).array
	}
	
	public var volume: DGMCubicMeter {
		return dgmpp_state_get_volume(opaque)
	}

}

public class DGMProductionState: DGMState {

	public required init(_ opaque: dgmpp_state_ptr) {
		super.init(opaque)
	}
	
	public var cycle: DGMProductionCycle? {
		var cycle = dgmpp_production_cycle()
		guard dgmpp_production_state_get_cycle(opaque, &cycle) else {return nil}
		return DGMProductionCycle(cycle)
	}
	
	public var efficiency: DGMPercent {
		return dgmpp_production_state_get_efficiency(opaque)
	}
}

extension DGMState: Hashable {
	
	public var hashValue: Int {
		return dgmpp_get_hash(opaque)
	}
	
	public static func ==(lhs: DGMState, rhs: DGMState) -> Bool {
		return lhs.hashValue == rhs.hashValue
	}
}

