#include "LocationRequiredSkillModifier.h"
#include "Item.h"
#include "Attribute.h"
#include <sstream>

using namespace dgmpp;

LocationRequiredSkillModifier::LocationRequiredSkillModifier(Domain domain, AttributeID attributeID, Association association, std::shared_ptr<Attribute>  const&modifier, TypeID skillID, bool isAssistance, bool isOffensive, Character* character) : Modifier(domain, attributeID, association, modifier, isAssistance, isOffensive, character), skillID_(skillID)
{
	
}

LocationRequiredSkillModifier::~LocationRequiredSkillModifier()
{
}

bool LocationRequiredSkillModifier::isMatch(Item* item) const
{
	return item->requireSkill(skillID_);
}

std::string LocationRequiredSkillModifier::print() {
	std::stringstream s;
	s << "{\"skillID\":\"" << static_cast<int>(skillID_)
	<< "\", \"association\":\"" << getAssociationName()
	<< "\", \"attributeID\":\"" << static_cast<int>(getAttributeID())
	<< "\", \"modifier\":" << *getModifier() << "}";
	return s.str();
}

