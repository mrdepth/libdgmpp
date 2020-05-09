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
		self.init(type)
	}

	public convenience init(_ other: DGMStructure) {
		self.init(dgmpp_structure_copy(other.handle))
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
            willChange()
			dgmpp_structure_set_area(handle, newValue?.handle)
		}
	}
    
    enum StructureCodingKeys: String, CodingKey {
        case area
    }
    
    public override func encode(to encoder: Encoder) throws {
        try super.encode(to: encoder)
        var container = encoder.container(keyedBy: StructureCodingKeys.self)
        try container.encodeIfPresent(area, forKey: .area)
    }

    public required init(from decoder: Decoder) throws {
        try super.init(from: decoder)
        let container = try decoder.container(keyedBy: StructureCodingKeys.self)
        area = try container.decodeIfPresent(DGMArea.self, forKey: .area)
    }
    
    required init(_ handle: dgmpp_type) {
        super.init(handle)
    }
    
}
