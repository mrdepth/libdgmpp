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

Gang::Gang(std::shared_ptr<Engine> const& engine) : Item(engine, 0, nullptr), fleetBooster_(nullptr), wingBooster_(nullptr), squadBooster_(nullptr)
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


Environment Gang::getEnvironment()
{
	Environment environment;
	auto engine = getEngine();
	if (engine) {
		/*environment["Self"] = shared_from_this();
		environment["Gang"] = shared_from_this();
		auto area = engine->getArea();
		if (area)
			environment["Area"] = area;*/
		environment.self = this;
		environment.gang = this;
		environment.area = engine->getArea().get();
		
	}
	return environment;
}

void Gang::reset()
{
	Item::reset();
	
	for (const auto& i: pilots_)
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

void Gang::setFleetBooster(std::shared_ptr<Character> const& fleetBooster)
{
	fleetBooster_ = fleetBooster;
	if (wingBooster_ == fleetBooster)
		wingBooster_ = nullptr;
	if (squadBooster_ == fleetBooster)
		squadBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

void Gang::setWingBooster(std::shared_ptr<Character> const& wingBooster)
{
	wingBooster_ = wingBooster;
	if (fleetBooster_ == wingBooster)
		fleetBooster_ = nullptr;
	if (squadBooster_ == wingBooster)
		squadBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

void Gang::setSquadBooster(std::shared_ptr<Character> const& squadBooster)
{
	squadBooster_ = squadBooster;
	if (fleetBooster_ == squadBooster)
		fleetBooster_ = nullptr;
	if (wingBooster_ == squadBooster)
		wingBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

void Gang::removeFleetBooster() {
	fleetBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

void Gang::removeWingBooster() {
	wingBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset();
	
}

void Gang::removeSquadBooster() {
	squadBooster_ = nullptr;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

ModifiersList Gang::getLocationModifiers(std::shared_ptr<Attribute> const& attribute)
{
	GangModifierMatchFunction match (attribute->getAttributeID(), fleetBooster_.get(), wingBooster_.get(), squadBooster_.get());
	ModifiersCompareFunction cmp (attribute->highIsGood());
	
	std::shared_ptr<Modifier> max = nullptr;

	auto i = locationModifiers_.find(attribute->getAttributeID());
	if (i != locationModifiers_.end()) {
		for (const auto& modifier: i->second) {
			if (match(modifier)) {
				if (!max || cmp(modifier, max))
					max = modifier;
			}
		}
	}

	ModifiersList result;
	if (max)
		result.push_back(max);
	return result;
}

ModifiersList Gang::getModifiersMatchingItem(std::shared_ptr<Item> const& item, std::shared_ptr<Attribute> const& attribute)
{
	GangModifierMatchFunction match (attribute->getAttributeID(), fleetBooster_.get(), wingBooster_.get(), squadBooster_.get());
	ModifiersCompareFunction cmp (attribute->highIsGood());
	ModifiersList result;

	{
		std::shared_ptr<Modifier> max = nullptr;

		auto i = locationGroupModifiers_.find(attribute->getAttributeID());
		if (i != locationGroupModifiers_.end()) {
			auto j = i->second.find(item->getGroupID());
			if (j != i->second.end()) {
				for (const auto& modifier: j->second) {
					if (match(modifier)) {
						if (!max || cmp(modifier, max))
							max = modifier;
					}
				}
				
			}
		}
		
		if (max)
			result.push_back(max);
	}

	{
		std::shared_ptr<Modifier> max = nullptr;

		auto i = locationRequiredSkillModifiers_.find(attribute->getAttributeID());
		if (i != locationRequiredSkillModifiers_.end()) {
			for (const auto& map: i->second) {
				if (item->requireSkill(map.first)) {
					const auto& list = map.second;
					for (const auto& modifier: list) {
						if (match(modifier)) {
							if (!max || cmp(modifier, max))
								max = modifier;
						}
					}
				}
			}
			
		}
		
		if (max)
			result.push_back(max);
	}
	
	return result;
}


std::ostream& eufe::operator<<(std::ostream& os, eufe::Gang& gang)
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
	
	os << "], \"locationModifiers\":[";
	
	if (gang.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: gang.locationModifiers_) {
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
	
	os << "], \"locationGroupModifiers\":[";
	
	if (gang.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: gang.locationGroupModifiers_) {
			for (const auto& list: map.second) {
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
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (gang.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: gang.locationRequiredSkillModifiers_) {
			for (const auto& list: map.second) {
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
	}
	
	os << "]}";
	return os;
}
