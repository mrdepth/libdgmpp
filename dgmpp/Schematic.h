#pragma once
#include "types.h"

namespace dgmpp {
	class Schematic {
	public:
		Schematic(std::shared_ptr<Engine> const& engine, TypeID schematicID);
	private:
		TypeID schematicID_;
		double cycleTime_;
		std::string schematicName_;
		std::list<std::shared_ptr<const Commodity>> inputs_;
		std::shared_ptr<const Commodity> output_;
	};
}