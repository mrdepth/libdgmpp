#pragma once
#include "Modifier.h"

namespace dgmpp {
	
	class LocationGroupModifier : public Modifier
	{
	public:
		LocationGroupModifier(Domain domain, TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, TypeID groupID, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~LocationGroupModifier(void);
		virtual bool isMatch(Item* item) const;
		TypeID getGroupID() const {return groupID_;}
		
		virtual std::string print();
		
	private:
		TypeID groupID_;
	};
	
}
