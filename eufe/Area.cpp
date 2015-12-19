#include "Area.h"
#include "Engine.h"
#include "Gang.h"
#include "Ship.h"
#include "Character.h"
#include "ControlTower.h"
#include "Environment.hpp"

using namespace eufe;

Area::Area(std::shared_ptr<Engine> const& engine, TypeID typeID) : Item(engine, typeID, nullptr)
{
}

Area::~Area()
{
}

void Area::addEffectsToShip(std::shared_ptr<Item> const&ship)
{
	Environment environment = getEnvironment();
	std::shared_ptr<Item> character = ship->getOwner();
	std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;

	/*environment["Ship"] = ship;
	if (character)
		environment["Char"] = character;
	if (gang)
		environment["Gang"] = gang;*/

	environment.ship = ship.get();
	environment.character = character.get();
	environment.gang = gang.get();

	for (const auto& i: effects_)
		if (i->getCategory() == Effect::CATEGORY_SYSTEM)
			i->addEffect(environment);
}

void Area::removeEffectsFromShip(std::shared_ptr<Item> const& ship)
{
	Environment environment = getEnvironment();
	std::shared_ptr<Item> character = ship->getOwner();
	std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;
	
/*	environment["Ship"] = ship;
	if (character)
		environment["Char"] = character;
	if (gang)
		environment["Gang"] = gang;*/
	environment.ship = ship.get();
	environment.character = character.get();
	environment.gang = gang.get();

	
	for (const auto& i: effects_)
		if (i->getCategory() == Effect::CATEGORY_SYSTEM)
			i->removeEffect(environment);
}

void Area::addEffects(Effect::Category category)
{
	auto engine = getEngine();
	if (!engine)
		return;
	loadIfNeeded();
	if (category == Effect::CATEGORY_SYSTEM)
	{
		for (const auto& i: engine->getGang()->getPilots())
			addEffectsToShip(i->getShip());
		std::shared_ptr<ControlTower> controlTower = engine->getControlTower();
		if (controlTower)
			addEffectsToShip(controlTower);
	}
}

void Area::removeEffects(Effect::Category category)
{
	auto engine = getEngine();
	if (!engine)
		return;
	loadIfNeeded();
	if (category == Effect::CATEGORY_SYSTEM)
	{
		for (const auto& i: engine->getGang()->getPilots())
			removeEffectsFromShip(i->getShip());
		std::shared_ptr<ControlTower> controlTower = engine->getControlTower();
		if (controlTower)
			removeEffectsFromShip(controlTower);
	}
}

Environment Area::buildEnvironment()
{
	Environment environment;
	//environment["Self"] = shared_from_this();
	//environment["Area"] = shared_from_this();
	environment.self = this;
	environment.area = this;
	return environment;
}