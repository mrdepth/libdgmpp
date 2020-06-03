//
//  Cargo.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 4/16/20.
//

#include "Cargo.hpp"
#include "SDE.hpp"

namespace dgmpp {
    Cargo::Cargo (TypeID typeID): Type(typeID) {
    }
    
    Cargo::Cargo (const Cargo& other): Type(other), quantity_(other.quantity_) {
    }

    CubicMeter Cargo::volume() {
        return static_cast<CubicMeter>((*this)[AttributeID::volume]->value() * quantity());
    }
}
