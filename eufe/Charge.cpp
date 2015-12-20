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
		if (effect->getCategory() == Effect::CATEGORY_TARGET)
			return  effect->isAssistance();
	return false;
}

bool Charge::isOffensive() {
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::CATEGORY_TARGET)
			return  effect->isOffensive();
	return false;
}

Item* Charge::ship() {
	return other()->getOwner().get();
}

Item* Charge::character() {
	return ship()->character();
}

Item* Charge::other() {
	return getOwner().get();
}
