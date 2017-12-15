#pragma once
#include "StorageFacility.h"

namespace dgmpp {
	class Spaceport: public StorageFacility {
	public:
		static const GroupID groupID = GroupID::spaceports;
		
		Spaceport(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual GroupID getGroupID() const {return groupID;};
		
	protected:
		virtual int priority() const {return 4;};
	private:
	};
}
