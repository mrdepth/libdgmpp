//
//  type.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "type.h"
#include "internal.h"

dgmpp_type_id dgmpp_type_get_type_id (dgmpp_type type) {
	return static_cast<dgmpp_type_id>(dgmpp_cast<Type>(type).metaInfo().typeID);
}

dgmpp_group_id dgmpp_type_get_group_id (dgmpp_type type) {
	return static_cast<dgmpp_group_id>(dgmpp_cast<Type>(type).metaInfo().groupID);
}

dgmpp_category_id dgmpp_type_get_category_id (dgmpp_type type) {
	return static_cast<dgmpp_category_id>(dgmpp_cast<Type>(type).metaInfo().categoryID);
}

BOOL dgmpp_type_get_parent (dgmpp_type type, dgmpp_type* parent) {
	if (auto p = dgmpp_cast<Type>(type).parent()) {
		*parent = dgmpp_handle_impl(p);
		return true;
	}
	else
		return false;
}

BOOL dgmpp_type_get_attribute (dgmpp_type type, dgmpp_attribute_id attribute_id, dgmpp_attribute* attribute) {
	if (auto a = dgmpp_cast<Type>(type)[static_cast<AttributeID>(attribute_id)]) {
		*attribute = dgmpp_handle_impl(a.get());
		return true;
	}
	else
		return false;
}

BOOL dgmpp_type_get_affectors (dgmpp_type type, dgmpp_array* affectors) {
	*affectors = dgmpp_make_array<dgmpp_handle_impl>(dgmpp_cast<Type>(type).affectors());
	return true;
}

BOOL dgmpp_type_get_attributes (dgmpp_type type, dgmpp_array* attributes) {
	*attributes = dgmpp_make_array<dgmpp_handle_impl>(dgmpp_cast<Type>(type).attributes());
	return true;
}

size_t dgmpp_type_get_identifier (dgmpp_type type) {
	return dgmpp_cast<Type>(type).identifier();
}

void dgmpp_type_set_identifier (dgmpp_type type, size_t identifier) {
	dgmpp_cast<Type>(type).identifier(identifier);
}
