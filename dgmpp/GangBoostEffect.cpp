#include "GangBoostEffect.h"
#include "Engine.h"
#include "Environment.h"
#include <memory>
#include "Gang.h"
#include "Attribute.h"

using namespace dgmpp;

GangBoostEffect::GangBoostEffect(std::shared_ptr<Engine> const& engine, std::shared_ptr<EffectPrototype> const& prototype, std::shared_ptr<Item> const& owner): Effect(engine, prototype, owner) {
	auto self = owner.get();
	
	
	
	static AttributeID ids[] = {AttributeID::warfareBuff1ID, AttributeID::warfareBuff2ID, AttributeID::warfareBuff3ID, AttributeID::warfareBuff4ID};
	static AttributeID values[] = {AttributeID::warfareBuff1Value, AttributeID::warfareBuff2Value, AttributeID::warfareBuff3Value, AttributeID::warfareBuff4Value};
	
	std::list<std::shared_ptr<GangBoost>> boosters;
	
	int i = 0;
	for (auto value: values) {
		if (self->hasAttribute(value)) {
			auto booster = std::make_shared<GangBoost>(engine, self->getAttribute(ids[i]), self->getAttribute(value));
			boosts_.push_back(booster);
		}
		i++;
	}
}

bool GangBoostEffect::addEffect(Environment* environment) {
	auto gang = dynamic_cast<Gang*>(environment->gang());
	for (const auto& booster: boosts_) {
		gang->addGangBoost(booster);
	}
	return true;
}

bool GangBoostEffect::removeEffect(Environment* environment) {
	auto gang = dynamic_cast<Gang*>(environment->gang());
	for (const auto& booster: boosts_) {
		gang->removeGangBoost(booster);
	}
	return true;
}
