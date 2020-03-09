//
//  DGMArea.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMArea: DGMType {
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_area_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type)
	}
	
	public convenience init(_ other: DGMArea) {
		self.init(dgmpp_area_copy(other.handle))
	}
}
