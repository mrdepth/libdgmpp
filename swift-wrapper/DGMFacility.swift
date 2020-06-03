//
//  DGMFacility.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation
import cwrapper

public class DGMFacility: DGMObject {
	
	class func facility(_ handle: dgmpp_facility) -> DGMFacility {
        DGMObject.get(handle) {
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
		guard dgmpp_facility_extract_commodity(handle, dgmpp_commodity(commodity)) != 0 else {throw DGMError.notEnoughCommodities}
	}
	
	public var isConfigured: Bool {
		return dgmpp_facility_is_configured(handle) != 0
	}
	
	public var name: String {
		return String(cString: dgmpp_facility_get_name(handle));
	}


}
