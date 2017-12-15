//
//  DGMAttirbute.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMAttribute {
	private var opaque: dgmpp_attribute_ptr
	
	init(_ opaque: dgmpp_attribute_ptr) {
		self.opaque = opaque
	}
	
	deinit {
		dgmpp_attribute_free(opaque)
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

