//
//  DGMFacility.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMFacility: DGMObject {
	
	class func facility(_ handle: dgmpp_facility) -> DGMFacility {
		switch dgmpp_facility_get_category(handle) {
		case DGMPP_FACILITY_CATEGORY_COMMAND_CENTER:
			return DGMCommandCenter(handle)
		case DGMPP_FACILITY_CATEGORY_SPACEPORT:
			return DGMSpaceport(handle)
		case DGMPP_FACILITY_CATEGORY_FACTORY:
			return DGMFactory(handle)
		case DGMPP_FACILITY_CATEGORY_ECU:
			return DGMExtractorControlUnit(handle)
		case DGMPP_FACILITY_CATEGORY_STORAGE:
			return DGMStorage(handle)
		default:
			return DGMFactory(handle)
		}
	}
	
	convenience init(_ handle: dgmpp_facility) {
		self.init(handle, owned: false)
	}

	
	public var typeID: DGMTypeID {
		return DGMTypeID(dgmpp_facility_get_type_id(handle))
	}
	
	public var groupID: DGMGroupID {
		return DGMGroupID(dgmpp_facility_get_group_id(handle))
	}

	public var identifier: Int64 {
		return dgmpp_facility_get_identifier(handle)
	}
	
	public var capacity: DGMCubicMeter {
		return dgmpp_facility_get_capacity(handle)
	}
	
	public var freeVolume: DGMCubicMeter {
		return dgmpp_facility_get_free_volume(handle)
	}

	public var usedVolume: DGMCubicMeter {
		return dgmpp_facility_get_used_volume(handle)
	}
	
	public var commodities: [DGMCommodity] {
		return DGMArray<DGMCommodity>(dgmpp_facility_copy_commodities(handle)).array
	}
	
	public func income(typeID: DGMTypeID) -> DGMCommodity {
		return DGMCommodity(dgmpp_facility_get_income(handle, dgmpp_type_id(typeID)))
	}

	public func add(_ commodity: DGMCommodity) {
		dgmpp_facility_add_commodity(handle, dgmpp_commodity(commodity))
	}

	public func extract(_ commodity: DGMCommodity) throws {
		guard dgmpp_facility_extract_commodity(handle, dgmpp_commodity(commodity)) else {throw DGMError.NotEnoughCommodities}
	}
	
	public var isConfigured: Bool {
		return dgmpp_facility_is_configured(handle)
	}
	
	public var name: String {
		return String(cString: dgmpp_facility_get_name(handle));
	}


}
