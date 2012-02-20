#include "Modifier.h"
#include "Attribute.h"
#include "Item.h"
#include "Module.h"

using namespace eufe;

Modifier::Modifier(TypeID attributeID, Association association, Attribute* modifier, bool isAssistance, bool isOffensive, Character* character) : attributeID_(attributeID), association_(association), modifier_(modifier), isAssistance_(isAssistance), isOffensive_(isOffensive), character_(character)
{
	
}

Modifier::~Modifier()
{
}

float Modifier::getValue() const
{
	float value = modifier_->getValue();
	if (association_ == ASSOCIATION_POST_DIV)
		return static_cast<float>(1.0 / value);
	else if (association_ == ASSOCIATION_POST_PERCENT)
		return static_cast<float>(1.0 + value / 100.0);
	else if (association_ == ASSOCIATION_ADD_RATE || association_ == ASSOCIATION_SUB_RATE)
	{
		Item* item = modifier_->getOwner();
		float duration;
		if (item->hasAttribute(DURATION_ATTRIBUTE_ID))
			duration = static_cast<float>(item->getAttribute(DURATION_ATTRIBUTE_ID)->getValue() / 1000.0);
		else if (item->hasAttribute(SPEED_ATTRIBUTE_ID))
			duration = static_cast<float>(item->getAttribute(SPEED_ATTRIBUTE_ID)->getValue() / 1000.0);
		else
			duration = 1;
		return duration > 0.0 ? static_cast<float>(value / duration) : 0.0;
	}
	else
		return value;
}

bool Modifier::isStackable() const
{
	return modifier_->isStackable();
}

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

#if _DEBUG

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

std::ostream& eufe::operator<<(std::ostream& os, eufe::Modifier& modifier)
{
	os	<< "{\"association\":\"" << modifier.getAssociationName()
	<< "\", \"attributeID\":\"" << modifier.attributeID_
	<< "\", \"modifier\":" << *modifier.modifier_ << "}";
	return os;
}

#endif