//
//  Cargo.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 4/16/20.
//

#pragma once
#include "Type.hpp"
#include <algorithm>

namespace dgmpp {
    class Cargo: public Type {
    public:
        Cargo (TypeID typeID);
        Cargo (const Cargo& other);
        
        std::size_t quantity() const { return quantity_;}
        void quantity(std::size_t newValue) { quantity_ = std::max(newValue, std::size_t(1)); }
        CubicMeter volume();
        
    private:
        std::size_t quantity_ = 1;
    };
}
