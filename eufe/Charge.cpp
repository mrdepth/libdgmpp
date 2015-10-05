#include "Charge.h"
#include "Engine.h"
#include "Area.h"
#include "Gang.h"
#include "Module.h"

using namespace eufe;

Charge::Charge(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Item> owner) : Item(engine, typeID, owner)
{
}

Charge::~Charge()
{
}

Environment Charge::getEnvironment()
{
	Environment environment;
	environment["Self"] = shared_from_this();

	Item* module = getOwner();
	Item* ship = module ? module->getOwner() : nullptr;
	Item* character = ship ? ship->getOwner() : nullptr;
	Item* gang = character ? character->getOwner() : nullptr;
	
	if (character)
		environment["Char"] = character;
	if (ship)
		environment["Ship"] = ship;
	if (gang)
		environment["Gang"] = gang;
	if (engine_->getArea())
		environment["Area"] = engine_->getArea();
	if (module)
		environment["Other"] = module;
	
	return environment;
}