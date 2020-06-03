//
//  attribute.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "attribute.h"
#include "internal.h"

dgmpp_attribute_id dgmpp_attribute_get_attribute_id (dgmpp_attribute attribute) {
	return static_cast<dgmpp_attribute_id>(reinterpret_cast<Attribute*>(attribute)->metaInfo().attributeID);
}

dgmpp_type dgmpp_attribute_copy_owner (dgmpp_attribute attribute) {
	return new_handle(reinterpret_cast<Attribute*>(attribute)->owner().shared_from_this());
}

double dgmpp_attribute_get_value (dgmpp_attribute attribute) {
	return reinterpret_cast<Attribute*>(attribute)->value();
}

double dgmpp_attribute_get_initial_value (dgmpp_attribute attribute) {
	return reinterpret_cast<Attribute*>(attribute)->initialValue();
}

dgmpp_bool dgmpp_attribute_is_stackable (dgmpp_attribute attribute) {
	return reinterpret_cast<Attribute*>(attribute)->metaInfo().isStackable;
}

dgmpp_bool dgmpp_attribute_high_is_good (dgmpp_attribute attribute) {
	return reinterpret_cast<Attribute*>(attribute)->metaInfo().highIsGood;
}

#if DEBUG
void dgmpp_attribute_dump_affectors (dgmpp_attribute attribute) {
	reinterpret_cast<Attribute*>(attribute)->dumpAffectors();
}
#endif
