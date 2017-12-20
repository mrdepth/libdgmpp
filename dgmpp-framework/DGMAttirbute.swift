//
//  DGMAttirbute.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMAttribute {
	fileprivate var opaque: dgmpp_attribute_ptr
	
	public required init(_ opaque: dgmpp_attribute_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_release(opaque)
	}

	public var attributeID: DGMAttributeID {
		return DGMAttributeID(dgmpp_attribute_get_attribute_id(opaque))
	}
	
	public var owner: DGMType {
		return DGMType(dgmpp_attribute_get_owner(opaque))
	}

	public var value: Double {
		return dgmpp_attribute_get_value(opaque)
	}

	public var initialValue: Double {
		return dgmpp_attribute_get_initial_value(opaque)
	}

}

extension DGMAttribute: Hashable {
	
	public var hashValue: Int {
		return dgmpp_get_hash(opaque)
	}
	
	public static func ==(lhs: DGMAttribute, rhs: DGMAttribute) -> Bool {
		return lhs.hashValue == rhs.hashValue
	}
}

