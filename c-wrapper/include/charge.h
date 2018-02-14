//
//  charge.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef charge_h
#define charge_h

#include "type.h"

DGMPP_EXTERN dgmpp_type dgmpp_charge_create (dgmpp_type_id type_id);
DGMPP_EXTERN dgmpp_type dgmpp_charge_copy (dgmpp_type charge);

DGMPP_EXTERN DGMPP_CHARGE_SIZE dgmpp_charge_get_charge_size (dgmpp_type charge);

#endif /* charge_h */
