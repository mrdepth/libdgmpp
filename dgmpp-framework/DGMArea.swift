//
//  DGMArea.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMArea: DGMType {
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_area_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type, owned: true)
	}
}
