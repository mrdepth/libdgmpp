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

boost::shared_ptr<Environment> Implant::getEnvironment()
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