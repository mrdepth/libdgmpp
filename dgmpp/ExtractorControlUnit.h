#pragma once
#include "Facility.h"

namespace dgmpp {
	class ExtractorControlUnit: public Facility {
	public:
		ExtractorControlUnit(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<CommandCenter> const& owner = std::shared_ptr<CommandCenter>(nullptr));
	private:
	};
}