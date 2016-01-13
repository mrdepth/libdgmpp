#pragma once
#include "types.h"

namespace dgmpp {
	class Schematic {
	public:
		Schematic(std::shared_ptr<Engine> const& engine, TypeID typeID);
	private:
		std::list<std::shared_ptr<const Commodity>> inputs_;
		std::shared_ptr<Commodity> output_;
	};
}