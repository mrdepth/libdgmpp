#pragma once
#include "Facility.h"

namespace dgmpp {
	class StorageFacility: public Facility {
	public:
		
		static const GroupID groupID = GroupID::storageFacilities;
		
		StorageFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual GroupID getGroupID() const {return groupID;};
		
	protected:
		virtual void update(double cycleTime);
		virtual int priority() const {return 900;};

	private:
		bool full_;
	};
}
