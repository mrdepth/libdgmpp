//
//  DGMCharge.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMCharge: DGMType {
	public enum Size: Int {
		case none = 0
		case small = 1
		case medium = 2
		case large = 3
		case xLarge = 4
	}
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_charge_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}

	public var size: Size {
		return Size(dgmpp_charge_get_charge_size(handle)) ?? .none
	}
}
