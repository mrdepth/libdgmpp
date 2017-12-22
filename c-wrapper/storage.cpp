//
//  storage.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "storage.h"
#include "internal.h"

dgmpp_array dgmpp_storage_get_states (dgmpp_facility_ptr facility) {
	return dgmpp_make_array<dgmpp_state_impl*>(facility_cast<Storage*>(facility)->states());
}
