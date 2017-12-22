//
//  attribute.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "attribute.h"
#include "internal.h"

dgmpp_attribute_id dgmpp_attribute_get_attribute_id (dgmpp_attribute attribute) {
	return static_cast<dgmpp_attribute_id>(dgmpp_cast<Attribute>(attribute).metaInfo().attributeID);
}

BOOL dgmpp_attribute_get_owner (dgmpp_attribute attribute, dgmpp_type* owner) {
	*owner = dgmpp_handle_impl(&dgmpp_cast<Attribute>(attribute).owner());
	return true;
}

double dgmpp_attribute_get_value (dgmpp_attribute attribute) {
	return dgmpp_cast<Attribute>(attribute).value();
}

double dgmpp_attribute_get_initial_value (dgmpp_attribute attribute) {
	return dgmpp_cast<Attribute>(attribute).initialValue();
}

BOOL dgmpp_attribute_is_stackable (dgmpp_attribute attribute) {
	return dgmpp_cast<Attribute>(attribute).metaInfo().isStackable;
}

BOOL dgmpp_attribute_high_is_good (dgmpp_attribute attribute) {
	return dgmpp_cast<Attribute>(attribute).metaInfo().highIsGood;
}
