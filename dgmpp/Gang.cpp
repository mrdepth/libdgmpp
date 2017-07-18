#include "Gang.h"
#include "Ship.h"
#include "Character.h"
#include "Engine.h"
#include "Area.h"
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include "Attribute.h"
#include <functional>
#include <cmath>
#include <algorithm>

using namespace dgmpp;

namespace std {
	template<> struct hash<Modifier> {
	public:
		uint64_t operator()(const Modifier& modifier) const {
			uint64_t h = static_cast<size_t>(modifier.getAttributeID());
			h <<= 16;
			h |= static_cast<size_t>(modifier.getModifier()->getAttributeID());
			h <<= 4;
			h |= static_cast<size_t>(modifier.getAssociation());
			return h;
		}
	};
}



class GangModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	GangModifierMatchFunction(TypeID attributeID, Character* fleetBooster, Character* wingBooster, Character* squadBooster) : attributeID_(attributeID), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		Character* character = modifier->getCharacter();
		bool isBooster = character == fleetBooster_ || character == squadBooster_ || character == wingBooster_ ;
		return (modifier->getAttributeID() == attributeID_ && isBooster);
	}
private:
	TypeID attributeID_;
	Character* fleetBooster_;
	Character* wingBooster_;
	Character* squadBooster_;
};

/*class GangLocationGroupModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	GangLocationGroupModifierMatchFunction(TypeID attributeID, TypeID groupID, std::shared_ptr<Character> const& fleetBooster, std::shared_ptr<Character> const& wingBooster, std::shared_ptr<Character> const& squadBooster) : attributeID_(attributeID), groupID_(groupID), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		std::shared_ptr<Character> character = modifier->getCharacter();
		bool isBooster = character == fleetBooster_ || character == squadBooster_ || character == wingBooster_ ;
		return !(modifier->getAttributeID() == attributeID_ && std::dynamic_pointer_cast<LocationGroupModifier>(modifier)->getGroupID() == groupID_ && isBooster);
	}
private:
	TypeID attributeID_;
	TypeID groupID_;
	std::shared_ptr<Character> fleetBooster_;
	std::shared_ptr<Character> wingBooster_;
	std::shared_ptr<Character> squadBooster_;
};

class GangLocationRequiredSkillModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	GangLocationRequiredSkillModifierMatchFunction(TypeID attributeID, std::shared_ptr<Item> const& item, std::shared_ptr<Character> const& fleetBooster, std::shared_ptr<Character> const& wingBooster, std::shared_ptr<Character> const& squadBooster) : attributeID_(attributeID), item_(item), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		std::shared_ptr<Character> character = modifier->getCharacter();
		bool isBooster = character == fleetBooster_ || character == squadBooster_ || character == wingBooster_ ;
		return !(modifier->getAttributeID() == attributeID_ && item_->requireSkill(std::dynamic_pointer_cast<LocationRequiredSkillModifier>(modifier)->getSkillID())  && isBooster);
	}
private:
	TypeID attributeID_;
	std::shared_ptr<Item> item_;
	std::shared_ptr<Character> fleetBooster_;
	std::shared_ptr<Character> wingBooster_;
	std::shared_ptr<Character> squadBooster_;
};*/

class ModifiersFindFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	ModifiersFindFunction(std::shared_ptr<Modifier> const& modifier) : attributeID_(modifier->getAttributeID()), modifier_(modifier->getModifier()), association_(modifier->getAssociation())	{};
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		return modifier->getAttributeID() == attributeID_ && modifier->getAssociation() == association_ && modifier->getModifier() == modifier_;
	}
private:
	TypeID attributeID_;
	std::shared_ptr<Attribute> modifier_;
	Modifier::Association association_;
};

class ModifiersCompareFunction : public std::binary_function<std::shared_ptr<Modifier> const&, std::shared_ptr<Modifier> const&, bool>
{
public:
	ModifiersCompareFunction(bool highIsGood) : highIsGood_(highIsGood) {}
	bool operator() (std::shared_ptr<Modifier> const& arg1, std::shared_ptr<Modifier> const& arg2)
	{
		if (arg1->getModifier()->highIsGood())
		//if (highIsGood_)
			return fabs(arg1->getModifier()->getValue()) > fabs(arg2->getModifier()->getValue());
		else
			return fabs(arg1->getModifier()->getValue()) < fabs(arg2->getModifier()->getValue());
/*		if (highIsGood_)
			return arg1->getValue() < arg2->getValue();
		else
			return arg1->getValue() > arg2->getValue();*/
		//return fabs(arg1->getModifier()->getValue()) < fabs(arg2->getModifier()->getValue());
		//return fabs(1.0 - arg1->getValue()) < fabs(1.0 - arg2->getValue());
	}
private:
	bool highIsGood_;
};

Gang::Gang(std::shared_ptr<Engine> const& engine) : Item(engine, 0, nullptr)
{
}

Gang::~Gang(void)
{
}

const CharactersList& Gang::getPilots()
{
	return pilots_;
}

std::shared_ptr<Character> Gang::addPilot()
{
	auto engine = getEngine();
	if (!engine)
		return nullptr;

	std::shared_ptr<Character> character = std::make_shared<Character>(engine, shared_from_this());
//	character->removeEffects(Effect::CATEGORY_GENERIC);
	pilots_.push_back(character);
	character->addEffects(Effect::CATEGORY_GENERIC);
	engine->reset();
	return character;
}


void Gang::removePilot(std::shared_ptr<Character> const& character)
{
	auto engine = getEngine();
	if (!engine)
		return;
	character->removeEffects(Effect::CATEGORY_GENERIC);
	//pilots_.remove(character);
	pilots_.erase(std::find(pilots_.begin(), pilots_.end(), character));
	engine->reset();
}


void Gang::reset()
{
	Item::reset();
	
	for (const auto& i: pilots_)
		i->reset();
	boostModifiers_ = nullptr;
}

void Gang::addGangBoost(std::shared_ptr<GangBoost> boost) {
	boosts_.push_back(boost);
}

void Gang::removeGangBoost(std::shared_ptr<GangBoost> boost) {
	boosts_.erase(std::find(boosts_.begin(), boosts_.end(), boost));
}

std::insert_iterator<ModifiersList> Gang::getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	return outIterator;
}

std::insert_iterator<ModifiersList> Gang::getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	auto modifiers = getBoostModifiers();
	auto i = modifiers.find(attribute->getAttributeID());
	if (i != modifiers.end()) {
		std::copy_if(i->second.begin(), i->second.end(), outIterator, [=](std::shared_ptr<Modifier> modifier) {
			return modifier->isMatch(item);
		});
	}
	
	return outIterator;
}

const ItemModifiers& Gang::getBoostModifiers() {
	if (!boostModifiers_) {
		boostModifiers_ = std::make_shared<ItemModifiers>();
		std::map<int, std::list<std::shared_ptr<GangBoost>>> m;
		for (const auto& boost: boosts_) {
			m[static_cast<int>(boost->getBufID()->getValue())].push_back(boost);
		}
		
		for (const auto& i: m) {
			auto boost = std::max_element(i.second.begin(), i.second.end(), [&](std::shared_ptr<GangBoost> a, std::shared_ptr<GangBoost> b) {
				return std::abs(a->getValue()->getValue()) < std::abs(b->getValue()->getValue());
			});
			if (boost != i.second.end()) {
				auto modifiers = (*boost)->modifiers();
				
				for (auto modifier: modifiers) {
					(*boostModifiers_)[modifier->getAttributeID()].push_back(modifier);
				}
			}
		}
	}
	return *boostModifiers_;
}

std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Gang& gang)
{
	os << "{\"typeName\":\"Gang\",\"pilots\":[";
	
	if (gang.pilots_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: gang.pilots_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"itemModifiers\":[";
	
	if (gang.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: gang.itemModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}
	
	os << "]}";
	return os;
}
