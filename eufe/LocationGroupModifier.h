#pragma once
#include "Modifier.h"

namespace eufe {
	
	class LocationGroupModifier : public Modifier
	{
	public:
		LocationGroupModifier(TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, TypeID groupID, bool isAssistance, bool isOffensive, std::shared_ptr<Character> const& character = nullptr);
		virtual ~LocationGroupModifier(void);
		virtual bool isMatch(std::shared_ptr<Item> const& item) const;
		TypeID getGroupID() const {return groupID_;}
		
		friend std::ostream& operator<<(std::ostream& os, LocationGroupModifier& modifier);
		
	private:
		TypeID groupID_;
	};
	
}