#include "Effect.h"
#include <iostream>
#include <fstream>
#include <ios>
#include "Compiler.h"
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

#include "EffectByteCodeInterpreter.h"
#include "EffectLeechInterpreter.h"
#include "EffectEnergyDestabilizationNewInterpreter.h"
#include "EffectEnergyTransferInterpreter.h"
#include "EffectArmorRepairInterpreter.h"
#include "EffectHullRepairInterpreter.h"
#include "EffectShieldBoostingInterpreter.h"
#include "EffectSlotModifierInterpreter.h"
#include "EffectHardPointModifierEffectInterpreter.h"
#include "EffectAdaptiveArmorHardener.h"

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

using namespace eufe;

const TypeID eufe::ONLINE_EFFECT_ID = 16;
const TypeID eufe::LO_POWER_EFFECT_ID = 11;
const TypeID eufe::HI_POWER_EFFECT_ID = 12;
const TypeID eufe::MED_POWER_EFFECT_ID = 13;
const TypeID eufe::RIG_SLOT_EFFECT_ID = 2663;
const TypeID eufe::SUBSYSTEM_EFFECT_ID = 3772;
const TypeID eufe::TURRET_FITTED_EFFECT_ID = 42;
const TypeID eufe::LAUNCHER_FITTED_EFFECT_ID = 40;

const TypeID eufe::MINING_LASER_EFFECT_ID = 61;
const TypeID eufe::POWER_BOOSTER_EFFECT_ID = 48;
const TypeID eufe::PROJECTILE_FIRED_EFFECT_ID = 34;
const TypeID eufe::TARGET_ATTACK_EFFECT_ID = 10;
const TypeID eufe::USE_MISSILES_EFFECT_ID = 101;

const TypeID eufe::LEECH_EFFECT_ID = 3250;
const TypeID eufe::ENERGY_DESTABILIZATION_NEW_EFFECT_ID = 2303;
const TypeID eufe::ENERGY_TRANSFER_EFFECT_ID = 31;

const TypeID eufe::WARP_DISRUPTION_FIELD_EFFECT_ONLINE_EFFECT_ID = 3461;

const TypeID eufe::ARMOR_REPAIR_EFFECT_ID = 27;
const TypeID eufe::TARGET_ARMOR_REPAIR_EFFECT_ID = 592;
const TypeID eufe::SHIELD_BOOSTING_EFFECT_ID = 4;
const TypeID eufe::SHIELD_TRANSFER_EFFECT_ID = 18;
const TypeID eufe::STRUCTURE_REPAIR_EFFECT_ID = 26;
const TypeID eufe::REMOTE_HULL_REPAIR_EFFECT_ID = 3041;
const TypeID eufe::SLOT_MODIFIER_EFFECT_ID = 3774;
const TypeID eufe::HARD_POINT_MODIFIER_EFFECT_EFFECT_ID = 3773;

const TypeID eufe::ONLINE_FOR_STRUCTURES_EFFECT_ID = 901;

const TypeID eufe::ADAPTIVE_ARMOR_HARDENER_EFFECT_ID = 4928;
const TypeID eufe::FUELED_SHIELD_BOOSTING_EFFECT_ID = 4936;

static std::map<TypeID, boost::weak_ptr<eufe::Effect> > reusableEffects;

boost::shared_ptr<eufe::Effect> Effect::getEffect(Engine* engine, int effectID)
{
	Engine::ScopedLock lock(*engine);

	std::map<TypeID, boost::weak_ptr<eufe::Effect> >::iterator i, end = reusableEffects.end();
	i = reusableEffects.find(effectID);
	if (i == end) {
		boost::shared_ptr<Effect> effect(new Effect(engine, effectID));
		reusableEffects[effectID] = boost::weak_ptr<Effect>(effect);
		return effect;
	}
	else {
		return i->second.lock();
	}
}

#if _DEBUG
Effect::Effect(Engine* engine, TypeID effectID, Category category, const void* byteCode, size_t size, bool isAssistance, bool isOffensive, const char* effectName) : engine_(engine), effectID_(effectID), category_(category), effectName_(effectName)
#else
Effect::Effect(Engine* engine, TypeID effectID, Category category, const void* byteCode, size_t size, bool isAssistance, bool isOffensive) : engine_(engine), effectID_(effectID), category_(category)
#endif
{
	if (effectID == LEECH_EFFECT_ID)
		interpreter_ = new EffectLeechInterpreter(engine, isAssistance, isOffensive);
	else if (effectID == ENERGY_DESTABILIZATION_NEW_EFFECT_ID)
		interpreter_ = new EffectEnergyDestabilizationNewInterpreter(engine, isAssistance, isOffensive);
	else if (effectID == ENERGY_TRANSFER_EFFECT_ID)
		interpreter_ = new EffectEnergyTransferInterpreter(engine, isAssistance, isOffensive);
	else if (effectID == ARMOR_REPAIR_EFFECT_ID)
		interpreter_ = new EffectArmorRepairInterpreter(engine, false, isAssistance, isOffensive);
	else if (effectID == TARGET_ARMOR_REPAIR_EFFECT_ID)
		interpreter_ = new EffectArmorRepairInterpreter(engine, true, isAssistance, isOffensive);
	else if (effectID == STRUCTURE_REPAIR_EFFECT_ID)
		interpreter_ = new EffectHullRepairInterpreter(engine, false, isAssistance, isOffensive);
	else if (effectID == REMOTE_HULL_REPAIR_EFFECT_ID)
		interpreter_ = new EffectHullRepairInterpreter(engine, true, isAssistance, isOffensive);
	else if (effectID == SHIELD_BOOSTING_EFFECT_ID)
		interpreter_ = new EffectShieldBoostingInterpreter(engine, false, isAssistance, isOffensive);
	else if (effectID == SHIELD_TRANSFER_EFFECT_ID)
		interpreter_ = new EffectShieldBoostingInterpreter(engine, true, isAssistance, isOffensive);
	else if (effectID == SLOT_MODIFIER_EFFECT_ID)
		interpreter_ = new EffectSlotModifierInterpreter(engine, isAssistance, isOffensive);
	else if (effectID == HARD_POINT_MODIFIER_EFFECT_EFFECT_ID)
		interpreter_ = new EffectHardPointModifierEffectInterpreter(engine, isAssistance, isOffensive);
	else if (effectID == ADAPTIVE_ARMOR_HARDENER_EFFECT_ID)
		interpreter_ = new EffectAdaptiveArmorHardener(engine, isAssistance, isOffensive);
	else if (effectID == FUELED_SHIELD_BOOSTING_EFFECT_ID)
		interpreter_ = new EffectShieldBoostingInterpreter(engine, false, isAssistance, isOffensive);
	else
		interpreter_ = new EffectByteCodeInterpreter(engine, byteCode, size, isAssistance, isOffensive);
#if _DEBUG
	std::string::iterator i, end = effectName_.end();
	for (i = effectName_.begin(); i != end; i++)
	{
		char c = *i;
		if (!((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
			*i = ' ';
	}
#endif
}

Effect::Effect(Engine* engine, TypeID effectID) : engine_(engine), effectID_(effectID)
{
	Engine::ScopedLock lock(*engine_);
	
	sqlite3* db = engine->getDb();
	std::stringstream sql;
#if _DEBUG
	sql << "SELECT effectCategory, isOffensive, isAssistance, byteCode, effectName FROM dgmCompiledEffects WHERE effectID = " << effectID;
#else
	sql << "SELECT effectCategory, isOffensive, isAssistance, byteCode FROM dgmCompiledEffects WHERE effectID = " << effectID;
#endif
	
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		category_ = static_cast<Effect::Category>(sqlite3_column_int(stmt, 0));
		bool isAssistance = sqlite3_column_int(stmt, 1) != 0;
		bool isOffensive = sqlite3_column_int(stmt, 2) != 0;
		size_t size = sqlite3_column_bytes(stmt, 3);
		const void* byteCode = sqlite3_column_blob(stmt, 3);
		
		if (effectID == LEECH_EFFECT_ID)
			interpreter_ = new EffectLeechInterpreter(engine, isAssistance, isOffensive);
		else if (effectID == ENERGY_DESTABILIZATION_NEW_EFFECT_ID)
			interpreter_ = new EffectEnergyDestabilizationNewInterpreter(engine, isAssistance, isOffensive);
		else if (effectID == ENERGY_TRANSFER_EFFECT_ID)
			interpreter_ = new EffectEnergyTransferInterpreter(engine, isAssistance, isOffensive);
		else if (effectID == ARMOR_REPAIR_EFFECT_ID)
			interpreter_ = new EffectArmorRepairInterpreter(engine, false, isAssistance, isOffensive);
		else if (effectID == TARGET_ARMOR_REPAIR_EFFECT_ID)
			interpreter_ = new EffectArmorRepairInterpreter(engine, true, isAssistance, isOffensive);
		else if (effectID == STRUCTURE_REPAIR_EFFECT_ID)
			interpreter_ = new EffectHullRepairInterpreter(engine, false, isAssistance, isOffensive);
		else if (effectID == REMOTE_HULL_REPAIR_EFFECT_ID)
			interpreter_ = new EffectHullRepairInterpreter(engine, true, isAssistance, isOffensive);
		else if (effectID == SHIELD_BOOSTING_EFFECT_ID)
			interpreter_ = new EffectShieldBoostingInterpreter(engine, false, isAssistance, isOffensive);
		else if (effectID == SHIELD_TRANSFER_EFFECT_ID)
			interpreter_ = new EffectShieldBoostingInterpreter(engine, true, isAssistance, isOffensive);
		else if (effectID == SLOT_MODIFIER_EFFECT_ID)
			interpreter_ = new EffectSlotModifierInterpreter(engine, isAssistance, isOffensive);
		else if (effectID == HARD_POINT_MODIFIER_EFFECT_EFFECT_ID)
			interpreter_ = new EffectHardPointModifierEffectInterpreter(engine, isAssistance, isOffensive);
		else if (effectID == ADAPTIVE_ARMOR_HARDENER_EFFECT_ID)
			interpreter_ = new EffectAdaptiveArmorHardener(engine, isAssistance, isOffensive);
		else if (effectID == FUELED_SHIELD_BOOSTING_EFFECT_ID)
			interpreter_ = new EffectShieldBoostingInterpreter(engine, false, isAssistance, isOffensive);
		else
			interpreter_ = new EffectByteCodeInterpreter(engine, byteCode, size, isAssistance, isOffensive);
		
		
#if _DEBUG
		effectName_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		std::string::iterator i, end = effectName_.end();
		for (i = effectName_.begin(); i != end; i++)
		{
			char c = *i;
			if (!((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
				*i = ' ';
		}
#endif
	}
	sqlite3_finalize(stmt);

}

Effect::Effect(const Effect& from) : interpreter_(from.interpreter_->clone())
{
#if _DEBUG
	effectName_ = from.effectName_;
#endif
}

Effect::~Effect(void)
{
	Engine::ScopedLock lock(*engine_);
	reusableEffects.erase(reusableEffects.find(effectID_));
	if (interpreter_)
		delete interpreter_;
}

bool Effect::addEffect(Environment environment)
{
	return interpreter_->addEffect(environment);
}

bool Effect::removeEffect(Environment environment)
{
	return interpreter_->removeEffect(environment);
}

TypeID Effect::getEffectID() const
{
	return effectID_;
}

Effect::Category Effect::getCategory() const
{
	return category_;
}

#if _DEBUG
const char* Effect::getEffectName() const
{
	return effectName_.c_str();
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::Effect& effect)
{
	os << "{\"effectName\":\"" << effect.effectName_<< "\", \"effectID\":\"" << effect.effectID_ << "\"}";
	return os;
}

#endif
