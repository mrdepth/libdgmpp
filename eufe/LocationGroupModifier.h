#pragma once
#include "Modifier.h"

namespace eufe {
	
	class LocationGroupModifier : public Modifier
	{
	public:
		LocationGroupModifier(TypeID attributeID, Association association, Attribute* modifier, TypeID groupID, bool isAssistance, bool isOffensive, Character* character = NULL);
		virtual ~LocationGroupModifier(void);
		virtual bool isMatch(Item* item) const;
		TypeID getGroupID() const {return groupID_;}
		
		friend std::ostream& operator<<(std::ostream& os, LocationGroupModifier& modifier);
		
	private:
		TypeID groupID_;
	};
	
}