#pragma once
#include "Facility.h"
#include "StorageCycle.h"

namespace dgmpp {
	class StorageFacility: public Facility {
	public:
		enum {
			GROUP_ID = 1029
		};
		StorageFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() const {return GROUP_ID;};
		virtual void startCycle(double cycleTime);
		virtual int priority() const {return 3;};
	private:
		bool full_;
	};
}