//
//  DGMFacility.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMFacility {
	var opaque: dgmpp_facility_ptr
	
	class func facility(_ opaque: dgmpp_facility_ptr) -> DGMFacility {
		switch dgmpp_facility_get_category(opaque) {
		case DGMPP_FACILITY_CATEGORY_COMMAND_CENTER:
			return DGMCommandCenter(opaque)
		case DGMPP_FACILITY_CATEGORY_SPACEPORT:
			return DGMSpaceport(opaque)
		case DGMPP_FACILITY_CATEGORY_FACTORY:
			return DGMFactory(opaque)
		case DGMPP_FACILITY_CATEGORY_ECU:
			return DGMExtractorControlUnit(opaque)
		case DGMPP_FACILITY_CATEGORY_STORAGE:
			return DGMStorage(opaque)
		default:
			return DGMFactory(opaque)
		}
	}
	
	public required init(_ opaque: dgmpp_facility_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_release(opaque)
	}

	public var typeID: DGMTypeID {
		return DGMTypeID(dgmpp_facility_get_type_id(opaque))
	}
	
	public var groupID: DGMGroupID {
		return DGMGroupID(dgmpp_facility_get_group_id(opaque))
	}

	public var identifier: Int64 {
		return dgmpp_facility_get_identifier(opaque)
	}
	
	public var capacity: DGMCubicMeter {
		return dgmpp_facility_get_capacity(opaque)
	}
	
	public var freeVolume: DGMCubicMeter {
		return dgmpp_facility_get_free_volume(opaque)
	}

	public var usedVolume: DGMCubicMeter {
		return dgmpp_facility_get_used_volume(opaque)
	}
	
	public var commodities: [DGMCommodity] {
		return DGMArray<DGMCommodity>(dgmpp_facility_get_commodities(opaque)).array
	}

	public func add(_ commodity: DGMCommodity) {
		dgmpp_facility_add_commodity(opaque, dgmpp_commodity(commodity))
	}

	public func extract(_ commodity: DGMCommodity) throws {
		guard dgmpp_facility_extract_commodity(opaque, dgmpp_commodity(commodity)) else {throw DGMError.NotEnoughCommodities}
	}
	
	public var isConfigured: Bool {
		return dgmpp_facility_is_configured(opaque)
	}

}
