//
//  attribute.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef attribute_h
#define attribute_h

#include "utility.h"

DGMPP_EXTERN dgmpp_attribute_id	dgmpp_attribute_get_attribute_id	(dgmpp_attribute attribute);
DGMPP_EXTERN dgmpp_type			dgmpp_attribute_get_owner			(dgmpp_attribute attribute);
DGMPP_EXTERN double				dgmpp_attribute_get_value			(dgmpp_attribute attribute);
DGMPP_EXTERN double				dgmpp_attribute_get_initial_value	(dgmpp_attribute attribute);
DGMPP_EXTERN dgmpp_bool				dgmpp_attribute_is_stackable		(dgmpp_attribute attribute);
DGMPP_EXTERN dgmpp_bool				dgmpp_attribute_high_is_good		(dgmpp_attribute attribute);

#endif /* attribute_h */
