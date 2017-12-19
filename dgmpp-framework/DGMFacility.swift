//
//  DGMFacility.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMFacility {
	var opaque: dgmpp_facility_ptr
	
	public required init(_ opaque: dgmpp_facility_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_release(opaque)
	}

	var typeID: DGMTypeID {
		return DGMTypeID(dgmpp_facility_get_type_id(opaque))
	}
	
	var groupID: DGMGroupID {
		return DGMGroupID(dgmpp_facility_get_group_id(opaque))
	}

	var identifier: Int64 {
		return dgmpp_facility_get_identifier(opaque)
	}
	
	var capacity: DGMCubicMeter {
		return dgmpp_facility_get_capacity(opaque)
	}
	
	var freeVolume: DGMCubicMeter {
		return dgmpp_facility_get_free_volume(opaque)
	}

	var usedVolume: DGMCubicMeter {
		return dgmpp_facility_get_used_volume(opaque)
	}

	func add(_ commodity: DGMCommodity) {
		dgmpp_facility_add_commodity(opaque, dgmpp_commodity(commodity))
	}

	func extract(_ commodity: DGMCommodity) throws {
		guard dgmpp_facility_extract_commodity(opaque, dgmpp_commodity(commodity)) else {throw DGMError.NotEnoughCommodities}
	}
	
	var isConfigured: Bool {
		return dgmpp_facility_is_configured(opaque)
	}

}
