//
//  type.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef type_h
#define type_h

#include "utility.h"
#include "attribute.h"

//struct dgmpp_attribute;

DGMPP_EXTERN void dgmpp_type_free (dgmpp_type_ptr type);
DGMPP_EXTERN void dgmpp_type_take_ownership (dgmpp_type_ptr type);

DGMPP_EXTERN dgmpp_type_id				dgmpp_type_get_type_id		(dgmpp_type_ptr type);
DGMPP_EXTERN dgmpp_group_id				dgmpp_type_get_group_id		(dgmpp_type_ptr type);
DGMPP_EXTERN dgmpp_category_id			dgmpp_type_get_category_id	(dgmpp_type_ptr type);
DGMPP_EXTERN dgmpp_type_ptr				dgmpp_type_get_parent		(dgmpp_type_ptr type);
DGMPP_EXTERN dgmpp_attribute_ptr			dgmpp_type_get_attribute	(dgmpp_type_ptr type, dgmpp_attribute_id attribute_id);
DGMPP_EXTERN dgmpp_types_array_ptr		dgmpp_type_get_affectors	(dgmpp_type_ptr type);
DGMPP_EXTERN dgmpp_attributes_array_ptr	dgmpp_type_get_attributes	(dgmpp_type_ptr type);

#endif /* type_h */
