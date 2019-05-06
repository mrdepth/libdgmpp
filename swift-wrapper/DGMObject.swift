//
//  DGMObject.swift
//  dgmpp
//
//  Created by Artem Shimanski on 26.12.2017.
//

import Foundation
import cwrapper

public class DGMObject {
	var handle: dgmpp_handle
	let owned: Bool
	
	public required init(_ handle: dgmpp_handle, owned: Bool) {
		self.handle = handle
		self.owned = owned
	}
	
	deinit {
		if owned {
			dgmpp_free(handle)
		}
	}
	
}


extension DGMObject: Hashable {
	
	public func hash(into hasher: inout Hasher) {
		hasher.combine(handle)
	}
	
	public static func ==(lhs: DGMObject, rhs: DGMObject) -> Bool {
		return lhs.handle == rhs.handle
	}
}

