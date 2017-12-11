#pragma once
#include "StorageFacility.h"
#include "Route.h"

namespace dgmpp {
	class CommandCenter: public StorageFacility {
	public:
		
		static const GroupID groupID = GroupID::commandCenters;

		CommandCenter(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual GroupID getGroupID() const {return groupID;};
	};
}