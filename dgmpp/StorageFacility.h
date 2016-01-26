#pragma once
#include "Facility.h"

namespace dgmpp {
	class StorageFacility: public Facility {
	public:
		enum: TypeID {
			GROUP_ID = 1029
		};
		StorageFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() const {return GROUP_ID;};
		
	protected:
		virtual void update(double cycleTime);
		virtual int priority() const {return 900;};

	private:
		bool full_;
	};
}