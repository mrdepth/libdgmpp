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
	boost::shared_ptr<Environment> environment = getEnvironment();
	Item* character = ship->getOwner();
	Item* gang = character != NULL ? character->getOwner() : NULL;

	(*environment)["Ship"] = ship;
	if (character != NULL)
		(*environment)["Char"] = character;
	if (gang != NULL)
		(*environment)["Gang"] = gang;
	
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == Effect::CATEGORY_SYSTEM)
			(*i)->addEffect(environment.get());
}

void Area::removeEffectsFromShip(Item* ship)
{
	boost::shared_ptr<Environment> environment = getEnvironment();
	Item* character = ship->getOwner();
	Item* gang = character != NULL ? character->getOwner() : NULL;
	
	(*environment)["Ship"] = ship;
	if (character != NULL)
		(*environment)["Char"] = character;
	if (gang != NULL)
		(*environment)["Gang"] = gang;
	
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == Effect::CATEGORY_SYSTEM)
			(*i)->removeEffect(environment.get());
}

void Area::addEffects(Effect::Category category)
{
	if (category == Effect::CATEGORY_SYSTEM)
	{
		const CharactersList& pilots = engine_->getGang()->getPilots();
		CharactersList::const_iterator i, end = pilots.end();
		
		for (i = pilots.begin(); i != end; i++)
			addEffectsToShip((*i)->getShip().get());
		boost::shared_ptr<ControlTower> controlTower = engine_->getControlTower();
		if (controlTower)
			addEffectsToShip(controlTower.get());
	}
}

void Area::removeEffects(Effect::Category category)
{
	if (category == Effect::CATEGORY_SYSTEM)
	{
		const CharactersList& pilots = engine_->getGang()->getPilots();
		CharactersList::const_iterator i, end = pilots.end();
		
		for (i = pilots.begin(); i != end; i++)
			removeEffectsFromShip((*i)->getShip().get());
		boost::shared_ptr<ControlTower> controlTower = engine_->getControlTower();
		if (controlTower)
			removeEffectsFromShip(controlTower.get());
	}
}

boost::shared_ptr<Environment> Area::getEnvironment()
{
	boost::shared_ptr<Environment> environment(new Environment());
	(*environment)["Self"] = this;
	(*environment)["Area"] = this;
	return environment;
}