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
#include <math.h>
#include <algorithm>


using namespace eufe;

class GangModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	GangModifierMatchFunction(TypeID attributeID, std::shared_ptr<Character> fleetBooster, std::shared_ptr<Character> wingBooster, std::shared_ptr<Character> squadBooster) : attributeID_(attributeID), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (std::shared_ptr<Modifier> modifier)
	{
		std::shared_ptr<Character> character = modifier->getCharacter();
		bool isBooster = character == fleetBooster_ || character == squadBooster_ || character == wingBooster_ ;
		return !(modifier->getAttributeID() == attributeID_ && isBooster);
	}
private:
	TypeID attributeID_;
	std::shared_ptr<Character> fleetBooster_;
	std::shared_ptr<Character> wingBooster_;
	std::shared_ptr<Character> squadBooster_;
};

class GangLocationGroupModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	GangLocationGroupModifierMatchFunction(TypeID attributeID, TypeID groupID, std::shared_ptr<Character> fleetBooster, std::shared_ptr<Character> wingBooster, std::shared_ptr<Character> squadBooster) : attributeID_(attributeID), groupID_(groupID), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (std::shared_ptr<Modifier> modifier)
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

class GangLocationRequiredSkillModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	GangLocationRequiredSkillModifierMatchFunction(TypeID attributeID, std::shared_ptr<Item> item, std::shared_ptr<Character> fleetBooster, std::shared_ptr<Character> wingBooster, std::shared_ptr<Character> squadBooster) : attributeID_(attributeID), item_(item), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (std::shared_ptr<Modifier> modifier)
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
};

class ModifiersFindFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	ModifiersFindFunction(std::shared_ptr<Modifier> modifier) : attributeID_(modifier->getAttributeID()), modifier_(modifier->getModifier()), association_(modifier->getAssociation())	{};
	bool operator() (std::shared_ptr<Modifier> modifier)
	{
		return modifier->getAttributeID() == attributeID_ && modifier->getAssociation() == association_ && modifier->getModifier() == modifier_;
	}
private:
	TypeID attributeID_;
	std::shared_ptr<Attribute> modifier_;
	Modifier::Association association_;
};

class ModifiersCompareFunction : public std::binary_function<std::shared_ptr<Modifier>, std::shared_ptr<Modifier>, bool>
{
public:
	ModifiersCompareFunction(bool highIsGood) : highIsGood_(highIsGood) {}
	bool operator() (std::shared_ptr<Modifier> arg1, std::shared_ptr<Modifier> arg2)
	{
/*		if (highIsGood_)
			return arg1->getValue() < arg2->getValue();
		else
			return arg1->getValue() > arg2->getValue();*/
		//return fabs(arg1->getModifier()->getValue()) < fabs(arg2->getModifier()->getValue());
		return fabs(1.0 - arg1->getValue()) < fabs(1.0 - arg2->getValue());
	}
private:
	bool highIsGood_;
};

Gang::Gang(std::shared_ptr<Engine> engine) : Item(engine, 0, nullptr), fleetBooster_(nullptr), wingBooster_(nullptr), squadBooster_(nullptr)
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
	engine->reset(shared_from_this());
	return character;
}


void Gang::removePilot(std::shared_ptr<Character> character)
{
	auto engine = getEngine();
	if (!engine)
		return;
	character->removeEffects(Effect::CATEGORY_GENERIC);
	pilots_.remove(character);
	engine->reset(shared_from_this());
}


Environment Gang::getEnvironment()
{
	Environment environment;
	auto engine = getEngine();
	if (engine) {
		environment["Self"] = shared_from_this();
		environment["Gang"] = shared_from_this();
		auto area = engine->getArea();
		if (area)
			environment["Area"] = area;
		
	}
	return environment;
}

void Gang::reset()
{
	Item::reset();
	
	for (auto i: pilots_)
		i->reset();
}

std::shared_ptr<Character> Gang::getFleetBooster()
{
	return fleetBooster_;
}

std::shared_ptr<Character> Gang::getWingBooster()
{
	return wingBooster_;
}

std::shared_ptr<Character> Gang::getSquadBooster()
{
	return squadBooster_;
}

void Gang::setFleetBooster(std::shared_ptr<Character> fleetBooster)
{
	fleetBooster_ = fleetBooster;
	if (wingBooster_ == fleetBooster)
		wingBooster_ = nullptr;
	if (squadBooster_ == fleetBooster)
		squadBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

void Gang::setWingBooster(std::shared_ptr<Character> wingBooster)
{
	wingBooster_ = wingBooster;
	if (fleetBooster_ == wingBooster)
		fleetBooster_ = nullptr;
	if (squadBooster_ == wingBooster)
		squadBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

void Gang::setSquadBooster(std::shared_ptr<Character> squadBooster)
{
	squadBooster_ = squadBooster;
	if (fleetBooster_ == squadBooster)
		fleetBooster_ = nullptr;
	if (wingBooster_ == squadBooster)
		wingBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

void Gang::removeFleetBooster() {
	fleetBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

void Gang::removeWingBooster() {
	wingBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
	
}

void Gang::removeSquadBooster() {
	squadBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

std::insert_iterator<ModifiersList> Gang::getLocationModifiers(std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator)
{
	ModifiersList list;
	std::remove_copy_if(locationModifiers_.begin(),
						locationModifiers_.end(),
						std::inserter(list, list.end()),
						GangModifierMatchFunction(attribute->getAttributeID(), fleetBooster_, wingBooster_, squadBooster_));
	ModifiersList::iterator i = std::max_element(list.begin(), list.end(), ModifiersCompareFunction(attribute->highIsGood()));
	if (i != list.end())
		*outIterator++ = *i;
	return outIterator;
}

std::insert_iterator<ModifiersList> Gang::getModifiersMatchingItem(std::shared_ptr<Item> item, std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator)
{
	ModifiersList list1;
	std::remove_copy_if(locationGroupModifiers_.begin(),
						locationGroupModifiers_.end(),
						std::inserter(list1, list1.end()),
						GangLocationGroupModifierMatchFunction(attribute->getAttributeID(), item->getGroupID(), fleetBooster_, wingBooster_, squadBooster_));
	ModifiersList::iterator i = std::max_element(list1.begin(), list1.end(), ModifiersCompareFunction(attribute->highIsGood()));
	if (i != list1.end())
		*outIterator++ = *i;

	ModifiersList list2;
	std::remove_copy_if(locationRequiredSkillModifiers_.begin(),
						locationRequiredSkillModifiers_.end(),
						std::inserter(list2, list2.end()),
						GangLocationRequiredSkillModifierMatchFunction(attribute->getAttributeID(), item, fleetBooster_, wingBooster_, squadBooster_));
	ModifiersList::iterator j = std::max_element(list2.begin(), list2.end(), ModifiersCompareFunction(attribute->highIsGood()));
	if (j != list2.end())
		*outIterator++ = *j;
	
	return outIterator;
}


std::ostream& eufe::operator<<(std::ostream& os, eufe::Gang& gang)
{
	os << "{\"typeName\":\"Gang\",\"pilots\":[";
	
	if (gang.pilots_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: gang.pilots_)
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
		for (auto i: gang.itemModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}

	os << "], \"locationModifiers\":[";
	
	if (gang.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: gang.locationModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (gang.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: gang.locationGroupModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationGroupModifier>(i);
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (gang.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: gang.locationRequiredSkillModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationRequiredSkillModifier>(i);
		}
	}
	
	os << "]}";
	return os;
}
