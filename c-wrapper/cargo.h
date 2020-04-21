//
//  cargo.h
//  dgmpp
//
//  Created by Artem Shimanski on 4/16/20.
//

#ifndef cargo_h
#define cargo_h

#include "type.h"

DGMPP_EXTERN dgmpp_type dgmpp_cargo_create (dgmpp_type_id type_id);
DGMPP_EXTERN dgmpp_type dgmpp_cargo_copy (dgmpp_type cargo);

DGMPP_EXTERN size_t dgmpp_cargo_get_quantity (dgmpp_type cargo);
DGMPP_EXTERN void   dgmpp_cargo_set_quantity (dgmpp_type cargo, size_t quantity);
DGMPP_EXTERN dgmpp_cubic_meter dgmpp_cargo_get_volume (dgmpp_type cargo);


#endif /* cargo_h */
