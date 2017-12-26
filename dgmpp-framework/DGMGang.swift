//
//  DGMGang.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMGang: DGMType {
	
	public convenience init() throws {
		self.init(dgmpp_gang_create()!, owned: true)
	}

	public func add(_ pilot: DGMCharacter) {
		dgmpp_gang_add_pilot(handle, pilot.handle)
	}
	
	public func remove(_ pilot: DGMCharacter) {
		dgmpp_gang_remove_pilot(handle, pilot.handle)
	}
	
	public var pilots: [DGMCharacter] {
		return DGMArray<DGMCharacter>(dgmpp_gang_copy_pilots(handle)).array
	}

}
