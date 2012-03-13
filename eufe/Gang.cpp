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


using namespace eufe;

class GangModifierMatchFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	GangModifierMatchFunction(TypeID attributeID, Character* fleetBooster, Character* wingBooster, Character* squadBooster) : attributeID_(attributeID), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		Character *character = modifier->getCharacter();
		bool isBooster = character == fleetBooster_ || character == squadBooster_ || character == wingBooster_ ;
		return !(modifier->getAttributeID() == attributeID_ && isBooster);
	}
private:
	TypeID attributeID_;
	Character* fleetBooster_;
	Character* wingBooster_;
	Character* squadBooster_;
};

class GangLocationGroupModifierMatchFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	GangLocationGroupModifierMatchFunction(TypeID attributeID, TypeID groupID, Character* fleetBooster, Character* wingBooster, Character* squadBooster) : attributeID_(attributeID), groupID_(groupID), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		Character *character = modifier->getCharacter();
		bool isBooster = character == fleetBooster_ || character == squadBooster_ || character == wingBooster_ ;
		return !(modifier->getAttributeID() == attributeID_ && boost::dynamic_pointer_cast<LocationGroupModifier>(modifier)->getGroupID() == groupID_ && isBooster);
	}
private:
	TypeID attributeID_;
	TypeID groupID_;
	Character* fleetBooster_;
	Character* wingBooster_;
	Character* squadBooster_;
};

class GangLocationRequiredSkillModifierMatchFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	GangLocationRequiredSkillModifierMatchFunction(TypeID attributeID, Item* item, Character* fleetBooster, Character* wingBooster, Character* squadBooster) : attributeID_(attributeID), item_(item), fleetBooster_(fleetBooster), wingBooster_(wingBooster), squadBooster_(squadBooster) {}
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		Character *character = modifier->getCharacter();
		bool isBooster = character == fleetBooster_ || character == squadBooster_ || character == wingBooster_ ;
		return !(modifier->getAttributeID() == attributeID_ && item_->requireSkill(boost::dynamic_pointer_cast<LocationRequiredSkillModifier>(modifier)->getSkillID())  && isBooster);
	}
private:
	TypeID attributeID_;
	Item* item_;
	Character* fleetBooster_;
	Character* wingBooster_;
	Character* squadBooster_;
};

class ModifiersFindFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	ModifiersFindFunction(const boost::shared_ptr<Modifier>& modifier) : attributeID_(modifier->getAttributeID()), modifier_(modifier->getModifier()), association_(modifier->getAssociation())	{};
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		return modifier->getAttributeID() == attributeID_ && modifier->getAssociation() == association_ && modifier->getModifier() == modifier_;
	}
private:
	TypeID attributeID_;
	Attribute* modifier_;
	Modifier::Association association_;
};

class ModifiersCompareFunction : public std::binary_function<const boost::shared_ptr<Modifier>&, const boost::shared_ptr<Modifier>&, bool>
{
public:
	ModifiersCompareFunction(bool highIsGood) : highIsGood_(highIsGood) {}
	bool operator() (const boost::shared_ptr<Modifier>& arg1, const boost::shared_ptr<Modifier>& arg2)
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

Gang::Gang(Engine* engine) : Item(engine, 0, NULL)
{
}

Gang::~Gang(void)
{
	CharactersList tmp = pilots_;
	pilots_.clear();
}

const CharactersList& Gang::getPilots()
{
	return pilots_;
}

boost::shared_ptr<Character> Gang::addPilot()
{
	boost::shared_ptr<Character> character(new Character(engine_, this));
	return addPilot(character);
}

boost::shared_ptr<Character> Gang::addPilot(const boost::shared_ptr<Character>& character)
{
	character->removeEffects(Effect::CATEGORY_GENERIC);
	pilots_.push_back(character);
	character->setOwner(this);
	character->addEffects(Effect::CATEGORY_GENERIC);
	engine_->reset(this);
	return character;
}

void Gang::removePilot(const boost::shared_ptr<Character>& character)
{
	character->removeEffects(Effect::CATEGORY_GENERIC);
	pilots_.remove(character);
	engine_->reset(this);
}


boost::shared_ptr<Environment> Gang::getEnvironment()
{
	boost::shared_ptr<Environment> environment(new Environment());
	(*environment)["Self"] = this;
	(*environment)["Gang"] = this;
	
	if (engine_->getArea() != NULL)
		(*environment)["Area"] = engine_->getArea().get();
	return environment;
}

void Gang::reset()
{
	Item::reset();
	
	CharactersList::iterator i, end = pilots_.end();
	for (i = pilots_.begin(); i != end; i++)
		(*i)->reset();
}

boost::shared_ptr<Character> Gang::getFleetBooster()
{
	return fleetBooster_;
}

boost::shared_ptr<Character> Gang::getWingBooster()
{
	return wingBooster_;
}

boost::shared_ptr<Character> Gang::getSquadBooster()
{
	return squadBooster_;
}

void Gang::setFleetBooster(const boost::shared_ptr<Character>& fleetBooster)
{
	fleetBooster_ = fleetBooster;
	engine_->reset(this);
}

void Gang::setWingBooster(const boost::shared_ptr<Character>& wingBooster)
{
	wingBooster_ = wingBooster;
	engine_->reset(this);
}

void Gang::setSquadBooster(const boost::shared_ptr<Character>& squadBooster)
{
	squadBooster_ = squadBooster;
	engine_->reset(this);
}

void Gang::removeFleetBooster() {
	fleetBooster_.reset();
	engine_->reset(this);
}

void Gang::removeWingBooster() {
	wingBooster_.reset();
	engine_->reset(this);
	
}

void Gang::removeSquadBooster() {
	squadBooster_.reset();
	engine_->reset(this);
	
}

std::insert_iterator<ModifiersList> Gang::getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	Item::scoped_lock lock(*this);
	ModifiersList list;
	std::remove_copy_if(locationModifiers_.begin(),
						locationModifiers_.end(),
						std::inserter(list, list.end()),
						GangModifierMatchFunction(attribute->getAttributeID(), fleetBooster_.get(), wingBooster_.get(), squadBooster_.get()));
	ModifiersList::iterator i = std::max_element(list.begin(), list.end(), ModifiersCompareFunction(attribute->highIsGood()));
	if (i != list.end())
		*outIterator++ = *i;
	return outIterator;
}

std::insert_iterator<ModifiersList> Gang::getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	Item::scoped_lock lock(*this);
	ModifiersList list1;
	std::remove_copy_if(locationGroupModifiers_.begin(),
						locationGroupModifiers_.end(),
						std::inserter(list1, list1.end()),
						GangLocationGroupModifierMatchFunction(attribute->getAttributeID(), item->getGroupID(), fleetBooster_.get(), wingBooster_.get(), squadBooster_.get()));
	ModifiersList::iterator i = std::max_element(list1.begin(), list1.end(), ModifiersCompareFunction(attribute->highIsGood()));
	if (i != list1.end())
		*outIterator++ = *i;

	ModifiersList list2;
	std::remove_copy_if(locationRequiredSkillModifiers_.begin(),
						locationRequiredSkillModifiers_.end(),
						std::inserter(list2, list2.end()),
						GangLocationRequiredSkillModifierMatchFunction(attribute->getAttributeID(), item, fleetBooster_.get(), wingBooster_.get(), squadBooster_.get()));
	ModifiersList::iterator j = std::max_element(list2.begin(), list2.end(), ModifiersCompareFunction(attribute->highIsGood()));
	if (j != list2.end())
		*outIterator++ = *j;

	
/*	outIterator = std::remove_copy_if(locationGroupModifiers_.begin(),
									  locationGroupModifiers_.end(),
									  outIterator,
									  GangLocationGroupModifierMatchFunction(attribute->getAttributeID(), item->getGroupID(), fleetBooster_.get(), wingBooster_.get(), squadBooster_.get()));
	outIterator = std::remove_copy_if(locationRequiredSkillModifiers_.begin(),
									  locationRequiredSkillModifiers_.end(),
									  outIterator,
									  GangLocationRequiredSkillModifierMatchFunction(attribute->getAttributeID(), item, fleetBooster_.get(), wingBooster_.get(), squadBooster_.get()));*/
	return outIterator;
}


#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Gang& gang)
{
	os << "{\"typeName\":\"Gang\",\"pilots\":[";
	
	if (gang.pilots_.size() > 0)
	{
		CharactersList::const_iterator i, end = gang.pilots_.end();
		bool isFirst = true;
		for (i = gang.pilots_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"itemModifiers\":[";
	
	if (gang.itemModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = gang.itemModifiers_.end();
		bool isFirst = true;
		for (i = gang.itemModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}

	os << "], \"locationModifiers\":[";
	
	if (gang.locationModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = gang.locationModifiers_.end();
		bool isFirst = true;
		for (i = gang.locationModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (gang.locationGroupModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = gang.locationGroupModifiers_.end();
		bool isFirst = true;
		for (i = gang.locationGroupModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>((*i).get());
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (gang.locationRequiredSkillModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = gang.locationRequiredSkillModifiers_.end();
		bool isFirst = true;
		for (i = gang.locationRequiredSkillModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>((*i).get());
		}
	}
	
	os << "]}";
	return os;
}

#endif