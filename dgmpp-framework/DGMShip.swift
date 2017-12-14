//
//  DGMShip.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMShip: DGMType {
	
	override init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}

	public init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_ship_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		super.init(type)
	}
}
