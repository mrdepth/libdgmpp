#include "Skill.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"

using namespace dgmpp;

Skill::Skill(std::shared_ptr<Engine> const& engine, TypeID typeID, int skillLevel, bool isLearned, std::shared_ptr<Character> const& owner) : Item(engine, typeID, owner), isLearned_(isLearned), skillLevel_(skillLevel)
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
	return static_cast<int>(getAttribute(AttributeID::skillLevel)->getValue());
}

void Skill::setSkillLevel(int level)
{
	getAttribute(AttributeID::skillLevel)->setValue(static_cast<Float>(level));
}

void Skill::lazyLoad() {
	Item::lazyLoad();
	AttributesMap::iterator i = attributes_.find(AttributeID::skillLevel);
	std::shared_ptr<Attribute> attribute;
	if (i != attributes_.end())
		attribute = i->second;
	else
		attribute = addExtraAttribute(AttributeID::skillLevel, 0);
	attribute->setValue(static_cast<Float>(skillLevel_));
}

Item* Skill::character() {
	return getOwner().get();
}

Item* Skill::ship() {
	return character()->ship();
}

Item* Skill::structure() {
	return character()->structure();
}

namespace dgmpp2 {
	
}
