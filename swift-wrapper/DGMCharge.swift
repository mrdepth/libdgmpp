//
//  DGMCharge.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMCharge: DGMType, Codable {
	public enum Size: Int {
		case none = 0
		case small = 1
		case medium = 2
		case large = 3
		case xLarge = 4
	}
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_charge_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type)
	}

	public convenience init(_ other: DGMCharge) {
		self.init(dgmpp_charge_copy(other.handle))
	}

	public var size: Size {
		return Size(dgmpp_charge_get_charge_size(handle)) ?? .none
	}
	
	
	required init(_ handle: dgmpp_handle) {
		super.init(handle)
	}
	
	public convenience required init(from decoder: Decoder) throws {
		let typeID = try decoder.singleValueContainer().decode(DGMTypeID.self)
		try self.init(typeID: typeID)
	}
	
	public func encode(to encoder: Encoder) throws {
		var container = encoder.singleValueContainer()
		try container.encode(typeID)
	}
	
}
