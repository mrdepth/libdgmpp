//
//  DGMAttirbute.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation
import cwrapper

public class DGMAttribute: DGMObject {
	
	convenience init(_ handle: dgmpp_attribute) {
		self.init(handle, owned: false)
	}
	
	public var attributeID: DGMAttributeID {
		return DGMAttributeID(dgmpp_attribute_get_attribute_id(handle))
	}
	
	public var owner: DGMType {
		return DGMType.type(dgmpp_attribute_get_owner(handle))
	}

	public var value: Double {
		return dgmpp_attribute_get_value(handle)
	}

	public var initialValue: Double {
		return dgmpp_attribute_get_initial_value(handle)
	}

}
