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

Character::Character(std::shared_ptr<Engine> const& engine, std::shared_ptr<Gang> const& owner, const char* characterName) : Item(engine, CHARACTER_TYPE_ID, owner), characterName_(characterName), ship_(nullptr)
{
}

Character::~Character(void)
{
}

std::shared_ptr<Ship> Character::getShip()
{
	return ship_;
}

std::shared_ptr<Ship> Character::setShip(TypeID typeID)
{
	try
	{
		loadIfNeeded();
		auto engine = getEngine();
		if (!engine)
			return nullptr;
		
		std::shared_ptr<Ship> ship = std::make_shared<Ship>(engine, typeID, shared_from_this());
		
		if (ship_)
			removeEffects(Effect::CATEGORY_GENERIC);
		ship_ = ship;
		
		if (ship_)
			addEffects(Effect::CATEGORY_GENERIC);
		engine->reset(shared_from_this());
		return ship;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

Environment Character::getEnvironment()
{
	Environment environment;
	auto engine = getEngine();
	if (engine) {
		environment["Self"] = shared_from_this();
		environment["Char"] = shared_from_this();
		std::shared_ptr<Item> gang = getOwner();
		std::shared_ptr<Area> area = engine->getArea();
		
		if (ship_)
			environment["Ship"] = ship_;
		
		if (gang)
			environment["Gang"] = gang;
		
		if (area)
			environment["Area"] = area;
	}
	return environment;
}

void Character::reset()
{
	Item::reset();
	if (ship_ != nullptr)
		ship_->reset();
	
	//for (const std::pair<int, const std::shared_ptr<Skill>&>& i: skills_)
	for (const auto& i: skills_)
		i.second->reset();
	for (const auto& i: implants_)
		i->reset();
	for (const auto& i: boosters_)
		i->reset();
}

std::shared_ptr<Skill> Character::addSkill(TypeID typeID, int skillLevel, bool isLearned)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Skill> skill = std::make_shared<Skill>(engine, typeID, skillLevel, isLearned, shared_from_this());
		skills_[typeID] = skill;
//	if (getOwner() && ship_ != nullptr)
		if (ship_)
			skill->addEffects(Effect::CATEGORY_GENERIC);
		return skill;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void Character::removeSkill(std::shared_ptr<Skill> const& skill)
{
//	if (getOwner() && ship_ != NULL)
	if (ship_)
		skill->removeEffects(Effect::CATEGORY_GENERIC);
	skills_.erase(skill->getTypeID());
}

std::shared_ptr<Skill> Character::getSkill(TypeID typeID)
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

std::shared_ptr<Implant> Character::getImplant(int slot)
{
	auto i = std::find_if(implants_.begin(), implants_.end(), [=](std::shared_ptr<Implant> implant) {
		return implant->getSlot() == slot;
	});
	return i != implants_.end() ? *i : nullptr;
}

std::shared_ptr<Booster> Character::getBooster(int slot)
{
	auto i = std::find_if(boosters_.begin(), boosters_.end(), [=](std::shared_ptr<Booster> booster) {
		return booster->getSlot() == slot;
	});
	return i != boosters_.end() ? *i : nullptr;
}

std::shared_ptr<Implant> Character::addImplant(TypeID typeID, bool forced)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Implant> implant = std::make_shared<Implant>(engine, typeID, shared_from_this());
		std::shared_ptr<Implant> currentImplant = getImplant(implant->getSlot());
		if (currentImplant) {
			if (forced)
				removeImplant(currentImplant);
			else
				return currentImplant;
		}
		implants_.push_back(implant);
		if (ship_)
			implant->addEffects(Effect::CATEGORY_GENERIC);
		engine->reset(shared_from_this());
		return implant;

	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

std::shared_ptr<Booster> Character::addBooster(TypeID typeID, bool forced)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Booster> booster = std::make_shared<Booster>(engine, typeID, shared_from_this());
		std::shared_ptr<Booster> currentBooster = getBooster(booster->getSlot());
		if (currentBooster) {
			if (forced)
				removeBooster(currentBooster);
			else
				return currentBooster;
		}
		boosters_.push_back(booster);
		if (ship_)
			booster->addEffects(Effect::CATEGORY_GENERIC);
		engine->reset(shared_from_this());
		return booster;
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

void Character::removeImplant(std::shared_ptr<Implant> const& implant)
{
	if (implant != NULL)
	{
		if (ship_)
			implant->removeEffects(Effect::CATEGORY_GENERIC);
		implants_.remove(implant);

		auto engine = getEngine();
		if (engine)
			engine->reset(shared_from_this());
	}
}

void Character::removeBooster(std::shared_ptr<Booster> const& booster)
{
	if (booster != NULL)
	{
		if (ship_)
			booster->removeEffects(Effect::CATEGORY_GENERIC);
		boosters_.remove(booster);
		
		auto engine = getEngine();
		if (engine)
			engine->reset(shared_from_this());
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
	if (ship_)
	{
		Item::addEffects(category);
		if (category == Effect::CATEGORY_GENERIC)
		{
			if (ship_)
				ship_->addEffects(Effect::CATEGORY_GENERIC);

			for (const auto& i: skills_)
				i.second->addEffects(Effect::CATEGORY_GENERIC);
			for (const auto& i: implants_)
				i->addEffects(Effect::CATEGORY_GENERIC);
			for (const auto& i: boosters_)
				i->addEffects(Effect::CATEGORY_GENERIC);
		}
	}
}

void Character::removeEffects(Effect::Category category)
{
	if (ship_)
	{
		Item::removeEffects(category);
		if (category == Effect::CATEGORY_GENERIC)
		{
			if (ship_)
				ship_->removeEffects(Effect::CATEGORY_GENERIC);

			for (const auto& i: skills_)
				i.second->removeEffects(Effect::CATEGORY_GENERIC);
			for (const auto& i: implants_)
				i->removeEffects(Effect::CATEGORY_GENERIC);
			for (const auto& i: boosters_)
				i->removeEffects(Effect::CATEGORY_GENERIC);
		}
	}
}

void Character::setCharacterName(const char* characterName)
{
	characterName_ = characterName ?: "";
}

const char*  Character::getCharacterName()
{
	return characterName_.c_str();
}

void Character::setSkillLevels(const std::map<TypeID, int>& levels)
{
	auto engine = getEngine();
	if (!engine)
		return;

	std::map<TypeID, int>::const_iterator j, endj = levels.end();
	
	for (const auto& i: skills_) {
		j = levels.find(i.first);
		if (j != endj)
			i.second->setSkillLevel(j->second);
		else
			i.second->setSkillLevel(0);
	}
	engine->reset(shared_from_this());
}

void Character::setAllSkillsLevel(int level)
{
	auto engine = getEngine();
	if (!engine)
		return;
	for (const auto& i: skills_)
		i.second->setSkillLevel(level);
	engine->reset(shared_from_this());
}

std::insert_iterator<ModifiersList> Character::getLocationModifiers(std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator)
{
	outIterator = Item::getLocationModifiers(attribute, outIterator);
	auto owner = getOwner();
	if (owner)
		outIterator = owner->getLocationModifiers(attribute, outIterator);
	return outIterator;
}

void Character::lazyLoad() {
	auto engine = getEngine();
	if (!engine)
		return;

	Item::lazyLoad();
	
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec("SELECT typeID FROM invTypes, invGroups WHERE invTypes.groupID = invGroups.groupID AND invGroups.categoryID = 16 AND invTypes.published = 1");
	while (result->next())
	{
		TypeID skillID = result->getInt(0);
		addSkill(skillID, 0, false);
	}
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::Character& character)
{
	os << "{\"typeName\":\"Character\",\"ship\":" << *character.ship_ << ", \"attributes\":[";
	
	if (character.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: character.attributes_)
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
		for (const auto& i: character.effects_)
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
		for (const auto& i: character.itemModifiers_)
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
		for (const auto& i: character.locationModifiers_)
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
		for (const auto& i: character.locationGroupModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationGroupModifier>(i);
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (character.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: character.locationRequiredSkillModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationRequiredSkillModifier>(i);
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
