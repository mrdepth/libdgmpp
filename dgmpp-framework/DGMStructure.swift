//
//  DGMStructure.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMStructure: DGMShip {
	
	public override init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_structure_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}

	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}

	public var fuelBlockTypeID: DGMTypeID {
		return DGMTypeID(dgmpp_structure_get_fuel_block_type_id(opaque))
	}
	
	public var fuelUse: DGMFuelUnitsPerHour {
		return DGMFuelUnitsPerHour(dgmpp_structure_get_fuel_use(opaque))
	}
}
