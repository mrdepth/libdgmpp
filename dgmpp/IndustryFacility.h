#pragma once
#include "Facility.h"
#include "Storage.h"

namespace dgmpp {
	class IndustryFacility: public Facility, public Storage {
	public:
		enum {
			GROUP_ID = 1028
		};
		IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() {return GROUP_ID;};
	private:
	};
}