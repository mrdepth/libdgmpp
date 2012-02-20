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

Character::Character(Engine* engine, Gang* owner, const char* characterName) : Item(engine, CHARACTER_TYPE_ID, owner), characterName_(characterName)
{
	sqlite3* db = engine->getDb();
	
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db, "SELECT typeID FROM invTypes, invGroups WHERE invTypes.groupID = invGroups.groupID AND invGroups.categoryID = 16 AND invTypes.published = 1", -1, &stmt, NULL);
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
}

boost::shared_ptr<Ship> Character::getShip()
{
	return ship_;
}

boost::shared_ptr<Ship> Character::setShip(const boost::shared_ptr<Ship>& ship)
{
//	if (ship_ != NULL)
		removeEffects(Effect::CATEGORY_GENERIC);
	ship_ = ship;
	ship_->setOwner(this);

	//if (getOwner() != NULL) {
	if (ship_ != NULL)
	{
		addEffects(Effect::CATEGORY_GENERIC);
	}
	engine_->reset(this);
	return ship;
}

boost::shared_ptr<Ship> Character::setShip(TypeID typeID)
{
	return setShip(boost::shared_ptr<Ship>(new Ship(engine_, typeID, this)));
}

boost::shared_ptr<Environment> Character::getEnvironment()
{
	boost::shared_ptr<Environment> environment(new Environment());
	(*environment)["Self"] = this;
	(*environment)["Char"] = this;
	Item* gang = getOwner();

	if (ship_ != NULL)
		(*environment)["Ship"] = ship_.get();

	if (gang != NULL)
		(*environment)["Gang"] = gang;
	
	if (engine_->getArea() != NULL)
		(*environment)["Area"] = engine_->getArea().get();
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

boost::shared_ptr<Skill> Character::addSkill(TypeID typeID, int skillLevel, bool isLearned)
{
	boost::shared_ptr<Skill> skill(new Skill(engine_, typeID, skillLevel, isLearned, this));
	skills_[typeID] = skill;
//	if (getOwner() && ship_ != NULL)
		skill->addEffects(Effect::CATEGORY_GENERIC);
	return skill;
}

void Character::removeSkill(boost::shared_ptr<Skill>& skill)
{
//	if (getOwner() && ship_ != NULL)
		skill->removeEffects(Effect::CATEGORY_GENERIC);
	skills_.erase(skill->getTypeID());
}

boost::shared_ptr<Skill> Character::getSkill(TypeID typeID)
{
	return skills_[typeID];
}

bool Character::emptyImplantSlot(int slot)
{
	ImplantsList::iterator i, end = implants_.end();
	for (i = implants_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			return true;
	return false;
}

bool Character::emptyBoosterSlot(int slot)
{
	BoostersList::iterator i, end = boosters_.end();
	for (i = boosters_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			return true;
	return false;
}

boost::shared_ptr<Implant> Character::getImplant(int slot)
{
	ImplantsList::iterator i, end = implants_.end();
	for (i = implants_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			return *i;
	return boost::shared_ptr<Implant>();
}

boost::shared_ptr<Booster> Character::getBooster(int slot)
{
	BoostersList::iterator i, end = boosters_.end();
	for (i = boosters_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			return *i;
	return boost::shared_ptr<Booster>();
}

boost::shared_ptr<Implant> Character::addImplant(TypeID typeID)
{
	return addImplant(boost::shared_ptr<Implant>(new Implant(engine_, typeID, this)));
}

boost::shared_ptr<Implant> Character::addImplant(const boost::shared_ptr<Implant>& implant)
{
	boost::shared_ptr<Implant> currentImplant = getImplant(implant->getSlot());
	if (currentImplant)
		removeImplant(currentImplant);
	implants_.push_back(implant);
	implant->setOwner(this);
//	if (getOwner() && ship_ != NULL)
		implant->addEffects(Effect::CATEGORY_GENERIC);
	engine_->reset(this);
	return implant;
}

boost::shared_ptr<Booster> Character::addBooster(TypeID typeID)
{
	return addBooster(boost::shared_ptr<Booster>(new Booster(engine_, typeID, this)));
}

boost::shared_ptr<Booster> Character::addBooster(const boost::shared_ptr<Booster>& booster)
{
	boost::shared_ptr<Booster> currentBooster = getBooster(booster->getSlot());
	if (currentBooster)
		removeBooster(currentBooster);
	boosters_.push_back(booster);
	booster->setOwner(this);
//	if (getOwner() && ship_ != NULL)
		booster->addEffects(Effect::CATEGORY_GENERIC);
	engine_->reset(this);
	return booster;
}

void Character::removeImplant(const boost::shared_ptr<Implant>& implant)
{
	//if (getOwner() && ship_ != NULL)
	{
		implant->removeEffects(Effect::CATEGORY_GENERIC);
		implants_.remove(implant);
		engine_->reset(this);
	}
}

void Character::removeBooster(const boost::shared_ptr<Booster>& booster)
{
	if (booster != NULL/* && getOwner() && ship_ != NULL*/)
	{
		booster->removeEffects(Effect::CATEGORY_GENERIC);
		boosters_.remove(booster);
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
			if (ship_ != NULL)
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
			if (ship_ != NULL)
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
	SkillsMap::iterator i, end = skills_.end();
	std::map<TypeID, int>::const_iterator j, endj = levels.end();
	
	for (i = skills_.begin(); i != end; i++)
	{
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


#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Character& character)
{
	os << "{\"typeName\":\"Character\",\"ship\":" << *character.ship_ << ", \"attributes\":[";
	
	if (character.attributes_.size() > 0)
	{
		AttributesMap::const_iterator i, end = character.attributes_.end();
		bool isFirst = true;
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
		EffectsList::const_iterator i, end = character.effects_.end();
		bool isFirst = true;
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
		ModifiersList::const_iterator i, end = character.itemModifiers_.end();
		bool isFirst = true;
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
		ModifiersList::const_iterator i, end = character.locationModifiers_.end();
		bool isFirst = true;
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
		ModifiersList::const_iterator i, end = character.locationGroupModifiers_.end();
		bool isFirst = true;
		for (i = character.locationGroupModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>((*i).get());
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (character.locationRequiredSkillModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = character.locationRequiredSkillModifiers_.end();
		bool isFirst = true;
		for (i = character.locationRequiredSkillModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>((*i).get());
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