#include "Area.h"
#include "Engine.h"
#include "Gang.h"
#include "Ship.h"
#include "Character.h"
#include "ControlTower.h"

using namespace dgmpp;

class AreaEnvironment: public Environment {
public:
	AreaEnvironment(Item* area, Item* ship) {
		area_ = area;
		ship_ = ship;
		character_ = ship ? ship->getOwner().get() : nullptr;
		gang_ = ship ? ship->getEngine()->getGang().get() : nullptr;
	}
	Item* ship_;
	Item* character_;
	Item* gang_;
	Item* area_;
	virtual Item* ship() {
		return ship_;
	}
	virtual Item* character() {
		return character_;
	}
	virtual Item* gang() {
		return gang_;
	}
	virtual Item* area() {
		return area_;
	}
	virtual Item* self() {
		return area_;
	}
};

Area::Area(std::shared_ptr<Engine> const& engine, TypeID typeID) : Item(engine, typeID, nullptr)
{
}

Area::~Area()
{
}

void Area::addEffectsToShip(std::shared_ptr<Item> const&ship)
{
	AreaEnvironment environment(this, ship.get());

	for (const auto& i: effects_)
		if (i->getCategory() == Effect::CATEGORY_SYSTEM)
			i->addEffect(&environment);
}

void Area::removeEffectsFromShip(std::shared_ptr<Item> const& ship)
{
	AreaEnvironment environment(this, ship.get());

	for (const auto& i: effects_)
		if (i->getCategory() == Effect::CATEGORY_SYSTEM)
			i->removeEffect(&environment);
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
