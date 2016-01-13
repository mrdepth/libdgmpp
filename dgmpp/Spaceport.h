#pragma once
#include "StorageFacility.h"

namespace dgmpp {
	class Spaceport: public StorageFacility {
	public:
		enum {
			GROUP_ID = 1030
		};
		Spaceport(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() {return GROUP_ID;};
	private:
	};
}