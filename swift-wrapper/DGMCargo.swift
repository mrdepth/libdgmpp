//
//  DGMCargo.swift
//  dgmpp
//
//  Created by Artem Shimanski on 4/16/20.
//

import Foundation
import cwrapper

public class DGMCargo: DGMType {

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
    
    public convenience required init(from decoder: Decoder) throws {
        let typeID = try decoder.singleValueContainer().decode(DGMTypeID.self)
        try self.init(typeID: typeID)
    }
    
    public func encode(to encoder: Encoder) throws {
        var container = encoder.singleValueContainer()
        try container.encode(typeID)
    }
    
}
