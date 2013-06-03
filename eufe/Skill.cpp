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
	Attribute* attribute;
	if (i != attributes_.end())
		attribute = i->second;
	else
#if _DEBUG
		attribute = attributes_[SKILL_LEVEL_ATTRIBUTE_ID] = new Attribute(engine, SKILL_LEVEL_ATTRIBUTE_ID, 0, 0.0, true, true, this, "skillLevel");
#else
		attribute = attributes_[SKILL_LEVEL_ATTRIBUTE_ID] = new Attribute(engine, SKILL_LEVEL_ATTRIBUTE_ID, 0, 0.0, true, true, this);
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

Environment Skill::getEnvironment()
{
	Environment environment;
	environment["Self"] = this;
	Character* character = dynamic_cast<Character*>(getOwner());
	Item* ship = character ? character->getShip() : NULL;
	Item* gang = character ? character->getOwner() : NULL;
	
	if (character)
		environment["Char"] = character;
	if (ship)
		environment["Ship"] = ship;
	if (gang)
		environment["Gang"] = gang;
	if (engine_->getArea())
		environment["Area"] = engine_->getArea();
	return environment;
}

Skill::Skill(Decoder& decoder, Engine* engine, Character* owner) : Item(decoder, engine, owner)
{
	decoder.decode(isLearned_);
}

void Skill::encode(Encoder& encoder)  const
{
	Item::encode(encoder);
	encoder.encode(isLearned_);
}