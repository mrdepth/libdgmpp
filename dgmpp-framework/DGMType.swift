//
//  DGMType.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMType: DGMObject {
	
	convenience init(_ handle: dgmpp_type) {
		self.init(handle, owned: false)
	}

	public var typeID: DGMTypeID {
		return DGMTypeID(dgmpp_type_get_type_id(handle))
	}
	
	public var groupID: DGMGroupID {
		return DGMGroupID(dgmpp_type_get_group_id(handle))
	}

	public var categoryID: DGMCategoryID {
		return DGMCategoryID(dgmpp_type_get_category_id(handle))
	}
	
	public var parent: DGMType? {
		guard let parent = dgmpp_type_get_parent(handle) else {return nil}
		return DGMType(parent)
	}
	
	public subscript(attributeID: DGMAttributeID) -> DGMAttribute? {
		guard let attribute = dgmpp_type_get_attribute(handle, dgmpp_attribute_id(attributeID)) else {return nil}
		return DGMAttribute(attribute)
	}
	
	public var affectors: [DGMType] {
		return DGMArray<DGMType>(dgmpp_type_copy_affectors(handle)).array
	}
	
	public var attributes: [DGMAttribute] {
		return DGMArray<DGMAttribute>(dgmpp_type_copy_attributes(handle)).array
	}
	
	public var identifier: Int {
		get {
			return dgmpp_type_get_identifier(handle)
		}
		set {
			dgmpp_type_set_identifier(handle, newValue)
		}
	}

}
