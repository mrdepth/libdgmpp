//
//  DGMType.swift
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

import Foundation

public class DGMType {
	var opaque: dgmpp_type_ptr
	
	public required init(_ opaque: dgmpp_type_ptr) {
		self.opaque = opaque
	}
	
	
	deinit {
		dgmpp_release(opaque)
	}
	
	public var typeID: DGMTypeID {
		return DGMTypeID(dgmpp_type_get_type_id(opaque))
	}
	
	public var groupID: DGMGroupID {
		return DGMGroupID(dgmpp_type_get_group_id(opaque))
	}

	public var categoryID: DGMCategoryID {
		return DGMCategoryID(dgmpp_type_get_category_id(opaque))
	}
	
	public var parent: DGMType? {
		guard let parent = dgmpp_type_get_parent(opaque) else {return nil}
		return DGMType(parent)
	}
	
	public subscript(attributeID: DGMAttributeID) -> DGMAttribute? {
		guard let attribute = dgmpp_type_get_attribute(opaque, dgmpp_attribute_id(attributeID)) else {return nil}
		return DGMAttribute(attribute)
	}
	
	public var affectors: [DGMType] {
		return DGMArray<DGMType>(dgmpp_type_get_affectors(opaque)).array
	}
	
	public var attributes: [DGMAttribute] {
		return DGMArray<DGMAttribute>(dgmpp_type_get_attributes(opaque)).array
	}

}

extension DGMType: Hashable {
	
	public var hashValue: Int {
		return dgmpp_get_hash(opaque)
	}
	
	public static func ==(lhs: DGMType, rhs: DGMType) -> Bool {
		return lhs.hashValue == rhs.hashValue
	}
}

