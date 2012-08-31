#include "Implant.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"

using namespace eufe;

Implant::Implant(Engine* engine, TypeID typeID, Character* owner) : Item(engine, typeID, owner)
{
	slot_ = static_cast<int>(getAttribute(IMPLANTNESS_ATTRIBUTE_ID)->getValue());
}

Implant::~Implant()
{
}

int Implant::getSlot()
{
	return slot_;
}

Environment Implant::getEnvironment()
{
	Environment environment;
	environment["Self"] = this;
	Character* character = dynamic_cast<Character*>(getOwner());
	Item* ship = character ? character->getShip() : nullptr;
	Item* gang = character ? character->getOwner() : nullptr;
	
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