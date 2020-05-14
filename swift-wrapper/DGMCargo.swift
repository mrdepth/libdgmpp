//
//  DGMCargo.swift
//  dgmpp
//
//  Created by Artem Shimanski on 4/16/20.
//

import Foundation
import cwrapper

public class DGMCargo: DGMType, Codable {

    public convenience init(typeID: DGMTypeID) throws {
        guard let type = dgmpp_cargo_create(dgmpp_type_id(typeID)) else { throw DGMError.typeNotFound(typeID)}
        self.init(type)
    }

    public convenience init(_ other: DGMCharge) {
        self.init(dgmpp_cargo_copy(other.handle))
    }

    public var quantity: Int {
        get {
            dgmpp_cargo_get_quantity(handle)
        }
        set {
            willChange()
            dgmpp_cargo_set_quantity(handle, max(newValue, 1))
        }
    }
    
    public var volume: DGMCubicMeter {
        dgmpp_cargo_get_volume(handle)
    }
    
    
    required init(_ handle: dgmpp_handle) {
        super.init(handle)
    }
    
    enum CodingKeys: String, CodingKey {
        case typeID
        case quantity
    }
    
    public convenience required init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        let typeID = try container.decode(DGMTypeID.self, forKey: .typeID)
        try self.init(typeID: typeID)
        quantity = try container.decode(Int.self, forKey: .quantity)
    }
    
    public func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(typeID, forKey: .typeID)
        try container.encode(quantity, forKey: .quantity)
    }
    
}
