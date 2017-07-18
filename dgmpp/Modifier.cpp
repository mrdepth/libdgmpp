#include "Modifier.h"
#include "Attribute.h"
#include "Item.h"
#include "Module.h"
#include <sstream>

using namespace dgmpp;

Modifier::Modifier(Domain domain, TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, bool isAssistance, bool isOffensive, Character* character) : domain_(domain), attributeID_(attributeID), association_(association), modifier_(modifier), isAssistance_(isAssistance), isOffensive_(isOffensive), character_(character)
{
}

Modifier::~Modifier()
{
}

bool Modifier::isMatch(std::shared_ptr<Item> const& item) const
{
	return true;
}

Modifier::Domain Modifier::getDomain() {
	return domain_;
}

TypeID Modifier::getAttributeID() const
{
	return attributeID_;
}

std::shared_ptr<Attribute> Modifier::getModifier() const
{
	return modifier_.lock();
}

Modifier::Association Modifier::getAssociation() const
{
	return association_;
}


Float Modifier::getValue() const
{
	auto modifier = modifier_.lock();
	if (!modifier)
		return 0;
	
	Float value = modifier->getValue();
	if (association_ == ASSOCIATION_POST_DIV)
		return static_cast<Float>(1.0 / value);
	else if (association_ == ASSOCIATION_POST_PERCENT)
		return static_cast<Float>(1.0 + value / 100.0);
	else if (association_ == ASSOCIATION_ADD_RATE || association_ == ASSOCIATION_SUB_RATE)
	{
		std::shared_ptr<Item> item = modifier->getOwner();
		if (!item)
			return 0;
		Float duration;
		if (item->hasAttribute(DURATION_ATTRIBUTE_ID))
			duration = static_cast<Float>(item->getAttribute(DURATION_ATTRIBUTE_ID)->getValue() / 1000.0);
		else if (item->hasAttribute(SPEED_ATTRIBUTE_ID))
			duration = static_cast<Float>(item->getAttribute(SPEED_ATTRIBUTE_ID)->getValue() / 1000.0);
		else
			duration = 1;
		return duration > 0.0 ? static_cast<Float>(value / duration) : 0.0;
	}
	else
		return value;
}

//bool Modifier::isStackable() const
//{
//	auto modifier = modifier_.lock();
//	return modifier ? modifier->isStackable() : false;
//}

Character* Modifier::getCharacter()
{
	return character_;
}

bool Modifier::isOffensive()
{
	return isOffensive_;
	
}

bool Modifier::isAssistance()
{
	return isAssistance_;
}

std::string Modifier::getAssociationName()
{
	switch (association_) {
		case ASSOCIATION_PRE_ASSIGNMENT:
			return "PreAssignment";
		case ASSOCIATION_MOD_ADD:
			return "ModAdd";
		case ASSOCIATION_MOD_SUB:
			return "ModSub";
		case ASSOCIATION_PRE_DIV:
			return "PreDiv";
		case ASSOCIATION_PRE_MUL:
			return "PreMul";
		case ASSOCIATION_POST_PERCENT:
			return "PostPercent";
		case ASSOCIATION_POST_DIV:
			return "PostDiv";
		case ASSOCIATION_POST_MUL:
			return "PostMul";
		case ASSOCIATION_POST_ASSIGNMENT:
			return "PostAssignment";
		case ASSOCIATION_SKILL_TIME:
			return "SkillTime";
		case ASSOCIATION_ADD_RATE:
			return "AddRate";
		case ASSOCIATION_SUB_RATE:
			return "SubRate";
		default:
			return "Unknown";
	}
}

std::string Modifier::print() {
	std::stringstream s;
	s << "{\"association\":\"" << getAssociationName()
	<< "\", \"attributeID\":\"" << attributeID_
	<< "\", \"modifier\":" << *modifier_.lock() << "}";
	return s.str();
}


std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Modifier& modifier)
{
	os << modifier.print();
	return os;
}

