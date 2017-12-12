//
//  dgm.swift
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

import Foundation

public extension DGMShip {
	@nonobjc public var supportedDroneCategories: [DGMCategoryID] {
		return __supportedDroneCategories.map {$0.intValue as DGMCategoryID}
	}
}

public extension DGMModule {
	@nonobjc public var availableStates: [DGMModuleState] {
		return __availableStates.flatMap {DGMModuleState(rawValue: $0.intValue)}
	}
	
	@nonobjc public var chargeGroups: [DGMGroupID] {
		return __chargeGroups.map {$0.intValue as DGMGroupID}
	}
}

