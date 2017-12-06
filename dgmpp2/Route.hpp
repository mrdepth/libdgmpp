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
		Facility* const from;
		Facility* const to;
		const Commodity commodity;
//		const int64_t identifier;

		
		bool operator== (const Route& other) const noexcept {
//			return from == other.from && to == other.to && commodity == other.commodity && identifier == other.identifier;
			return from == other.from && to == other.to && commodity == other.commodity;
		}
		
		void update(std::chrono::seconds time) const;
	};
}


namespace std {
	template<>
	struct hash<dgmpp2::Route> {
		typedef dgmpp2::Route argument_type;
		typedef size_t result_type;
		
		result_type operator() (const argument_type& value) const noexcept;
	};
};

