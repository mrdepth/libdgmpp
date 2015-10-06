#include "Skill.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"

using namespace eufe;

Skill::Skill(std::shared_ptr<Engine> engine, TypeID typeID, int skillLevel, bool isLearned, std::shared_ptr<Character> owner) : Item(engine, typeID, owner), isLearned_(isLearned), skillLevel_(skillLevel)
{
}

Skill::~Skill(void)
{
}

bool Skill::isLearned() const
{
	return isLearned_;
}

int Skill::getSkillLevel()
{
	return static_cast<int>(getAttribute(SKILL_LEVEL_ATTRIBUTE_ID)->getValue());
}

void Skill::setSkillLevel(int level)
{
	getAttribute(SKILL_LEVEL_ATTRIBUTE_ID)->setValue(static_cast<float>(level));
}

Environment Skill::getEnvironment()
{
	Environment environment;
	environment["Self"] = shared_from_this();
	std::shared_ptr<Character> character = std::dynamic_pointer_cast<Character>(getOwner());
	std::shared_ptr<Item> ship = character ? character->getShip() : nullptr;
	std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;
	std::shared_ptr<Area> area = engine_.lock()->getArea();
	
	if (character)
		environment["Char"] = character;
	if (ship)
		environment["Ship"] = ship;
	if (gang)
		environment["Gang"] = gang;
	if (area)
		environment["Area"] = area;
	return environment;
}

void Skill::lazyLoad() {
	Item::lazyLoad();
	AttributesMap::iterator i = attributes_.find(SKILL_LEVEL_ATTRIBUTE_ID);
	std::shared_ptr<Attribute> attribute;
	if (i != attributes_.end())
		attribute = i->second;
	else
		attribute = addExtraAttribute(SKILL_LEVEL_ATTRIBUTE_ID, 0, 0, true, true);
	attribute->setValue(static_cast<float>(skillLevel_));
}
