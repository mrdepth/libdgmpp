#pragma once
#include "Modifier.h"

namespace dgmpp {
	
	class LocationRequiredSkillModifier : public Modifier
	{
	public:
		LocationRequiredSkillModifier(Domain domain, TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, TypeID skillID, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~LocationRequiredSkillModifier(void);
		virtual bool isMatch(Item* item) const;
		TypeID getSkillID() const {return skillID_;}

		virtual std::string print();

	private:
		TypeID skillID_;
	};
	
}
