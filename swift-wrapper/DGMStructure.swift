//
//  DGMStructure.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMStructure: DGMShip {
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_structure_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}

	public convenience init(_ other: DGMStructure) {
		self.init(dgmpp_structure_copy(other.handle), owned: true)
	}

	public var fuelBlockTypeID: DGMTypeID {
		return DGMTypeID(dgmpp_structure_get_fuel_block_type_id(handle))
	}
	
	public var fuelUse: DGMFuelUnitsPerHour {
		return DGMFuelUnitsPerHour(dgmpp_structure_get_fuel_use(handle))
	}
	
	public var area: DGMArea? {
		get {
			guard let area = dgmpp_structure_get_area(handle) else {return nil}
			return DGMArea(area)
		}
		set {
			dgmpp_structure_set_area(handle, newValue?.handle)
		}
	}

}
