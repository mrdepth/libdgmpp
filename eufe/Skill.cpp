#include "Skill.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"

using namespace eufe;

Skill::Skill(Engine* engine, TypeID typeID, int skillLevel, bool isLearned, Character* owner) : Item(engine, typeID, owner), isLearned_(isLearned)
{
	AttributesMap::iterator i = attributes_.find(SKILL_LEVEL_ATTRIBUTE_ID);
	boost::shared_ptr<Attribute> attribute;
	if (i != attributes_.end())
		attribute = i->second;
	else
#if _DEBUG
		attribute = attributes_[SKILL_LEVEL_ATTRIBUTE_ID] = boost::shared_ptr<Attribute>(new Attribute(engine, SKILL_LEVEL_ATTRIBUTE_ID, 0, 0.0, true, true, this, "skillLevel"));
#else
		attribute = attributes_[SKILL_LEVEL_ATTRIBUTE_ID] = boost::shared_ptr<Attribute>(new Attribute(engine, SKILL_LEVEL_ATTRIBUTE_ID, 0, 0.0, true, true, this));
#endif
	attribute->setValue(static_cast<float>(skillLevel));
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

boost::shared_ptr<Environment> Skill::getEnvironment()
{
	boost::shared_ptr<Environment> environment(new Environment());
	(*environment)["Self"] = this;
	Character* character = dynamic_cast<Character*>(getOwner());
	Item* ship = character != NULL ? character->getShip().get() : NULL;
	Item* gang = character != NULL ? character->getOwner() : NULL;
	
	if (character != NULL)
		(*environment)["Char"] = character;
	if (ship != NULL)
		(*environment)["Ship"] = ship;
	if (gang != NULL)
		(*environment)["Gang"] = gang;
	if (engine_->getArea() != NULL)
		(*environment)["Area"] = engine_->getArea().get();
	return environment;
}
