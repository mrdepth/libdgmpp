#include "Area.h"
#include "Engine.h"
#include "Gang.h"
#include "Ship.h"
#include "Character.h"
#include "ControlTower.h"

using namespace eufe;

Area::Area(Engine* engine, TypeID typeID) : Item(engine, typeID, nullptr)
{
}

Area::~Area()
{
}

void Area::addEffectsToShip(Item* ship)
{
	Environment environment = getEnvironment();
	Item* character = ship->getOwner();
	Item* gang = character ? character->getOwner() : nullptr;

	environment["Ship"] = ship;
	if (character)
		environment["Char"] = character;
	if (gang)
		environment["Gang"] = gang;
	
	for (auto i: effects_)
		if (i->getCategory() == Effect::CATEGORY_SYSTEM)
			i->addEffect(environment);
}

void Area::removeEffectsFromShip(Item* ship)
{
	Environment environment = getEnvironment();
	Item* character = ship->getOwner();
	Item* gang = character ? character->getOwner() : nullptr;
	
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
		for (auto i: engine_->getGang()->getPilots())
			addEffectsToShip(i->getShip());
		ControlTower* controlTower = engine_->getControlTower();
		if (controlTower)
			addEffectsToShip(controlTower);
	}
}

void Area::removeEffects(Effect::Category category)
{
	if (category == Effect::CATEGORY_SYSTEM)
	{
		for (auto i: engine_->getGang()->getPilots())
			removeEffectsFromShip(i->getShip());
		ControlTower* controlTower = engine_->getControlTower();
		if (controlTower)
			removeEffectsFromShip(controlTower);
	}
}

Environment Area::getEnvironment()
{
	Environment environment;
	environment["Self"] = this;
	environment["Area"] = this;
	return environment;
}