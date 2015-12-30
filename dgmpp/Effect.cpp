#include "Effect.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>
//#include "Compiler.h"
#include "Ship.h"
#include "Module.h"
#include <cctype>
#include <algorithm>
#include "Item.h"
#include "Attribute.h"
#include "Engine.h"
#include "Character.h"

#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"

/*#include "EffectByteCodeInterpreter.h"
#include "EffectLeechInterpreter.h"
#include "EffectEnergyDestabilizationNewInterpreter.h"
#include "EffectEnergyTransferInterpreter.h"
#include "EffectArmorRepairInterpreter.h"
#include "EffectHullRepairInterpreter.h"
#include "EffectShieldBoostingInterpreter.h"
#include "EffectSlotModifierInterpreter.h"
#include "EffectHardPointModifierEffectInterpreter.h"
#include "EffectAdaptiveArmorHardener.h"
#include "EffectNaniteRepairPasteArmorDamageBonus.h"*/
#include "EffectPrototype.h"

using namespace dgmpp;

const TypeID dgmpp::ONLINE_EFFECT_ID = 16;
const TypeID dgmpp::LO_POWER_EFFECT_ID = 11;
const TypeID dgmpp::HI_POWER_EFFECT_ID = 12;
const TypeID dgmpp::MED_POWER_EFFECT_ID = 13;
const TypeID dgmpp::RIG_SLOT_EFFECT_ID = 2663;
const TypeID dgmpp::SUBSYSTEM_EFFECT_ID = 3772;
const TypeID dgmpp::TURRET_FITTED_EFFECT_ID = 42;
const TypeID dgmpp::LAUNCHER_FITTED_EFFECT_ID = 40;

const TypeID dgmpp::MINING_LASER_EFFECT_ID = 61;
const TypeID dgmpp::POWER_BOOSTER_EFFECT_ID = 48;
const TypeID dgmpp::PROJECTILE_FIRED_EFFECT_ID = 34;
const TypeID dgmpp::TARGET_ATTACK_EFFECT_ID = 10;
const TypeID dgmpp::USE_MISSILES_EFFECT_ID = 101;

const TypeID dgmpp::LEECH_EFFECT_ID = 3250;
const TypeID dgmpp::ENERGY_NOSFERATU_FALLOFF = 6197;
const TypeID dgmpp::ENERGY_DESTABILIZATION_NEW_EFFECT_ID = 2303;
const TypeID dgmpp::ENERGY_TRANSFER_EFFECT_ID = 31;

const TypeID dgmpp::WARP_DISRUPTION_FIELD_EFFECT_ONLINE_EFFECT_ID = 3461;

const TypeID dgmpp::ARMOR_REPAIR_EFFECT_ID = 27;
const TypeID dgmpp::TARGET_ARMOR_REPAIR_EFFECT_ID = 592;
const TypeID dgmpp::SHIELD_BOOSTING_EFFECT_ID = 4;
const TypeID dgmpp::SHIELD_TRANSFER_EFFECT_ID = 18;
const TypeID dgmpp::STRUCTURE_REPAIR_EFFECT_ID = 26;
const TypeID dgmpp::REMOTE_HULL_REPAIR_EFFECT_ID = 3041;
const TypeID dgmpp::SLOT_MODIFIER_EFFECT_ID = 3774;
const TypeID dgmpp::HARD_POINT_MODIFIER_EFFECT_EFFECT_ID = 3773;

const TypeID dgmpp::ONLINE_FOR_STRUCTURES_EFFECT_ID = 901;

const TypeID dgmpp::ADAPTIVE_ARMOR_HARDENER_EFFECT_ID = 4928;
const TypeID dgmpp::FUELED_SHIELD_BOOSTING_EFFECT_ID = 4936;
const TypeID dgmpp::FUELED_ARMOR_REPAIR__EFFECT_ID = 5275;

const TypeID dgmpp::NANITE_REPAIR_PASTE_ARMOR_DAMAGE_BONUS_EFFECT_ID = 10001;
const TypeID dgmpp::TACTICAL_MODE_EFFECT_ID = 10002;

std::shared_ptr<dgmpp::Effect> Effect::getEffect(std::shared_ptr<Engine> const& engine, TypeID effectID, std::shared_ptr<Item> const& owner)
{
	return std::make_shared<Effect>(engine, EffectPrototype::getEffectPrototype(engine, effectID), owner);
}

Effect::Effect(std::shared_ptr<Engine> const& engine, std::shared_ptr<EffectPrototype> const& prototype, std::shared_ptr<Item> const& owner) : engine_(engine), prototype_(prototype), owner_(owner)
{
	auto env = owner.get();

	for (const auto& modifierPrototype: prototype->getModifierPrototypes()) {
		std::shared_ptr<Modifier> modifier;
		switch (modifierPrototype->type) {
			case Modifier::ITEM_MODIFIER:
			case Modifier::LOCATION_MODIFIER:
				modifier = std::make_shared<Modifier>(modifierPrototype->domain,
													  modifierPrototype->modifiedAttributeID,
													  modifierPrototype->association,
													  env->self()->getAttribute(modifierPrototype->modifyingAttributeID),
													  isAssistance(),
													  isOffensive(),
													  dynamic_cast<Character*>(env->character()));
				break;
			case Modifier::LOCATION_GROUP_MODIFIER:
				modifier = std::make_shared<LocationGroupModifier>(modifierPrototype->domain,
																   modifierPrototype->modifiedAttributeID,
																   modifierPrototype->association,
																   env->self()->getAttribute(modifierPrototype->modifyingAttributeID),
																   modifierPrototype->requiredID,
																   isAssistance(),
																   isOffensive(),
																   dynamic_cast<Character*>(env->character()));
				break;
			case Modifier::LOCATION_REQUIRED_SKILL_MODIFIER:
			case Modifier::OWNER_REQUIRED_SKILL_MODIFIER:
				modifier = std::make_shared<LocationRequiredSkillModifier>(modifierPrototype->domain,
																		   modifierPrototype->modifiedAttributeID,
																		   modifierPrototype->association,
																		   env->self()->getAttribute(modifierPrototype->modifyingAttributeID),
																		   modifierPrototype->requiredID,
																		   isAssistance(),
																		   isOffensive(),
																		   dynamic_cast<Character*>(env->character()));
				break;
			case Modifier::LOCATION_REQUIRED_DOMAIN_SKILL_MODIFIER:
				modifier = std::make_shared<LocationRequiredSkillModifier>(modifierPrototype->domain,
																		   modifierPrototype->modifiedAttributeID,
																		   modifierPrototype->association,
																		   env->self()->getAttribute(modifierPrototype->modifyingAttributeID),
																		   (*env)[static_cast<Modifier::Domain>(modifierPrototype->requiredID)]->getTypeID(),
																		   isAssistance(),
																		   isOffensive(),
																		   dynamic_cast<Character*>(env->character()));
				break;
			default:
				throw std::bad_typeid();
				break;
		}
		modifiers_[modifierPrototype->type].push_back(modifier);
	}
}

Effect::~Effect(void)
{
	//reusableEffects.erase(reusableEffects.find(effectID_));
}

bool Effect::addEffect(Environment* env)
{
	for (const auto& i: modifiers_) {
		switch (i.first) {
			case Modifier::ITEM_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->addItemModifier(modifier);
				}
				break;
			case Modifier::LOCATION_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->addLocationModifier(modifier);
				}
				break;
			case Modifier::LOCATION_GROUP_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->addLocationGroupModifier(std::dynamic_pointer_cast<LocationGroupModifier> (modifier));
				}
				break;
			case Modifier::LOCATION_REQUIRED_SKILL_MODIFIER:
			case Modifier::LOCATION_REQUIRED_DOMAIN_SKILL_MODIFIER:
			case Modifier::OWNER_REQUIRED_SKILL_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->addLocationRequiredSkillModifier(std::dynamic_pointer_cast<LocationRequiredSkillModifier> (modifier));
				}
				break;
			default:
				break;
		}
	}
	return true;
}

bool Effect::removeEffect(Environment* env)
{
	for (const auto& i: modifiers_) {
		switch (i.first) {
			case Modifier::ITEM_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->removeItemModifier(modifier);
				}
				break;
			case Modifier::LOCATION_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->removeLocationModifier(modifier);
				}
				break;
			case Modifier::LOCATION_GROUP_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->removeLocationGroupModifier(std::dynamic_pointer_cast<LocationGroupModifier> (modifier));
				}
				break;
			case Modifier::LOCATION_REQUIRED_SKILL_MODIFIER:
			case Modifier::LOCATION_REQUIRED_DOMAIN_SKILL_MODIFIER:
			case Modifier::OWNER_REQUIRED_SKILL_MODIFIER:
				for (const auto& modifier: i.second) {
					auto item = (*env)[modifier->getDomain()];
					if (item)
						item->removeLocationRequiredSkillModifier(std::dynamic_pointer_cast<LocationRequiredSkillModifier> (modifier));
				}
				break;
			default:
				break;
		}
	}
	return true;
}

TypeID Effect::getEffectID() const
{
	return prototype_->getEffectID();
}

Effect::Category Effect::getCategory() const
{
	return prototype_->getCategory();
}

const char* Effect::getEffectName() const
{
	return prototype_->getEffectName();
}

bool Effect::isAssistance() const {
	return prototype_->isAssistance();
}

bool Effect::isOffensive() const {
	return prototype_->isOffensive();
}

std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Effect& effect)
{
	os << "{\"effectName\":\"" << effect.getEffectName()<< "\", \"effectID\":\"" << effect.getEffectID() << "\"}";
	return os;
}
