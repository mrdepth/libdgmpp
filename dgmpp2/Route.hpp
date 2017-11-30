//
//  Route.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "MetaInfo.hpp"
#include "Commodity.hpp"

namespace dgmpp2 {
	class Facility;
	
	struct Route {
	public:
//		Route (Facility* from, Facility* to, const Commodity& commodity, int64_t identifier)
//		: from_(from), to_(to), commodity_(commodity), identifier_(identifier) {}
		
		Facility* const from;
		Facility* const to;
		const Commodity commodity;
		const int64_t identifier;

		
		bool operator== (const Route& other) const noexcept {
			return from == other.from && to == other.to && commodity == other.commodity && identifier == other.identifier;
		}

//	private:
//		friend class Planet;
//		friend class std::hash<Route>;
	};
}


namespace std {
	template<>
	struct hash<dgmpp2::Route> {
		typedef dgmpp2::Route argument_type;
		typedef size_t result_type;
		
		constexpr result_type operator()(const argument_type& value) const noexcept {
			return dgmpp2::hashValue(value.from, value.to, value.commodity, value.identifier);
		}
		
	};
};

