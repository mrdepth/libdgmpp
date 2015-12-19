#include "Booster.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"
#include "Environment.hpp"

using namespace eufe;

Booster::Booster(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner) : Item(engine, typeID, owner), slot_(-1)
{
}

Booster::~Booster()
{
}

int Booster::getSlot()
{
	loadIfNeeded();
	return slot_;
}

Environment Booster::buildEnvironment()
{
	Environment environment;
	auto engine = getEngine();
	if (engine) {
		/*environment["Self"] = shared_from_this();
		std::shared_ptr<Character> character = std::dynamic_pointer_cast<Character>(getOwner());
		std::shared_ptr<Item> ship = character ? character->getShip() : nullptr;
		std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;
		std::shared_ptr<Area> area = engine->getArea();
		
		if (character)
			environment["Char"] = character;
		if (ship)
			environment["Ship"] = ship;
		if (gang)
			environment["Gang"] = gang;
		if (area)
			environment["Area"] = area;*/
		environment.self = this;
		environment.character = getOwner().get();
		environment.ship = environment.character ? dynamic_cast<Character*>(environment.character)->getShip().get() : nullptr;
		environment.gang = environment.character ? environment.character->getOwner().get() : nullptr;
		environment.area = engine->getArea().get();
	}
	return environment;
}

void Booster::lazyLoad() {
	Item::lazyLoad();
	slot_ = static_cast<int>(getAttribute(BOOSTERNESS_ATTRIBUTE_ID)->getValue());
}