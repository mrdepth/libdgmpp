#include "Character.h"
#include "Ship.h"
#include "Gang.h"
#include "Engine.h"
#include "Area.h"
#include "Skill.h"
#include "Attribute.h"
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include "Implant.h"
#include "Booster.h"

using namespace eufe;

static const TypeID CHARACTER_TYPE_ID = 1381;

Character::Character(Engine* engine, Gang* owner, const char* characterName) : Item(engine, CHARACTER_TYPE_ID, owner), characterName_(characterName), ship_(NULL)
{
	Engine::ScopedLock lock(*engine_);

	boost::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec("SELECT typeID FROM invTypes, invGroups WHERE invTypes.groupID = invGroups.groupID AND invGroups.categoryID = 16 AND invTypes.published = 1");
	while (result->next())
	{
		TypeID skillID = result->getInt(0);
		addSkill(skillID, 0, false);
	}
	engine_->reset(this);
}

Character::~Character(void)
{
	delete ship_;
	ship_ = NULL;
	
	{
		SkillsMap::iterator i, end = skills_.end();
		for (i = skills_.begin(); i != end; i++)
			delete i->second;
		skills_.clear();
	}
	
	{
		ImplantsList::iterator i, end = implants_.end();
		for (i = implants_.begin(); i != end; i++)
			delete *i;
		implants_.clear();
	}

	{
		BoostersList::iterator i, end = boosters_.end();
		for (i = boosters_.begin(); i != end; i++)
			delete *i;
		boosters_.clear();
	}
}

Ship* Character::getShip()
{
	return ship_;
}

Ship* Character::setShip(Ship* ship)
{
	removeEffects(Effect::CATEGORY_GENERIC);
	if (ship_)
		delete ship_;
	
	ship_ = ship;
	ship_->setOwner(this);

	if (ship_)
		addEffects(Effect::CATEGORY_GENERIC);
	engine_->reset(this);
	return ship;
}

Ship* Character::setShip(TypeID typeID)
{
	try
	{
		return setShip(new Ship(engine_, typeID, this));
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

Environment Character::getEnvironment()
{
	Environment environment;
	environment["Self"] = this;
	environment["Char"] = this;
	Item* gang = getOwner();

	if (ship_)
		environment["Ship"] = ship_;

	if (gang)
		environment["Gang"] = gang;
	
	if (engine_->getArea())
		environment["Area"] = engine_->getArea();
	return environment;
}

void Character::reset()
{
	Item::reset();
	if (ship_ != NULL)
		ship_->reset();
	
	{
		SkillsMap::iterator i, end = skills_.end();
		for (i = skills_.begin(); i != end; i++)
			i->second->reset();
	}
	
	{
		ImplantsList::iterator i, end = implants_.end();
		for (i = implants_.begin(); i != end; i++)
			(*i)->reset();
	}
	
	{
		BoostersList::iterator i, end = boosters_.end();
		for (i = boosters_.begin(); i != end; i++)
			(*i)->reset();
	}
}

Skill* Character::addSkill(TypeID typeID, int skillLevel, bool isLearned)
{
	try
	{
		Skill* skill = new Skill(engine_, typeID, skillLevel, isLearned, this);
		skills_[typeID] = skill;
//	if (getOwner() && ship_ != NULL)
		skill->addEffects(Effect::CATEGORY_GENERIC);
		return skill;
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

void Character::removeSkill(Skill* skill)
{
//	if (getOwner() && ship_ != NULL)
		skill->removeEffects(Effect::CATEGORY_GENERIC);
	skills_.erase(skill->getTypeID());
	delete skill;
}

Skill* Character::getSkill(TypeID typeID)
{
	return skills_[typeID];
}

bool Character::emptyImplantSlot(int slot)
{
	return !getImplant(slot);
}

bool Character::emptyBoosterSlot(int slot)
{
	return !getBooster(slot);
}

Implant* Character::getImplant(int slot)
{
	ImplantsList::iterator i, end = implants_.end();
	for (i = implants_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			return *i;
	return NULL;
}

Booster* Character::getBooster(int slot)
{
	BoostersList::iterator i, end = boosters_.end();
	for (i = boosters_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			return *i;
	return NULL;
}

Implant* Character::addImplant(TypeID typeID)
{
	try
	{
		return addImplant(new Implant(engine_, typeID, this));
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

Implant* Character::addImplant(Implant* implant)
{
	Implant* currentImplant = getImplant(implant->getSlot());
	if (currentImplant)
		removeImplant(currentImplant);
	implants_.push_back(implant);
	implant->setOwner(this);
//	if (getOwner() && ship_ != NULL)
		implant->addEffects(Effect::CATEGORY_GENERIC);
	engine_->reset(this);
	return implant;
}

Booster* Character::addBooster(TypeID typeID)
{
	try
	{
		return addBooster(new Booster(engine_, typeID, this));
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

Booster* Character::addBooster(Booster* booster)
{
	Booster* currentBooster = getBooster(booster->getSlot());
	if (currentBooster)
		removeBooster(currentBooster);
	boosters_.push_back(booster);
	booster->setOwner(this);
//	if (getOwner() && ship_ != NULL)
		booster->addEffects(Effect::CATEGORY_GENERIC);
	engine_->reset(this);
	return booster;
}

void Character::removeImplant(Implant* implant)
{
	//if (getOwner() && ship_ != NULL)
	if (implant != NULL)
	{
		implant->removeEffects(Effect::CATEGORY_GENERIC);
		implants_.remove(implant);
		delete implant;
		engine_->reset(this);
	}
}

void Character::removeBooster(Booster* booster)
{
	if (booster != NULL/* && getOwner() && ship_ != NULL*/)
	{
		booster->removeEffects(Effect::CATEGORY_GENERIC);
		boosters_.remove(booster);
		delete booster;
		engine_->reset(this);
	}
}

const ImplantsList& Character::getImplants()
{
	return implants_;
}

const BoostersList& Character::getBoosters()
{
	return boosters_;
}

void Character::addEffects(Effect::Category category)
{
//	if (ship_ != NULL)
	{
		Item::addEffects(category);
		if (category == Effect::CATEGORY_GENERIC)
		{
			if (ship_)
				ship_->addEffects(Effect::CATEGORY_GENERIC);

			{
				SkillsMap::iterator i, end = skills_.end();
				for (i = skills_.begin(); i != end; i++)
					i->second->addEffects(Effect::CATEGORY_GENERIC);
			}
			
			{
				ImplantsList::iterator i, end = implants_.end();
				for (i = implants_.begin(); i != end; i++)
					(*i)->addEffects(Effect::CATEGORY_GENERIC);
			}
			
			{
				BoostersList::iterator i, end = boosters_.end();
				for (i = boosters_.begin(); i != end; i++)
					(*i)->addEffects(Effect::CATEGORY_GENERIC);
			}
		}
	}
}

void Character::removeEffects(Effect::Category category)
{
//	if (ship_ != NULL)
	{
		Item::removeEffects(category);
		if (category == Effect::CATEGORY_GENERIC)
		{
			if (ship_)
				ship_->removeEffects(Effect::CATEGORY_GENERIC);

			{
				SkillsMap::iterator i, end = skills_.end();
				for (i = skills_.begin(); i != end; i++)
					i->second->removeEffects(Effect::CATEGORY_GENERIC);
			}
			
			{
				ImplantsList::iterator i, end = implants_.end();
				for (i = implants_.begin(); i != end; i++)
					(*i)->removeEffects(Effect::CATEGORY_GENERIC);
			}
			
			{
				BoostersList::iterator i, end = boosters_.end();
				for (i = boosters_.begin(); i != end; i++)
					(*i)->removeEffects(Effect::CATEGORY_GENERIC);
			}
		}
	}
}

void Character::setCharacterName(const char* characterName)
{
	characterName_ = characterName;
}

const char*  Character::getCharacterName()
{
	return characterName_.c_str();
}

void Character::setSkillLevels(const std::map<TypeID, int>& levels)
{
	std::map<TypeID, int>::const_iterator j, endj = levels.end();
	
	SkillsMap::iterator i, end = skills_.end();
	for (i = skills_.begin(); i != end; i++) {
		j = levels.find(i->first);
		if (j != endj)
			i->second->setSkillLevel(j->second);
		else
			i->second->setSkillLevel(0);
	}
	engine_->reset(this);
}

void Character::setAllSkillsLevel(int level)
{
	SkillsMap::iterator i, end = skills_.end();
	for (i = skills_.begin(); i != end; i++)
		i->second->setSkillLevel(level);
	engine_->reset(this);
}

std::insert_iterator<ModifiersList> Character::getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	outIterator = Item::getLocationModifiers(attribute, outIterator);
	if (owner_)
		outIterator = owner_->getLocationModifiers(attribute, outIterator);
	return outIterator;
}

Character::Character(Decoder& decoder, Engine* engine, Gang* owner) : Item(decoder, engine, owner), ship_(NULL)
{
	SkillsMap::size_type size;
	decoder.decode(size);
	for (SkillsMap::size_type i = 0; i < size; i++)
	{
		Skill* skill = new Skill(decoder, engine, this);
		skills_[skill->getTypeID()] = skill;
	}
}

void Character::encode(Encoder& encoder) const
{
	Item::encode(encoder);
	SkillsMap::const_iterator i, end = skills_.end();
	encoder.encode(skills_.size());
	for (i = skills_.begin(); i != end; i++)
		i->second->encode(encoder);
}

#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Character& character)
{
	os << "{\"typeName\":\"Character\",\"ship\":" << *character.ship_ << ", \"attributes\":[";
	
	if (character.attributes_.size() > 0)
	{
		bool isFirst = true;
		AttributesMap::iterator i, end = character.attributes_.end();
		for (i = character.attributes_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i->second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (character.effects_.size() > 0)
	{
		bool isFirst = true;
		EffectsList::iterator i, end = character.effects_.end();
		for (i = character.effects_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}

	
	os << "], \"itemModifiers\":[";

	
	if (character.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		ModifiersList::iterator i, end = character.itemModifiers_.end();
		for (i = character.itemModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (character.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		ModifiersList::iterator i, end = character.locationModifiers_.end();
		for (i = character.locationModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (character.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		ModifiersList::iterator i, end = character.locationGroupModifiers_.end();
		for (i = character.locationGroupModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>(*i);
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (character.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		ModifiersList::iterator i, end = character.locationRequiredSkillModifiers_.end();
		for (i = character.locationRequiredSkillModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>(*i);
		}
	}

	
/*	os << "],\"skills\":[";
	
	if (character.skills_.size() > 0)
	{
		SkillsMap::const_iterator i, end = character.skills_.end();
		bool isFirst = true;
		for (i = character.skills_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *(i->second);
		}
	}*/

	os << "]}";
	return os;
}

#endif