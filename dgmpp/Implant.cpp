#include "Implant.h"
#include "Character.h"
#include "Attribute.h"
#include "Ship.h"
#include "Engine.h"
#include "Area.h"

using namespace dgmpp;

Implant::Implant(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner) : Item(engine, typeID, owner), slot_(-1)
{
}

Implant::~Implant()
{
}

int Implant::getSlot()
{
	loadIfNeeded();
	return slot_;
}

void Implant::lazyLoad() {
	Item::lazyLoad();
	slot_ = static_cast<int>(getAttribute(IMPLANTNESS_ATTRIBUTE_ID)->getValue());
}

Item* Implant::character() {
	return getOwner().get();
}

Item* Implant::ship() {
	return character()->ship();
}
