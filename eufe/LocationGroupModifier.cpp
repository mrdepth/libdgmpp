#include "LocationGroupModifier.h"
#include "Item.h"
#include "Attribute.h"
#include <sstream>

using namespace eufe;

LocationGroupModifier::LocationGroupModifier(TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, TypeID groupID, bool isAssistance, bool isOffensive, Character* character) : Modifier(attributeID, association, modifier, isAssistance, isOffensive, character), groupID_(groupID)
{
	
}

LocationGroupModifier::~LocationGroupModifier()
{
}

bool LocationGroupModifier::isMatch(std::shared_ptr<Item> const& item) const
{
	return item->getGroupID() == groupID_;
}

std::string LocationGroupModifier::print() {
	std::stringstream s;
	s << "{\"groupID\":\"" << groupID_
	<< "\", \"association\":\"" << getAssociationName()
	<< "\", \"attributeID\":\"" << getAttributeID()
	<< "\", \"modifier\":" << *getModifier() << "}";
	return s.str();
}
