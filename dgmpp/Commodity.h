#pragma once
#include "types.h"

namespace dgmpp {
	class Commodity {
	public:
		typedef std::runtime_error NotEnoughCommodities;

		Commodity(std::shared_ptr<Engine> const& engine, TypeID typeID);
		Commodity(const Commodity& other, int32_t quantity);
		void add(int32_t quantity);
		std::shared_ptr<Commodity> extract(int32_t quantity);
		
		TypeID typeID;
		int32_t quantity;
		float volume;
	};
}