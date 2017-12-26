//
//  type.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "type.h"
#include "internal.h"

dgmpp_type_id dgmpp_type_get_type_id (dgmpp_type type) {
	return static_cast<dgmpp_type_id>(reinterpret_cast<Type*>(type)->metaInfo().typeID);
}

dgmpp_group_id dgmpp_type_get_group_id (dgmpp_type type) {
	return static_cast<dgmpp_group_id>(reinterpret_cast<Type*>(type)->metaInfo().groupID);
}

dgmpp_category_id dgmpp_type_get_category_id (dgmpp_type type) {
	return static_cast<dgmpp_category_id>(reinterpret_cast<Type*>(type)->metaInfo().categoryID);
}

dgmpp_type dgmpp_type_get_parent (dgmpp_type type) {
	return reinterpret_cast<Type*>(type)->parent();
}

dgmpp_attribute dgmpp_type_get_attribute (dgmpp_type type, dgmpp_attribute_id attribute_id) {
	if (auto a = (*reinterpret_cast<Type*>(type))[static_cast<AttributeID>(attribute_id)])
		return a.get();
	else
		return nullptr;
}

dgmpp_array dgmpp_type_copy_affectors (dgmpp_type type) {
	return dgmpp_make_array<Type*>(reinterpret_cast<Type*>(type)->affectors());
}

dgmpp_array dgmpp_type_copy_attributes (dgmpp_type type) {
	return dgmpp_make_array<Attribute*>(reinterpret_cast<Type*>(type)->attributes());
}

size_t dgmpp_type_get_identifier (dgmpp_type type) {
	return reinterpret_cast<Type*>(type)->identifier();
}

void dgmpp_type_set_identifier (dgmpp_type type, size_t identifier) {
	reinterpret_cast<Type*>(type)->identifier(identifier);
}
