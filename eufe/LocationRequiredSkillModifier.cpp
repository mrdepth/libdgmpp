#include "LocationRequiredSkillModifier.h"
#include "Item.h"
#include "Attribute.h"

using namespace eufe;

LocationRequiredSkillModifier::LocationRequiredSkillModifier(TypeID attributeID, Association association, std::shared_ptr<Attribute> modifier, TypeID skillID, bool isAssistance, bool isOffensive, std::shared_ptr<Character> character) : Modifier(attributeID, association, modifier, isAssistance, isOffensive, character), skillID_(skillID)
{
	
}

LocationRequiredSkillModifier::~LocationRequiredSkillModifier()
{
}

bool LocationRequiredSkillModifier::isMatch(std::shared_ptr<Item> item) const
{
	return item->requireSkill(skillID_);
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::LocationRequiredSkillModifier& modifier)
{
	os	<< "{\"skillID\":\"" << modifier.skillID_
	<< "\", \"association\":\"" << modifier.getAssociationName()
	<< "\", \"attributeID\":\"" << modifier.getAttributeID()
	<< "\", \"modifier\":" << *modifier.getModifier() << "}";
	return os;
}

