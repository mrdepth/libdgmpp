#include "LocationGroupModifier.h"
#include "Item.h"
#include "Attribute.h"

using namespace eufe;

LocationGroupModifier::LocationGroupModifier(TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, TypeID groupID, bool isAssistance, bool isOffensive, std::shared_ptr<Character> const& character) : Modifier(attributeID, association, modifier, isAssistance, isOffensive, character), groupID_(groupID)
{
	
}

LocationGroupModifier::~LocationGroupModifier()
{
}

bool LocationGroupModifier::isMatch(std::shared_ptr<Item> const& item) const
{
	return item->getGroupID() == groupID_;
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::LocationGroupModifier& modifier)
{
	os	<< "{\"groupID\":\"" << modifier.groupID_
	<< "\", \"association\":\"" << modifier.getAssociationName()
	<< "\", \"attributeID\":\"" << modifier.getAttributeID()
	<< "\", \"modifier\":" << *modifier.getModifier() << "}";
	return os;
}
