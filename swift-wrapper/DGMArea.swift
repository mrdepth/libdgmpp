//
//  DGMArea.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMArea: DGMType, Codable {
	
	public convenience init(typeID: DGMTypeID) throws {
		guard let type = dgmpp_area_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
		self.init(type)
	}
	
	public convenience init(_ other: DGMArea) {
		self.init(dgmpp_area_copy(other.handle))
	}
    
    public convenience required init(from decoder: Decoder) throws {
        let typeID = try decoder.container(keyedBy: CodingKeys.self).decode(DGMTypeID.self, forKey: .typeID)
        try self.init(typeID: typeID)
    }
    
    public func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(typeID, forKey: .typeID)
    }
    
    enum CodingKeys: String, CodingKey {
        case typeID
    }

}
