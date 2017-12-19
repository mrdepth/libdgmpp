//
//  DGMGang.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMGang: DGMType {
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		super.init(opaque)
	}
	
	public init() {
		super.init(dgmpp_gang_create()!)
	}
	
	public func add(_ pilot: DGMCharacter) {
		dgmpp_gang_add_pilot(opaque, pilot.opaque)
	}
	
	public func remove(_ implant: DGMImplant) {
		dgmpp_gang_remove_pilot(opaque, implant.opaque)
	}
	
	public var pilots: [DGMCharacter] {
		return DGMArray<DGMCharacter>(dgmpp_gang_get_pilots(opaque)).array
	}

}
