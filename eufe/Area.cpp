#include "Area.h"
#include "Engine.h"
#include "Gang.h"
#include "Ship.h"
#include "Character.h"
#include "ControlTower.h"

using namespace eufe;

Area::Area(Engine* engine, TypeID typeID) : Item(engine, typeID, NULL)
{
}

Area::~Area()
{
}

void Area::addEffectsToShip(Item* ship)
{
	Environment environment = getEnvironment();
	Item* character = ship->getOwner();
	Item* gang = character ? character->getOwner() : NULL;

	environment["Ship"] = ship;
	if (character)
		environment["Char"] = character;
	if (gang)
		environment["Gang"] = gang;
	
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == Effect::CATEGORY_SYSTEM)
			(*i)->addEffect(environment);
}

void Area::removeEffectsFromShip(Item* ship)
{
	Environment environment = getEnvironment();
	Item* character = ship->getOwner();
	Item* gang = character ? character->getOwner() : NULL;
	
	environment["Ship"] = ship;
	if (character)
		environment["Char"] = character;
	if (gang)
		environment["Gang"] = gang;
	
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == Effect::CATEGORY_SYSTEM)
			(*i)->removeEffect(environment);
}

void Area::addEffects(Effect::Category category)
{
	if (category == Effect::CATEGORY_SYSTEM)
	{
		const CharactersList& pilots = engine_->getGang()->getPilots();
		CharactersList::const_iterator i, end = pilots.end();
		for (i = pilots.begin(); i != end; i++)
			addEffectsToShip((*i)->getShip());
		ControlTower* controlTower = engine_->getControlTower();
		if (controlTower)
			addEffectsToShip(controlTower);
	}
}

void Area::removeEffects(Effect::Category category)
{
	if (category == Effect::CATEGORY_SYSTEM)
	{
		const CharactersList& pilots = engine_->getGang()->getPilots();
		CharactersList::const_iterator i, end = pilots.end();
		for (i = pilots.begin(); i != end; i++)
			removeEffectsFromShip((*i)->getShip());
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