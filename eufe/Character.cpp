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

Character::Character(Engine* engine, Gang* owner, const char* characterName) : Item(engine, CHARACTER_TYPE_ID, owner), characterName_(characterName), ship_(nullptr)
{
	Engine::scoped_lock lock(*engine);

	sqlite3* db = engine->getDb();
	
	sqlite3_stmt* stmt = nullptr;
	sqlite3_prepare_v2(db, "SELECT typeID FROM invTypes, invGroups WHERE invTypes.groupID = invGroups.groupID AND invGroups.categoryID = 16 AND invTypes.published = 1", -1, &stmt, nullptr);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		TypeID skillID = sqlite3_column_int(stmt, 0);
		addSkill(skillID, 0, false);
	}
	sqlite3_finalize(stmt);
	engine_->reset(this);
}

Character::~Character(void)
{
	delete ship_;
	ship_ = nullptr;
	
	for (auto i: skills_)
		delete i.second;
	skills_.clear();
	
	for (auto i: implants_)
		delete i;
	implants_.clear();

	for (auto i: boosters_)
		delete i;
	boosters_.clear();
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
	return setShip(new Ship(engine_, typeID, this));
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
	if (ship_ != nullptr)
		ship_->reset();
	
	for (auto i: skills_)
		i.second->reset();

	for (auto i: implants_)
		i->reset();
	
	for (auto i: boosters_)
		i->reset();
}

Skill* Character::addSkill(TypeID typeID, int skillLevel, bool isLearned)
{
	Skill* skill = new Skill(engine_, typeID, skillLevel, isLearned, this);
	skills_[typeID] = skill;
//	if (getOwner() && ship_ != NULL)
		skill->addEffects(Effect::CATEGORY_GENERIC);
	return skill;
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
	for (auto i: implants_)
		if (i->getSlot() == slot)
			return i;
	return nullptr;
}

Booster* Character::getBooster(int slot)
{
	for (auto i: boosters_)
		if (i->getSlot() == slot)
			return i;
	return nullptr;
}

Implant* Character::addImplant(TypeID typeID)
{
	return addImplant(new Implant(engine_, typeID, this));
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
	return addBooster(new Booster(engine_, typeID, this));
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
	if (implant != nullptr)
	{
		implant->removeEffects(Effect::CATEGORY_GENERIC);
		implants_.remove(implant);
		delete implant;
		engine_->reset(this);
	}
}

void Character::removeBooster(Booster* booster)
{
	if (booster != nullptr/* && getOwner() && ship_ != NULL*/)
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
			for (auto i: skills_)
				i.second->addEffects(Effect::CATEGORY_GENERIC);
			
			for (auto i: implants_)
				i->addEffects(Effect::CATEGORY_GENERIC);
			
			for (auto i: boosters_)
				i->addEffects(Effect::CATEGORY_GENERIC);
			
			if (ship_)
				ship_->addEffects(Effect::CATEGORY_GENERIC);
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
			for (auto i: skills_)
				i.second->removeEffects(Effect::CATEGORY_GENERIC);
			
			for (auto i: implants_)
				i->removeEffects(Effect::CATEGORY_GENERIC);
			
			for (auto i: boosters_)
				i->removeEffects(Effect::CATEGORY_GENERIC);
			
			if (ship_)
				ship_->removeEffects(Effect::CATEGORY_GENERIC);
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
	
	for (auto i: skills_) {
		j = levels.find(i.first);
		if (j != endj)
			i.second->setSkillLevel(j->second);
		else
			i.second->setSkillLevel(0);
	}
	engine_->reset(this);
}

void Character::setAllSkillsLevel(int level)
{
	for (auto i: skills_)
		i.second->setSkillLevel(level);
	engine_->reset(this);
}

std::insert_iterator<ModifiersList> Character::getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	outIterator = Item::getLocationModifiers(attribute, outIterator);
	if (owner_)
		outIterator = owner_->getLocationModifiers(attribute, outIterator);
	return outIterator;
}


#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Character& character)
{
	os << "{\"typeName\":\"Character\",\"ship\":" << *character.ship_ << ", \"attributes\":[";
	
	if (character.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: character.attributes_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i.second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (character.effects_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: character.effects_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}

	
	os << "], \"itemModifiers\":[";

	
	if (character.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: character.itemModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (character.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: character.locationModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (character.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: character.locationGroupModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>(i);
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (character.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: character.locationRequiredSkillModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>(i);
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