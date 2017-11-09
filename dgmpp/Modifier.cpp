#include "Modifier.h"
#include "Attribute.h"
#include "Item.h"
#include "Module.h"
#include <sstream>
#include "Type.hpp"

using namespace dgmpp;

Modifier::Modifier(Domain domain, AttributeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, bool isAssistance, bool isOffensive, Character* character) : domain_(domain), attributeID_(attributeID), association_(association), modifier_(modifier), isAssistance_(isAssistance), isOffensive_(isOffensive), character_(character)
{
}

Modifier::~Modifier()
{
}

bool Modifier::isMatch(Item* item) const
{
	return true;
}

Modifier::Domain Modifier::getDomain() {
	return domain_;
}

AttributeID Modifier::getAttributeID() const
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
	if (association_ == Association::postDiv)
		return static_cast<Float>(1.0 / value);
	else if (association_ == Association::postPercent)
		return static_cast<Float>(1.0 + value / 100.0);
	else if (association_ == Association::addRate || association_ == Association::subRate)
	{
		std::shared_ptr<Item> item = modifier->getOwner();
		if (!item)
			return 0;
		Float duration;
		
		if (item->hasAttribute(AttributeID::duration))
			duration = static_cast<Float>(item->getAttribute(AttributeID::duration)->getValue() / 1000.0);
		else if (item->hasAttribute(AttributeID::speed))
			duration = static_cast<Float>(item->getAttribute(AttributeID::speed)->getValue() / 1000.0);
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
		case Association::preAssignment:
			return "PreAssignment";
		case Association::modAdd:
			return "ModAdd";
		case Association::modSub:
			return "ModSub";
		case Association::preDiv:
			return "PreDiv";
		case Association::preMul:
			return "PreMul";
		case Association::postPercent:
			return "PostPercent";
		case Association::postDiv:
			return "PostDiv";
		case Association::postMul:
			return "PostMul";
		case Association::postAssignment:
			return "PostAssignment";
		case Association::skillTime:
			return "SkillTime";
		case Association::addRate:
			return "AddRate";
		case Association::subRate:
			return "SubRate";
		default:
			return "Unknown";
	}
}

std::string Modifier::print() {
	std::stringstream s;
	s << "{\"association\":\"" << getAssociationName()
	<< "\", \"attributeID\":\"" << static_cast<int>(attributeID_)
	<< "\", \"modifier\":" << *modifier_.lock() << "}";
	return s.str();
}


std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Modifier& modifier)
{
	os << modifier.print();
	return os;
}


namespace dgmpp2 {
	
	Modifier::Modifier(const MetaInfo& metaInfo, Type& owner, const Effect& effect)
	: metaInfo_(metaInfo), owner_(owner), effect_(effect), modifyingAttribute_(*owner[metaInfo.modifyingAttributeID]) {
		switch (owner.metaInfo().categoryID) {
			case CategoryID::module:
			case CategoryID::drone:
			case CategoryID::charge:
			case CategoryID::fighter:
			case CategoryID::starbase:
				needsStackingCheck_ = true;
				break;
			default:
				needsStackingCheck_ = false;
		}
	}
	
	Type* Modifier::domain() const {
		return owner().domain(metaInfo().domain);
	}
	
	bool Modifier::match(const Type* type) const {
		switch (metaInfo_.type) {
			case MetaInfo::ModifierType::item:
			case MetaInfo::ModifierType::location:
				return true;
			case MetaInfo::ModifierType::locationGroup:
				return type->metaInfo().groupID == metaInfo_.require.groupID;
			case MetaInfo::ModifierType::locationRequiredSkill:
			case MetaInfo::ModifierType::ownerRequiredSkill:
				return type->metaInfo().requireSkill(metaInfo_.require.typeID);
			case MetaInfo::ModifierType::locationRequiredDomainSkill:
				if (auto type = owner_.domain(metaInfo_.domain))
					return type->metaInfo().requireSkill(type->metaInfo().typeID);
				else
					return false;
			default:
				assert(!"Invalid Modifier::MetaInfo::ModifierType value");
		}
	}
	
	Float Modifier::get() const {
		switch (metaInfo_.association) {
			using namespace std::chrono_literals;
				
			case MetaInfo::Association::postDiv:
				return 1.0 / modifyingAttribute_.value();
			case MetaInfo::Association::postPercent:
				return 1.0 + modifyingAttribute_.value() / 100.0;
			case MetaInfo::Association::addRate:
			case MetaInfo::Association::subRate:
				std::chrono::duration<Float> duration;
				if (auto attr = owner_[AttributeID::duration])
					duration = std::chrono::duration<Float, std::milli>(attr->value());
				else if (auto attr = owner_[AttributeID::speed]) {
					duration = std::chrono::duration<Float, std::milli>(attr->value());
				}
				else {
					duration = 1s;
				}
				return duration > 0.0s ? modifyingAttribute_.value() / duration.count() : 0.0;
			default:
				return modifyingAttribute_.value();
		}
		return 0;
	}
}

