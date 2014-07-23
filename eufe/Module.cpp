#include "Module.h"
#include "Ship.h"
#include "Effect.h"
#include "Attribute.h"
#include "Engine.h"
#include "Area.h"
#include "Charge.h"
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include "HeatSimulator.h"
#include <algorithm>

using namespace eufe;

Module::Module(Engine* engine, TypeID typeID, Item* owner) : Item(engine, typeID, owner), state_(STATE_OFFLINE), target_(NULL), reloadTime_(0), forceReload_(false), charge_(NULL)
{
	#if _DEBUG
		attributes_[IS_ONLINE_ATTRIBUTE_ID] = new Attribute(engine, IS_ONLINE_ATTRIBUTE_ID, 0, 0.0, true, true, this, "isOnline");
	#else
		attributes_[IS_ONLINE_ATTRIBUTE_ID] = new Attribute(engine, IS_ONLINE_ATTRIBUTE_ID, 0, 0.0, true, true, this);
	#endif

	if (hasEffect(LO_POWER_EFFECT_ID))
		slot_ = SLOT_LOW;
	else if (hasEffect(MED_POWER_EFFECT_ID))
		slot_ = SLOT_MED;
	else if (hasEffect(HI_POWER_EFFECT_ID))
		slot_ = SLOT_HI;
	else if (hasEffect(RIG_SLOT_EFFECT_ID))
		slot_ = SLOT_RIG;
	else if (hasEffect(SUBSYSTEM_EFFECT_ID))
		slot_ = SLOT_SUBSYSTEM;
	else if (getCategoryID() == STRUCTURE_CATEGORY_ID)
		slot_ = SLOT_STRUCTURE;
	else
		slot_ = SLOT_NONE;
	
	if (hasAttribute(RELOAD_TIME_ATTRIBUTE_ID))
		reloadTime_ = getAttribute(RELOAD_TIME_ATTRIBUTE_ID)->getValue();
	else
	{
		if (hasEffect(MINING_LASER_EFFECT_ID) || hasEffect(TARGET_ATTACK_EFFECT_ID) || hasEffect(USE_MISSILES_EFFECT_ID))
			reloadTime_ = 1000;
		else if (hasEffect(POWER_BOOSTER_EFFECT_ID) || hasEffect(PROJECTILE_FIRED_EFFECT_ID))
			reloadTime_ = 10000;
	}
		
	if (hasEffect(TURRET_FITTED_EFFECT_ID))
		hardpoint_ = HARDPOINT_TURRET;
	else if (hasEffect(LAUNCHER_FITTED_EFFECT_ID))
		hardpoint_ = HARDPOINT_LAUNCHER;
	else
		hardpoint_ = HARDPOINT_NONE;

	canBeOnline_ = hasEffect(ONLINE_EFFECT_ID) || hasEffect(ONLINE_FOR_STRUCTURES_EFFECT_ID);

	state_ = STATE_OFFLINE;

	canBeActive_ = false;
	canBeOverloaded_ = false;
	requireTarget_ = false;
	int n = 0;
	
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
	{
		Effect::Category category = (*i)->getCategory();
		if (category == Effect::CATEGORY_ACTIVE)
		{
			n++;
			if (n >= 2)
			{
				canBeActive_ = true;
			}
		}
		else if (category == Effect::CATEGORY_TARGET)
		{
			canBeActive_ = true;
			requireTarget_ = true;
		}
		else if (category == Effect::CATEGORY_OVERLOADED)
		{
			canBeActive_ = true;
			canBeOverloaded_ = true;
		}
	}
	forceReload_ = groupID_ == CAPACITOR_BOOSTER_GROUP_ID;
	
	shots_ = -1;
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
	
	TypeID attributes[] = {CHARGE_GROUP1_ATTRIBUTE_ID, CHARGE_GROUP2_ATTRIBUTE_ID, CHARGE_GROUP3_ATTRIBUTE_ID, CHARGE_GROUP4_ATTRIBUTE_ID, CHARGE_GROUP5_ATTRIBUTE_ID};
	for (int i = 0; i < 5; i++)
		if (hasAttribute(attributes[i]))
		{
			TypeID typeID = static_cast<TypeID>(getAttribute(attributes[i])->getValue());
			if (typeID > 0) {
				chargeGroups_.push_back(typeID);
				if (!forceReload_ && (typeID == CAPACITOR_BOOSTER_CHARGE_GROUP_ID || typeID == NANITE_REPAIR_PASTE_GROUP_ID))
					forceReload_ = true;
			}
		}
	std::sort(chargeGroups_.begin(), chargeGroups_.end());
}

Module::Module(const Module& from) :	Item(from),
										canBeOnline_(from.canBeOnline_),
										canBeActive_(from.canBeActive_),
										canBeOverloaded_(from.canBeOverloaded_),
										requireTarget_(from.requireTarget_),
										slot_(from.slot_),
										hardpoint_(from.hardpoint_),
										state_(STATE_OFFLINE),
										chargeGroups_(from.chargeGroups_),
										target_(NULL),
										reloadTime_(from.reloadTime_),
										shots_(from.shots_),
										forceReload_(from.forceReload_),
										charge_(NULL)
{
	if (from.charge_)
	{
		charge_ = new Charge(*from.charge_);
		charge_->setOwner(this);
	}
	shots_ = -1;
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
}

Module::~Module(void)
{
	if (charge_)
		delete charge_;
	if (target_)
		clearTarget();
}

Attribute* Module::getAttribute(TypeID attributeID)
{
	Engine::ScopedLock lock(*engine_);
	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return i->second;
	else
		return attributes_[attributeID] = new Attribute(engine_, attributeID, this);
}

Module::Slot Module::getSlot()
{
	return slot_;
}

Module::Hardpoint Module::getHardpoint()
{
	return hardpoint_;
}

bool Module::canHaveState(State state)
{
	bool canHaveState =	 state == STATE_OFFLINE ||
						(state == STATE_ONLINE && canBeOnline_) ||
						(state == STATE_ACTIVE && canBeActive_) ||
						(state == STATE_OVERLOADED && canBeOverloaded_);
	if (canHaveState && state >= STATE_ACTIVE)
	{
		if (getAttribute(ACTIVATION_BLOCKED_ATTRIBUTE_ID)->getValue() > 0)
			return false;
			
		Ship* ship = dynamic_cast<Ship*>(getOwner());
		
		if (hasAttribute(MAX_GROUP_ACTIVE_ATTRIBUTE_ID))
		{
			int maxGroupActive = static_cast<int>(getAttribute(MAX_GROUP_ACTIVE_ATTRIBUTE_ID)->getValue()) - 1;
			
			const ModulesList& modules = ship->getModules();
			ModulesList::const_iterator i, end = modules.end();
			for (i = modules.begin(); i != end; i++)
				if (*i != this && (*i)->getState() >= Module::STATE_ACTIVE && (*i)->getGroupID() == groupID_)
					maxGroupActive--;
			if (maxGroupActive < 0)
				canHaveState = false;
		}
	}
	return canHaveState;
}

Module::State Module::getState()
{
	return state_;
}

void Module::setState(State state)
{
	if (canHaveState(state))
	{
		if (state < state_)
		{
			if (state_ >= STATE_OVERLOADED && state < STATE_OVERLOADED)
				removeEffects(Effect::CATEGORY_OVERLOADED);
			if (state_ >= STATE_ACTIVE && state < STATE_ACTIVE)
			{
				removeEffects(Effect::CATEGORY_ACTIVE);
				removeEffects(Effect::CATEGORY_TARGET);
			}
			if (state_ >= STATE_ONLINE && state < STATE_ONLINE)
			{
				removeEffects(Effect::CATEGORY_PASSIVE);
				getEffect(ONLINE_EFFECT_ID)->removeEffect(getEnvironment());
			}
		}
		else if (state > state_)
		{
			if (state_ < STATE_ONLINE && state >= STATE_ONLINE)
			{
				addEffects(Effect::CATEGORY_PASSIVE);
				getEffect(ONLINE_EFFECT_ID)->addEffect(getEnvironment());
			}
			if (state_ < STATE_ACTIVE && state >= STATE_ACTIVE)
			{
				addEffects(Effect::CATEGORY_ACTIVE);
				addEffects(Effect::CATEGORY_TARGET);
			}
			if (state_ < STATE_OVERLOADED && state >= STATE_OVERLOADED)
				addEffects(Effect::CATEGORY_OVERLOADED);
		}
		state_ = state;
		engine_->reset(this);
	}
}

Environment Module::getEnvironment()
{
	Environment environment;
	environment["Self"] = this;
	Item* ship = getOwner();
	Item* character = ship ? ship->getOwner() : NULL;
	Item* gang = character ? character->getOwner() : NULL;
	
	if (character)
		environment["Char"] = character;
	if (ship)
		environment["Ship"] = ship;
	if (gang)
		environment["Gang"] = gang;
	if (engine_->getArea())
		environment["Area"] = engine_->getArea();
	if (target_)
		environment["Target"] = target_;
	return environment;
}

void Module::addEffects(Effect::Category category)
{
	Environment environment = getEnvironment();
	
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getEffectID() != ONLINE_EFFECT_ID && (*i)->getCategory() == category)
			(*i)->addEffect(environment);
	
	if (category == Effect::CATEGORY_GENERIC)
	{
		if (state_ >= STATE_ONLINE)
		{
			addEffects(Effect::CATEGORY_PASSIVE);
			getEffect(ONLINE_EFFECT_ID)->addEffect(getEnvironment());
		}
		if (state_ >= STATE_ACTIVE)
		{
			addEffects(Effect::CATEGORY_ACTIVE);
			addEffects(Effect::CATEGORY_TARGET);
		}
		if (state_ >= STATE_OVERLOADED)
			addEffects(Effect::CATEGORY_OVERLOADED);
		
		if (charge_)
			charge_->addEffects(category);
	}
}

void Module::removeEffects(Effect::Category category)
{
	Environment environment = getEnvironment();

	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getEffectID() != ONLINE_EFFECT_ID && (*i)->getCategory() == category)
			(*i)->removeEffect(environment);
//	if (category == Effect::CATEGORY_GENERIC && charge_ != NULL)
//		charge_->removeEffects(category);
	if (category == Effect::CATEGORY_GENERIC)
	{
		if (state_ >= STATE_OVERLOADED)
			removeEffects(Effect::CATEGORY_OVERLOADED);
		if (state_ >= STATE_ACTIVE)
		{
			removeEffects(Effect::CATEGORY_ACTIVE);
			removeEffects(Effect::CATEGORY_TARGET);
		}
		if (state_ >= STATE_ONLINE)
		{
			removeEffects(Effect::CATEGORY_PASSIVE);
			getEffect(ONLINE_EFFECT_ID)->removeEffect(getEnvironment());
		}
		
		if (charge_)
			charge_->removeEffects(category);
	}
}

void Module::reset()
{
	Item::reset();
	shots_ = -1;
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
	lifeTime_ = -1;
	if (charge_)
		charge_->reset();
}

Charge* Module::setCharge(Charge* charge)
{
	if (charge)
	{
		if (canFit(charge))
		{
			if (charge_) {
				charge_->removeEffects(Effect::CATEGORY_GENERIC);
				delete charge_;
			}
			charge_ = charge;
			charge_->setOwner(this);
			charge_->addEffects(Effect::CATEGORY_GENERIC);
			engine_->reset(this);
		}
		else {
			delete charge;
			return NULL;
		}
	}
	else if (charge_) {
		charge_->removeEffects(Effect::CATEGORY_GENERIC);
		engine_->reset(this);
		delete charge_;
		charge_ = NULL;
	}
	return charge_;
}

Charge* Module::setCharge(TypeID typeID)
{
	try
	{
		return setCharge(new Charge(engine_, typeID, this));
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

void Module::clearCharge()
{
	if (charge_)
	{
		charge_->removeEffects(Effect::CATEGORY_GENERIC);
		delete charge_;
		charge_ = NULL;
		engine_->reset(this);
	}
}


Charge* Module::getCharge()
{
	return charge_;
}

const std::vector<TypeID>& Module::getChargeGroups()
{
	return chargeGroups_;
}

int Module::getChargeSize()
{
	if (hasAttribute(CHARGE_SIZE_ATTRIBUTE_ID))
		return static_cast<int>(getAttribute(CHARGE_SIZE_ATTRIBUTE_ID)->getValue());
	else
		return 0;
}

void Module::removeCharge()
{
	setCharge(0);
}

bool Module::canFit(Charge* charge)
{
	if (!charge)
		return true;
	if (charge->getAttribute(VOLUME_ATTRIBUTE_ID)->getValue() > getAttribute(CAPACITY_ATTRIBUTE_ID)->getValue())
		return false;
	
	int chargeSize = getChargeSize();
	if (chargeSize > 0)
	{
		if (!charge->hasAttribute(CHARGE_SIZE_ATTRIBUTE_ID) || static_cast<int>(charge->getAttribute(CHARGE_SIZE_ATTRIBUTE_ID)->getValue()) != chargeSize)
			return false;
	}
	
	TypeID chargeGroup = charge->getGroupID();
	
	std::vector<TypeID>::iterator i, end = chargeGroups_.end();
	for (i = chargeGroups_.begin(); i != end; i++)
		if (*i == chargeGroup)
			return true;
	return false;
}

bool Module::requireTarget()
{
	return requireTarget_;
}

void Module::setTarget(Ship* target)
{
	if (target == getOwner())
		throw BadTargetException() << BadTargetExceptionInfo(target);
	
	if (target_)
	{
		removeEffects(Effect::CATEGORY_TARGET);
		target_->removeProjectedModule(this);
	}
	target_ = target;
	if (target)
	{
		target->addProjectedModule(this);
		addEffects(Effect::CATEGORY_TARGET);
	}
}

void Module::clearTarget()
{
	setTarget(NULL);
}

Ship* Module::getTarget()
{
	return target_;
}

float Module::getReloadTime()
{
	if (hasAttribute(RELOAD_TIME_ATTRIBUTE_ID))
		return getAttribute(RELOAD_TIME_ATTRIBUTE_ID)->getValue();
	else
		return reloadTime_;
}

//Calculations

float Module::getCycleTime()
{
	float reactivation = hasAttribute(MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID) ? getAttribute(MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID)->getValue() : 0;
	float speed = getRawCycleTime() + reactivation;
	
	bool factorReload = forceReload_;
#ifdef FACTOR_RELOAD
	factorReload = true;
#endif
	float reload = charge_ ? getReloadTime() : 0;
	if (factorReload && reactivation < reload)
	{
		float additionalReloadTime = (reload - reactivation);
		float numShots = static_cast<float>(getShots());
		speed = numShots > 0 ? (speed * numShots + additionalReloadTime) / numShots : speed;
	}
	return speed;
}

float Module::getRawCycleTime()
{
	if (hasAttribute(SPEED_ATTRIBUTE_ID))
		return getAttribute(SPEED_ATTRIBUTE_ID)->getValue();
	else if (hasAttribute(DURATION_ATTRIBUTE_ID))
		return getAttribute(DURATION_ATTRIBUTE_ID)->getValue();
	else if (hasAttribute(MISSILE_LAUNCH_DURATION_ATTRIBUTE_ID))
		return getAttribute(MISSILE_LAUNCH_DURATION_ATTRIBUTE_ID)->getValue();
	else
		return 0;
}

int Module::getCharges()
{
	if (!charge_)
		return 0;
	
	float chargeVolume = charge_->getAttribute(VOLUME_ATTRIBUTE_ID)->getValue();
	float containerCapacity = getAttribute(CAPACITY_ATTRIBUTE_ID)->getValue();
	if (!chargeVolume || !containerCapacity)
		return 0;
	return static_cast<int>(containerCapacity / chargeVolume);
}

int Module::getShots()
{
	if (!charge_)
		return 0;
	if (shots_ < 0)
	{
		int charges = getCharges();
		if (charges > 0 && hasAttribute(CHARGE_RATE_ATTRIBUTE_ID))
		{
			float chargeRate = getAttribute(CHARGE_RATE_ATTRIBUTE_ID)->getValue();
			shots_ = static_cast<int>(getCharges() / chargeRate);
		}
		else if (charges > 0 && hasAttribute(CRYSTALS_GET_DAMAGED_ATTRIBUTE_ID))
		{
			float hp = charge_->getAttribute(HP_ATTRIBUTE_ID)->getValue();
			float chance = charge_->getAttribute(CRYSTAL_VOLATILITY_CHANCE_ATTRIBUTE_ID)->getValue();
			float damage = charge_->getAttribute(CRYSTAL_VOLATILITY_DAMAGE_ATTRIBUTE_ID)->getValue();
			shots_ = static_cast<int>(getCharges() * hp / (damage * chance));
		}
		else
			shots_ = 0;
	}
	return shots_;
}

float Module::getCapUse()
{
	if (state_ >= STATE_ACTIVE)
	{
		float capNeed = 0.0;
		if (hasAttribute(CAPACITOR_NEED_ATTRIBUTE_ID))
			capNeed = getAttribute(CAPACITOR_NEED_ATTRIBUTE_ID)->getValue();
		if (capNeed == 0.0 && hasEffect(LEECH_EFFECT_ID))
			capNeed = -getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID)->getValue();
		if (capNeed == 0.0 && hasEffect(POWER_BOOSTER_EFFECT_ID) && charge_)
			capNeed = -charge_->getAttribute(CAPACITOR_BONUS_ATTRIBUTE_ID)->getValue();
		
		if (capNeed != 0.0)
		{
			float cycleTime = getCycleTime();
			return cycleTime != 0.0f ? capNeed / (cycleTime / 1000.0f) : 0.0f;
		}
		else
			return 0.0f;
		return capNeed;
	}
	else
		return 0.0f;
}

float Module::getVolley()
{
	if (volley_ < 0)
		calculateDamageStats();
	return volley_;
}

float Module::getDps()
{
	if (dps_ < 0)
		calculateDamageStats();
	return dps_;
}

float Module::getMaxRange()
{
	if (maxRange_ < 0)
	{
		TypeID attributes[] = {
			MAX_RANGE_ATTRIBUTE_ID, SHIELD_TRANSFER_RANGE_ATTRIBUTE_ID, POWER_TRANSFER_RANGE_ATTRIBUTE_ID, ENERGY_DESTABILIZATION_RANGE_ATTRIBUTE_ID,
			EMP_FIELD_RANGE_ATTRIBUTE_ID, ECM_BURST_RANGE_ATTRIBUTE_ID, WARP_SCRAMBLE_RANGE_ATTRIBUTE_ID, CARGO_SCAN_RANGE_ATTRIBUTE_ID,
			SHIP_SCAN_RANGE_ATTRIBUTE_ID, SURVEY_SCAN_RANGE_ATTRIBUTE_ID};
		for (int i = 0; i < 10; i++)
			if (hasAttribute(attributes[i]))
			{
				maxRange_ = getAttribute(attributes[i])->getValue();
				return maxRange_;
			}
		
		if (charge_)
		{
			if (charge_->hasAttribute(MAX_VELOCITY_ATTRIBUTE_ID) && charge_->hasAttribute(EXPLOSION_DELAY_ATTRIBUTE_ID) &&
				charge_->hasAttribute(MASS_ATTRIBUTE_ID) && charge_->hasAttribute(AGILITY_ATTRIBUTE_ID))
			{
				float missileEntityVelocityMultiplier = 1;
				float missileEntityFlightTimeMultiplier = 1;
				if (hasAttribute(MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID))
					missileEntityVelocityMultiplier = getAttribute(MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(MISSILE_ENTITY_FLIGHT_TIME_MULTIPLIER_ATTRIBUTE_ID))
					missileEntityFlightTimeMultiplier = getAttribute(MISSILE_ENTITY_FLIGHT_TIME_MULTIPLIER_ATTRIBUTE_ID)->getValue();
				if (missileEntityVelocityMultiplier == 0)
					missileEntityVelocityMultiplier = 1.0;
				if (missileEntityFlightTimeMultiplier == 0)
					missileEntityFlightTimeMultiplier = 1.0;
				
				float maxVelocity = charge_->getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue() * missileEntityVelocityMultiplier;
				float flightTime = charge_->getAttribute(EXPLOSION_DELAY_ATTRIBUTE_ID)->getValue() / 1000.0f * missileEntityFlightTimeMultiplier;
				float mass = charge_->getAttribute(MASS_ATTRIBUTE_ID)->getValue();
				float agility = charge_->getAttribute(AGILITY_ATTRIBUTE_ID)->getValue();
				
				float accelTime = std::min(flightTime, static_cast<float>(mass * agility / 1000000.0f));
				float duringAcceleration = maxVelocity / 2 * accelTime;
				float fullSpeed = maxVelocity * (flightTime - accelTime);
				maxRange_ =  duringAcceleration + fullSpeed;
			}
			else
				maxRange_ = 0;
		}
		else
			maxRange_ = 0;
	}
	return maxRange_;
}

float Module::getFalloff()
{
	if (falloff_ < 0)
	{
		if (hasAttribute(FALLOFF_ATTRIBUTE_ID))
			falloff_ = getAttribute(FALLOFF_ATTRIBUTE_ID)->getValue();
		else if (hasAttribute(SHIP_SCAN_RANGE_ATTRIBUTE_ID))
			falloff_ = getAttribute(SHIP_SCAN_RANGE_ATTRIBUTE_ID)->getValue();
		else
			falloff_ = 0;
	}
	return falloff_;
}

float Module::getTrackingSpeed()
{
	if (trackingSpeed_ < 0)
	{
		if (hasAttribute(TRACKING_SPEED_ATTRIBUTE_ID))
			trackingSpeed_ = getAttribute(TRACKING_SPEED_ATTRIBUTE_ID)->getValue();
		else
			trackingSpeed_ = 0;
	}
	return trackingSpeed_;
}

float Module::getLifeTime()
{
	if (lifeTime_ < 0)
	{
		Ship* ship = dynamic_cast<Ship*>(getOwner());
		ship->updateHeatDamage();
	}
	return lifeTime_;
}

void Module::setLifeTime(float lifeTime)
{
	lifeTime_ = lifeTime;
}

void Module::calculateDamageStats()
{
	if (state_ < STATE_ACTIVE)
		dps_ = volley_ = 0;
	else
	{
		volley_ = 0;
		dps_ = 0;
		Item* item = charge_ ? static_cast<Item*>(charge_) : static_cast<Item*>(this);
		if (item->hasAttribute(EM_DAMAGE_ATTRIBUTE_ID))
			volley_ += item->getAttribute(EM_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (item->hasAttribute(KINETIC_DAMAGE_ATTRIBUTE_ID))
			volley_ += item->getAttribute(KINETIC_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (item->hasAttribute(EXPLOSIVE_DAMAGE_ATTRIBUTE_ID))
			volley_ += item->getAttribute(EXPLOSIVE_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (item->hasAttribute(THERMAL_DAMAGE_ATTRIBUTE_ID))
			volley_ += item->getAttribute(THERMAL_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (hasAttribute(DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
			volley_ *= getAttribute(DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();
		else if (hasAttribute(MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
			volley_ *= getAttribute(MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();

		float speed = getCycleTime();
		if (speed > 0)
			dps_ = volley_ / (speed / 1000.0f);
	}
}

#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Module& module)
{
	os << "{\"typeName\":\"" << module.getTypeName() << "\", \"typeID\":\"" << module.typeID_ << "\", \"groupID\":\"" << module.groupID_ << "\", \"attributes\":[";
	
	if (module.attributes_.size() > 0)
	{
		AttributesMap::const_iterator i, end = module.attributes_.end();
		bool isFirst = true;
		for (i = module.attributes_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i->second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (module.effects_.size() > 0)
	{
		EffectsList::const_iterator i, end = module.effects_.end();
		bool isFirst = true;
		for (i = module.effects_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "],";
	
	if (module.charge_)
		os << "\"charge\":" << *module.charge_ << ",";

	os << "\"itemModifiers\":[";
	
	if (module.itemModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = module.itemModifiers_.end();
		bool isFirst = true;
		for (i = module.itemModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (module.locationModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = module.locationModifiers_.end();
		bool isFirst = true;
		for (i = module.locationModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (module.locationGroupModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = module.locationGroupModifiers_.end();
		bool isFirst = true;
		for (i = module.locationGroupModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>(*i);
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (module.locationRequiredSkillModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = module.locationRequiredSkillModifiers_.end();
		bool isFirst = true;
		for (i = module.locationRequiredSkillModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>(*i);
		}
	}
	
	os << "]}";
	return os;
}

#endif