#pragma once
#include "Modifier.h"

namespace dgmpp {
	
	class LocationGroupModifier : public Modifier
	{
	public:
		LocationGroupModifier(Domain domain, AttributeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, GroupID groupID, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~LocationGroupModifier(void);
		virtual bool isMatch(Item* item) const;
		GroupID getGroupID() const {return groupID_;}
		
		virtual std::string print();
		
	private:
		GroupID groupID_;
	};
	
}
