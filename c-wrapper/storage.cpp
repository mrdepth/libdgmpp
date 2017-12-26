//
//  storage.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "storage.h"
#include "internal.h"

dgmpp_array dgmpp_storage_copy_states (dgmpp_facility facility) {
	return dgmpp_make_array<State*>(reinterpret_cast<Storage*>(facility)->states());
}
