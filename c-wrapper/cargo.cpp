//
//  cargo.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 4/16/20.
//

#include "cargo.h"
#include "internal.h"

dgmpp_type dgmpp_cargo_create (dgmpp_type_id type_id) {
    try {
        return new_handle(std::make_shared<Cargo>(static_cast<TypeID>(type_id)));
    }
    catch (...) {
        return nullptr;
    }
}

dgmpp_type dgmpp_cargo_copy (dgmpp_type charge) {
    try {
        return new_handle(std::make_shared<Cargo>(*get<Cargo>(charge)));
    }
    catch (...) {
        return nullptr;
    }
}

size_t dgmpp_cargo_get_quantity (dgmpp_type cargo) {
    return get<Cargo>(cargo)->quantity();
}

void dgmpp_cargo_set_quantity (dgmpp_type cargo, size_t quantity) {
    get<Cargo>(cargo)->quantity(quantity);
}

DGMPP_EXTERN dgmpp_cubic_meter dgmpp_cargo_get_volume (dgmpp_type cargo) {
    return get<Cargo>(cargo)->volume();
}
