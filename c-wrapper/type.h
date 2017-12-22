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

DGMPP_EXTERN dgmpp_type_id			dgmpp_type_get_type_id		(dgmpp_type type);
DGMPP_EXTERN dgmpp_group_id			dgmpp_type_get_group_id		(dgmpp_type type);
DGMPP_EXTERN dgmpp_category_id		dgmpp_type_get_category_id	(dgmpp_type type);
DGMPP_EXTERN BOOL					dgmpp_type_get_parent		(dgmpp_type type, dgmpp_type* parent);
DGMPP_EXTERN BOOL					dgmpp_type_get_attribute	(dgmpp_type type, dgmpp_attribute_id attribute_id, dgmpp_attribute* attribute);
DGMPP_EXTERN BOOL					dgmpp_type_get_affectors	(dgmpp_type type, dgmpp_array* affectors);
DGMPP_EXTERN BOOL					dgmpp_type_get_attributes	(dgmpp_type type, dgmpp_array* attributes);
DGMPP_EXTERN size_t					dgmpp_type_get_identifier	(dgmpp_type type);
DGMPP_EXTERN void					dgmpp_type_set_identifier	(dgmpp_type type, size_t identifier);

#endif /* type_h */
