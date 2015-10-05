#pragma once
#include "Modifier.h"

namespace eufe {
	
	class LocationRequiredSkillModifier : public Modifier
	{
	public:
		LocationRequiredSkillModifier(TypeID attributeID, Association association, Attribute* modifier, TypeID skillID, bool isAssistance, bool isOffensive, Character* character = NULL);
		virtual ~LocationRequiredSkillModifier(void);
		virtual bool isMatch(Item* item) const;
		TypeID getSkillID() const {return skillID_;}

		friend std::ostream& operator<<(std::ostream& os, LocationRequiredSkillModifier& modifier);

	private:
		TypeID skillID_;
	};
	
}