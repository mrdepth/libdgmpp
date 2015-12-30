#include "Booster.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"

using namespace dgmpp;

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

void Booster::lazyLoad() {
	Item::lazyLoad();
	slot_ = static_cast<int>(getAttribute(BOOSTERNESS_ATTRIBUTE_ID)->getValue());
}

Item* Booster::character() {
	return getOwner().get();
}

Item* Booster::ship() {
	return character()->ship();
}
