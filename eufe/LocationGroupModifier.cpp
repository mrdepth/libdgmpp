#include "LocationGroupModifier.h"
#include "Item.h"
#include "Attribute.h"

using namespace eufe;

LocationGroupModifier::LocationGroupModifier(TypeID attributeID, Association association, Attribute* modifier, TypeID groupID, bool isAssistance, bool isOffensive, Character* character) : Modifier(attributeID, association, modifier, isAssistance, isOffensive, character), groupID_(groupID)
{
	
}

LocationGroupModifier::~LocationGroupModifier()
{
}

bool LocationGroupModifier::isMatch(Item* item) const
{
	return item->getGroupID() == groupID_;
}

#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::LocationGroupModifier& modifier)
{
	os	<< "{\"groupID\":\"" << modifier.groupID_
	<< "\", \"association\":\"" << modifier.getAssociationName()
	<< "\", \"attributeID\":\"" << modifier.getAttributeID()
	<< "\", \"modifier\":" << *modifier.getModifier() << "}";
	return os;
}

#endif