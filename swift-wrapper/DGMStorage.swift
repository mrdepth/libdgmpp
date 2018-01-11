//
//  DGMStorage.swift
//  dgmpp
//
//  Created by Artem Shimanski on 19.12.2017.
//

import Foundation

public class DGMStorage: DGMFacility {
	
	public var states: [DGMState] {
		return DGMArray<DGMState>(dgmpp_storage_copy_states(handle)).array
	}
	
}

public class DGMSpaceport: DGMStorage {
}

public class DGMCommandCenter: DGMStorage {
}
