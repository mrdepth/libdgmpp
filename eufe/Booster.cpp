#include "Booster.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"

using namespace eufe;

Booster::Booster(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Character> owner) : Item(engine, typeID, owner), slot_(-1)
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

Environment Booster::getEnvironment()
{
	Environment environment;
	auto engine = getEngine();
	if (engine) {
		environment["Self"] = shared_from_this();
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
			environment["Area"] = area;
	}
	return environment;
}

void Booster::lazyLoad() {
	Item::lazyLoad();
	slot_ = static_cast<int>(getAttribute(BOOSTERNESS_ATTRIBUTE_ID)->getValue());
}