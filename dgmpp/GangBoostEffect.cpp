#include "GangBoostEffect.h"
#include "Engine.h"
#include "Environment.h"
#include <memory>
#include "Gang.h"
#include "Attribute.h"

using namespace dgmpp;

GangBoostEffect::GangBoostEffect(std::shared_ptr<Engine> const& engine, std::shared_ptr<EffectPrototype> const& prototype, std::shared_ptr<Item> const& owner): Effect(engine, prototype, owner) {
	auto self = owner.get();
	
	static AttributeID ids[] = {WARFARE_BUFF1_ID_ATTRIBUTE_ID, WARFARE_BUFF2_ID_ATTRIBUTE_ID, WARFARE_BUFF3_ID_ATTRIBUTE_ID, WARFARE_BUFF4_ID_ATTRIBUTE_ID};
	static AttributeID values[] = {WARFARE_BUFF1_VALUE_ATTRIBUTE_ID, WARFARE_BUFF2_VALUE_ATTRIBUTE_ID, WARFARE_BUFF3_VALUE_ATTRIBUTE_ID, WARFARE_BUFF4_VALUE_ATTRIBUTE_ID};
	
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
