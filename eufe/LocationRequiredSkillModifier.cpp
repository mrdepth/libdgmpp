#include "LocationRequiredSkillModifier.h"
#include "Item.h"
#include "Attribute.h"
#include <sstream>

using namespace eufe;

LocationRequiredSkillModifier::LocationRequiredSkillModifier(TypeID attributeID, Association association, std::shared_ptr<Attribute>  const&modifier, TypeID skillID, bool isAssistance, bool isOffensive, Character* character) : Modifier(attributeID, association, modifier, isAssistance, isOffensive, character), skillID_(skillID)
{
	
}

LocationRequiredSkillModifier::~LocationRequiredSkillModifier()
{
}

bool LocationRequiredSkillModifier::isMatch(std::shared_ptr<Item> const& item) const
{
	return item->requireSkill(skillID_);
}

std::string LocationRequiredSkillModifier::print() {
	std::stringstream s;
	s << "{\"skillID\":\"" << skillID_
	<< "\", \"association\":\"" << getAssociationName()
	<< "\", \"attributeID\":\"" << getAttributeID()
	<< "\", \"modifier\":" << *getModifier() << "}";
	return s.str();
}

