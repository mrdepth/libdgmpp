//
//  charge.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef charge_h
#define charge_h

#include "type.h"

dgmpp_type_ptr dgmpp_charge_create (dgmpp_type_id type_id);

DGMPP_CHARGE_SIZE dgmpp_charge_get_charge_size (dgmpp_type_ptr charge);

#endif /* charge_h */
