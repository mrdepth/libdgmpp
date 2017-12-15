//
//  type.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "type.h"
#include "internal.h"

void dgmpp_type_free (dgmpp_type_ptr type) {
	if (type)
		delete reinterpret_cast<dgmpp_type_impl*>(type);
}

dgmpp_type_id dgmpp_type_get_type_id (dgmpp_type_ptr type) {
	return static_cast<dgmpp_type_id>(type_cast<Type*>(type)->metaInfo().typeID);
}

dgmpp_group_id dgmpp_type_get_group_id (dgmpp_type_ptr type) {
	return static_cast<dgmpp_group_id>(type_cast<Type*>(type)->metaInfo().groupID);
}

dgmpp_category_id dgmpp_type_get_category_id (dgmpp_type_ptr type) {
	return static_cast<dgmpp_category_id>(type_cast<Type*>(type)->metaInfo().categoryID);
}

dgmpp_type_ptr dgmpp_type_get_parent (dgmpp_type_ptr type) {
	return dgmpp_make_type(type_cast<Type*>(type)->parent());
}
dgmpp_attribute_ptr dgmpp_type_get_attribute (dgmpp_type_ptr type, dgmpp_attribute_id attribute_id) {
	if (auto attribute = (*type_cast<Type*>(type))[static_cast<AttributeID>(attribute_id)])
		return reinterpret_cast<dgmpp_attribute_ptr>(new dgmpp_attribute_impl {attribute.get()});
	else
		return nullptr;
}

dgmpp_types_array_ptr dgmpp_type_get_affectors (dgmpp_type_ptr type) {
	return new dgmpp_types_array_impl(type_cast<Type*>(type)->affectors());
}

dgmpp_attributes_array_ptr dgmpp_type_get_attributes (dgmpp_type_ptr type) {
	return new dgmpp_attributes_array_impl(type_cast<Type*>(type)->attributes());
}
