//
//  Storage.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Storage.hpp"

namespace dgmpp2 {
    
    void Storage::update(std::chrono::seconds time) {
        Facility::update(time);
        
        if (!states_.empty()) {
            const auto& state = states_.back();
            if (state->timestamp < time) {
                auto c = commodities();
                if (state->commodities != c)
                    states_.emplace_back(new State{time, std::move(c)});
            }
            else
                state->commodities = commodities();
        }
        else
            states_.emplace_back(new State{time, commodities()});
    }
}
