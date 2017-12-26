//
//  DGMStructure.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMStructure: DGMShip {
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_structure_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}

	public var fuelBlockTypeID: DGMTypeID {
		return DGMTypeID(dgmpp_structure_get_fuel_block_type_id(handle))
	}
	
	public var fuelUse: DGMFuelUnitsPerHour {
		return DGMFuelUnitsPerHour(dgmpp_structure_get_fuel_use(handle))
	}
}
