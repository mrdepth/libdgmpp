#pragma once
#include "StorageFacility.h"

namespace dgmpp {
	class Spaceport: public StorageFacility {
	public:
		Spaceport(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<CommandCenter> const& owner = std::shared_ptr<CommandCenter>(nullptr));
	private:
	};
}