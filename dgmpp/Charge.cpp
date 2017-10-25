#include "Charge.h"
#include "Engine.h"
#include "Area.h"
#include "Gang.h"
#include "Module.h"

using namespace dgmpp;

Charge::Charge(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner) : Item(engine, typeID, owner)
{
}

Charge::~Charge()
{
}

bool Charge::isAssistance() {
	loadIfNeeded();
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::Category::target)
			return  effect->isAssistance();
	return false;
}

bool Charge::isOffensive() {
	loadIfNeeded();
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::Category::target)
			return  effect->isOffensive();
	return false;
}

bool Charge::canBeActive() {
	loadIfNeeded();
	return canBeActive_;
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

void Charge::lazyLoad() {
	Item::lazyLoad();
	canBeActive_ = false;
	
	for (const auto& i: effects_)
	{
		Effect::Category category = i->getCategory();
		if (category == Effect::Category::active ||
			category == Effect::Category::target ||
			category == Effect::Category::overloaded) {
			canBeActive_ = true;
			break;
		}
	}
}
