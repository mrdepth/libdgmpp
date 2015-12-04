#include "Charge.h"
#include "Engine.h"
#include "Area.h"
#include "Gang.h"
#include "Module.h"

using namespace eufe;

Charge::Charge(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner) : Item(engine, typeID, owner)
{
}

Charge::~Charge()
{
}

bool Charge::isAssistance() {
	for (const auto& effect: getEffects())
		if (effect->isAssistance())
			return true;
	return false;
}

bool Charge::isOffensive() {
	for (const auto& effect: getEffects())
		if (effect->isOffensive())
			return true;
	return false;
}

Environment Charge::getEnvironment()
{
	Environment environment;
	auto engine = getEngine();
	if (engine) {
		environment["Self"] = shared_from_this();
		
		std::shared_ptr<Item> module = getOwner();
		std::shared_ptr<Item> ship = module ? module->getOwner() : nullptr;
		std::shared_ptr<Item> character = ship ? ship->getOwner() : nullptr;
		std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;
		std::shared_ptr<Area> area = engine->getArea();
		if (character)
			environment["Char"] = character;
		if (ship)
			environment["Ship"] = ship;
		if (gang)
			environment["Gang"] = gang;
		if (area)
			environment["Area"] = area;
		if (module)
			environment["Other"] = module;
	}
	
	return environment;
}