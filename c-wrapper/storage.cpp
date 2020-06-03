//
//  storage.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "storage.h"
#include "internal.h"

dgmpp_array dgmpp_storage_copy_states (dgmpp_facility facility) {
    const auto& states = get<Storage>(facility)->states();
    std::vector<State*> result;
    std::transform(states.begin(), states.end(), std::back_inserter(result), [](const auto& i) {
        return i.get();
    });
    return dgmpp_make_array<State*>(std::move(result));
}
