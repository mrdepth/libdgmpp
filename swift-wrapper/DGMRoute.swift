//
//  DGMRoute.swift
//  Dgmpp iOS
//
//  Created by Artem Shimanski on 3/31/20.
//

import Foundation
import cwrapper

public struct DGMRoute {
    
    public var from: DGMFacility?
    public var to: DGMFacility?
    public var commodity: DGMCommodity

    init(_ handle: dgmpp_handle) {
        from = dgmpp_route_copy_from(handle).map{DGMFacility.facility($0)}
        to = dgmpp_route_copy_to(handle).map{DGMFacility.facility($0)}
        commodity = DGMCommodity(dgmpp_route_get_commodity(handle))
    }
    
    public init(from: DGMFacility, to: DGMFacility, commodity: DGMCommodity) {
        self.from = from
        self.to = to
        self.commodity = commodity
    }
    
}
