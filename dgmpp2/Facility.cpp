//
//  Facility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Facility.hpp"
#include <numeric>

namespace dgmpp2 {
	
	CubicMeter Facility::usedVolume() const {
		return std::accumulate(commodities_.begin(), commodities_.end(), CubicMeter(0), [](auto sum, const auto& i) {
			return sum + i.second.volume();
		});
	}
}
