//
//  type.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "type.h"
#include "internal.h"

DGMPP_TYPE dgmpp_get_type (dgmpp_type type) {
	auto base = reinterpret_cast<Type*>(type);
	if (dynamic_cast<Gang*>(base))
		return DGMPP_TYPE_GANG;
	else if (dynamic_cast<Character*>(base))
		return DGMPP_TYPE_CHARACTER;
	else if (dynamic_cast<Skill*>(base))
		return DGMPP_TYPE_SKILL;
	else if (dynamic_cast<Implant*>(base))
		return DGMPP_TYPE_IMPLANT;
	else if (dynamic_cast<Booster*>(base))
		return DGMPP_TYPE_BOOSTER;
	else if (dynamic_cast<Structure*>(base))
		return DGMPP_TYPE_STRUCTURE;
	else if (dynamic_cast<Ship*>(base))
		return DGMPP_TYPE_SHIP;
	else if (dynamic_cast<Module*>(base))
		return DGMPP_TYPE_MODULE;
	else if (dynamic_cast<Drone*>(base))
		return DGMPP_TYPE_DRONE;
	else if (dynamic_cast<Charge*>(base))
		return DGMPP_TYPE_CHARGE;
	else
		return DGMPP_TYPE_NONE;
}


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
	return (*reinterpret_cast<Type*>(type))[static_cast<AttributeID>(attribute_id)];
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

DGMPP_META_GROUP dgmpp_type_get_meta_group (dgmpp_type type) {
	return static_cast<DGMPP_META_GROUP>(reinterpret_cast<Type*>(type)->metaInfo().metaGroup);
}

size_t dgmpp_type_get_meta_level (dgmpp_type type) {
	return reinterpret_cast<Type*>(type)->metaInfo().metaLevel;
}
