#include "Area.h"
#include "Engine.h"
#include "Gang.h"
#include "Ship.h"
#include "Character.h"
#include "ControlTower.h"

using namespace eufe;

Area::Area(std::shared_ptr<Engine> engine, TypeID typeID) : Item(engine, typeID, nullptr)
{
}

Area::~Area()
{
}

void Area::addEffectsToShip(std::shared_ptr<Item> ship)
{
	Environment environment = getEnvironment();
	std::shared_ptr<Item> character = ship->getOwner();
	std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;

	environment["Ship"] = ship;
	if (character)
		environment["Char"] = character;
	if (gang)
		environment["Gang"] = gang;
	
	for (auto i: effects_)
		if (i->getCategory() == Effect::CATEGORY_SYSTEM)
			i->addEffect(environment);
}

void Area::removeEffectsFromShip(std::shared_ptr<Item> ship)
{
	Environment environment = getEnvironment();
	std::shared_ptr<Item> character = ship->getOwner();
	std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;
	
	environment["Ship"] = ship;
	if (character)
		environment["Char"] = character;
	if (gang)
		environment["Gang"] = gang;
	
	for (auto i: effects_)
		if (i->getCategory() == Effect::CATEGORY_SYSTEM)
			i->removeEffect(environment);
}

void Area::addEffects(Effect::Category category)
{
	if (category == Effect::CATEGORY_SYSTEM)
	{
		for (auto i: getEngine()->getGang()->getPilots())
			addEffectsToShip(i->getShip());
		std::shared_ptr<ControlTower> controlTower = getEngine()->getControlTower();
		if (controlTower)
			addEffectsToShip(controlTower);
	}
}

void Area::removeEffects(Effect::Category category)
{
	if (category == Effect::CATEGORY_SYSTEM)
	{
		for (auto i: getEngine()->getGang()->getPilots())
			removeEffectsFromShip(i->getShip());
		std::shared_ptr<ControlTower> controlTower = getEngine()->getControlTower();
		if (controlTower)
			removeEffectsFromShip(controlTower);
	}
}

Environment Area::getEnvironment()
{
	Environment environment;
	environment["Self"] = shared_from_this();
	environment["Area"] = shared_from_this();
	return environment;
}