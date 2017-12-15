//
//  Route.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Route.hpp"
#include "Facility.hpp"

#include <iostream>

namespace dgmpp {

	void Route::update(std::chrono::seconds time) const {
		auto c = std::min((*from)[commodity], to->free(commodity));
		if (c.quantity() > 0) {
			from->extract(c);
			to->add(c);
			to->update(time);
		}
	}
}

/*namespace std {
	template<>
	struct hash<dgmpp::Route> {
		typedef dgmpp::Route argument_type;
		typedef size_t result_type;
		
		constexpr result_type operator()(const argument_type& value) const noexcept {
			//			return dgmpp::hashValue(value.from, value.to, value.commodity, value.identifier);
			return dgmpp::hashValue(value.from->identifier(), value.to->identifier(), value.commodity);
		}
		
	};
};

*/

namespace std {
	hash<dgmpp::Route>::result_type hash<dgmpp::Route>::operator() (const hash<dgmpp::Route>::argument_type& value) const noexcept {
		return dgmpp::hashValue(value.from, value.to, value.commodity);
		
//		return dgmpp::hashValue(value.from->identifier(), value.to->identifier(), value.commodity);
	}
}

