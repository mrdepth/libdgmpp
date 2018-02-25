//
//  DGMGang.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMGang: DGMType {
	
	public convenience init() throws {
		self.init(dgmpp_gang_create()!, owned: true)
	}

	public convenience init(_ other: DGMGang) {
		self.init(dgmpp_gang_copy(other.handle), owned: true)
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
	
	public var factorReload: Bool {
		get {
			return dgmpp_gang_get_factor_reload(handle) != 0
		}
		set {
			
			dgmpp_gang_set_factor_reload(handle, newValue ? 1 : 0)
		}
	}
	
	public var area: DGMArea? {
		get {
			guard let area = dgmpp_gang_get_area(handle) else {return nil}
			return DGMArea(area)
		}
		set {
			dgmpp_gang_set_area(handle, newValue?.handle)
		}
	}


}
