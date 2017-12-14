//
//  attribute.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef attribute_h
#define attribute_h

#include "utility.h"

void dgmpp_attribute_free (dgmpp_attribute_ptr attribute);

dgmpp_attribute_id	dgmpp_attribute_get_attribute_id	(dgmpp_attribute_ptr attribute);
dgmpp_type_ptr		dgmpp_attribute_get_owner			(dgmpp_attribute_ptr attribute);
double				dgmpp_attribute_get_value			(dgmpp_attribute_ptr attribute);
double				dgmpp_attribute_get_initial_value	(dgmpp_attribute_ptr attribute);
BOOL				dgmpp_attribute_is_stackable		(dgmpp_attribute_ptr attribute);
BOOL				dgmpp_attribute_high_is_good		(dgmpp_attribute_ptr attribute);

#endif /* attribute_h */
