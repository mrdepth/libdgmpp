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

DGMPP_EXTERN DGMPP_TYPE				dgmpp_get_type				(dgmpp_type type);

DGMPP_EXTERN dgmpp_type_id			dgmpp_type_get_type_id		(dgmpp_type type);
DGMPP_EXTERN dgmpp_group_id			dgmpp_type_get_group_id		(dgmpp_type type);
DGMPP_EXTERN dgmpp_category_id		dgmpp_type_get_category_id	(dgmpp_type type);
DGMPP_EXTERN dgmpp_type				dgmpp_type_get_parent		(dgmpp_type type);
DGMPP_EXTERN dgmpp_attribute		dgmpp_type_get_attribute	(dgmpp_type type, dgmpp_attribute_id attribute_id);
DGMPP_EXTERN dgmpp_array			dgmpp_type_copy_affectors	(dgmpp_type type);
DGMPP_EXTERN dgmpp_array			dgmpp_type_copy_attributes	(dgmpp_type type);
DGMPP_EXTERN size_t					dgmpp_type_get_identifier	(dgmpp_type type);
DGMPP_EXTERN void					dgmpp_type_set_identifier	(dgmpp_type type, size_t identifier);
DGMPP_EXTERN DGMPP_META_GROUP		dgmpp_type_get_meta_group	(dgmpp_type type);
DGMPP_EXTERN size_t					dgmpp_type_get_meta_level	(dgmpp_type type);
#endif /* type_h */
