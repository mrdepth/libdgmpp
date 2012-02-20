#include "Charge.h"
#include "Engine.h"
#include "Area.h"
#include "Gang.h"
#include "Module.h"

using namespace eufe;

Charge::Charge(Engine* engine, TypeID typeID, Item* owner) : Item(engine, typeID, owner)
{
}

Charge::~Charge()
{
}

boost::shared_ptr<Environment> Charge::getEnvironment()
{
	boost::shared_ptr<Environment> environment(new Environment());
	(*environment)["Self"] = this;

	Item* module = getOwner();
	Item* ship = module != NULL ? module->getOwner() : NULL;
	Item* character = ship != NULL ? ship->getOwner() : NULL;
	Item* gang = character != NULL ? character->getOwner() : NULL;
	
	if (character != NULL)
		(*environment)["Char"] = character;
	if (ship != NULL)
		(*environment)["Ship"] = ship;
	if (gang != NULL)
		(*environment)["Gang"] = gang;
	if (engine_->getArea() != NULL)
		(*environment)["Area"] = engine_->getArea().get();
	if (module != NULL)
		(*environment)["Other"] = module;
	
	return environment;
}