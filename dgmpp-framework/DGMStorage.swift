//
//  DGMStorage.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMStorage: DGMFacility {
	
	public required init(_ opaque: dgmpp_facility_ptr) {
		super.init(opaque)
	}
	
	public var states: [DGMState] {
		return DGMArray<DGMState>(dgmpp_storage_get_states(opaque)).array
	}
	
}

public class DGMSpaceport: DGMStorage {
	
	public required init(_ opaque: dgmpp_facility_ptr) {
		super.init(opaque)
	}
}

public class DGMCommandCenter: DGMStorage {
	
	public required init(_ opaque: dgmpp_facility_ptr) {
		super.init(opaque)
	}
}
