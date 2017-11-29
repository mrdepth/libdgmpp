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
	
	class Route {
	public:
		Route (Facility* from, Facility* to, const Commodity& commodity, int64_t identifier)
		: from_(from), to_(to), commodity_(commodity), identifier_(identifier) {}
		
		bool operator== (const Route& other) const noexcept {
			return from_ == other.from_ && to_ == other.to_ && commodity_ == other.commodity_ && identifier_ == other.identifier_;
		}

	private:
		friend class Planet;
		friend class std::hash<Route>;
		Facility* const from_;
		Facility* const to_;
		const Commodity commodity_;
		const int64_t identifier_;
	};
}


namespace std {
	template<>
	struct hash<dgmpp2::Route> {
		typedef dgmpp2::Route argument_type;
		typedef size_t result_type;
		
		constexpr result_type operator()(const argument_type& value) const noexcept {
			return dgmpp2::hashValue(value.from_, value.to_, value.commodity_, value.identifier_);
		}
		
	};
};

