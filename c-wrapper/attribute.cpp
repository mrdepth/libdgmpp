//
//  attribute.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "attribute.h"
#include "internal.h"

void dgmpp_attribute_free (dgmpp_attribute_ptr attribute) {
	delete reinterpret_cast<dgmpp_attribute_impl*>(attribute);
}

void dgmpp_attribute_take_ownership (dgmpp_attribute_ptr attribute) {
	reinterpret_cast<dgmpp_attribute_impl*>(attribute)->owned = false;
}

dgmpp_attribute_id dgmpp_attribute_get_attribute_id (dgmpp_attribute_ptr attribute) {
	return static_cast<dgmpp_attribute_id>(reinterpret_cast<dgmpp_attribute_impl*>(attribute)->attribute->metaInfo().attributeID);
}

dgmpp_type_ptr dgmpp_attribute_get_owner (dgmpp_attribute_ptr attribute) {
	auto parent = &reinterpret_cast<dgmpp_attribute_impl*>(attribute)->attribute->owner();
	return dgmpp_make_type(parent);
}

double dgmpp_attribute_get_value (dgmpp_attribute_ptr attribute) {
	return reinterpret_cast<dgmpp_attribute_impl*>(attribute)->attribute->value();
}

double dgmpp_attribute_get_initial_value (dgmpp_attribute_ptr attribute) {
	return reinterpret_cast<dgmpp_attribute_impl*>(attribute)->attribute->initialValue();
}

BOOL dgmpp_attribute_is_stackable (dgmpp_attribute_ptr attribute) {
	return reinterpret_cast<dgmpp_attribute_impl*>(attribute)->attribute->metaInfo().isStackable;
}

BOOL dgmpp_attribute_high_is_good (dgmpp_attribute_ptr attribute) {
	return reinterpret_cast<dgmpp_attribute_impl*>(attribute)->attribute->metaInfo().highIsGood;
}
