#pragma once
#include "Facility.h"
#include "Storage.h"

namespace dgmpp {
	class StorageFacility: public Facility, public Storage {
	public:
		StorageFacility(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<CommandCenter> const& owner = std::shared_ptr<CommandCenter>(nullptr));
	private:
	};
}