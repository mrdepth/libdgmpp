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

Module::Module(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Item> owner) : Item(engine, typeID, owner), state_(STATE_OFFLINE), target_(), reloadTime_(0), forceReload_(false), charge_(nullptr), slot_(SLOT_UNKNOWN), enabled_(true)
{
}

Module::~Module(void)
{
}

/*Attribute* Module::getAttribute(TypeID attributeID)
{
	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return i->second;
	else
		return attributes_[attributeID] = new Attribute(engine_, attributeID, this);
}*/

Module::Slot Module::getSlot()
{
	loadIfNeeded();
	return slot_;
}

Module::Hardpoint Module::getHardpoint()
{
	loadIfNeeded();
	return hardpoint_;
}

bool Module::canHaveState(State state)
{
	loadIfNeeded();
	if (isEnabled()) {
		bool canHaveState =	 state == STATE_OFFLINE ||
		(state == STATE_ONLINE && canBeOnline_) ||
		(state == STATE_ACTIVE && canBeActive_) ||
		(state == STATE_OVERLOADED && canBeOverloaded_);
		if (canHaveState && state >= STATE_ACTIVE)
		{
			if (getAttribute(ACTIVATION_BLOCKED_ATTRIBUTE_ID)->getValue() > 0)
				return false;
			
			std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(getOwner());
			
			if (hasAttribute(MAX_GROUP_ACTIVE_ATTRIBUTE_ID))
			{
				int maxGroupActive = static_cast<int>(getAttribute(MAX_GROUP_ACTIVE_ATTRIBUTE_ID)->getValue()) - 1;
				
				for (auto i: ship->getModules())
					if (i.get() != this && i->getState() >= Module::STATE_ACTIVE && i->getGroupID() == groupID_)
						maxGroupActive--;
				if (maxGroupActive < 0)
					canHaveState = false;
			}
		}
		return canHaveState;
	}
	else
		return state == STATE_OFFLINE;
}

Module::State Module::getState()
{
	loadIfNeeded();
	return isEnabled() ? state_ : STATE_OFFLINE;
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
		auto engine = getEngine();
		if (engine)
			engine->reset(shared_from_this());
	}
}

Environment Module::getEnvironment()
{
	Environment environment;
	auto engine = getEngine();
	if (engine) {
		environment["Self"] = shared_from_this();
		std::shared_ptr<Item> ship = getOwner();
		std::shared_ptr<Item> character = ship ? ship->getOwner() : nullptr;
		std::shared_ptr<Item> gang = character ? character->getOwner() : nullptr;
		std::shared_ptr<Area> area = engine->getArea();
		std::shared_ptr<Item> target = target_.lock();
		
		if (character)
			environment["Char"] = character;
		if (ship)
			environment["Ship"] = ship;
		if (gang)
			environment["Gang"] = gang;
		if (area)
			environment["Area"] = area;
		if (target)
			environment["Target"] = target;
		
	}

	return environment;
}

void Module::addEffects(Effect::Category category)
{
	loadIfNeeded();
	Environment environment = getEnvironment();
	
	for (auto i: effects_)
		if (i->getEffectID() != ONLINE_EFFECT_ID && i->getCategory() == category)
			i->addEffect(environment);
	
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
	loadIfNeeded();
	Environment environment = getEnvironment();

	for (auto i: effects_)
		if (i->getEffectID() != ONLINE_EFFECT_ID && i->getCategory() == category)
			i->removeEffect(environment);
//	if (category == Effect::CATEGORY_GENERIC && charge_ != nullptr)
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

std::shared_ptr<Charge> Module::setCharge(TypeID typeID)
{
	loadIfNeeded();
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;
		
		if (typeID) {
			std::shared_ptr<Charge> charge = std::make_shared<Charge>(engine, typeID, shared_from_this());
			if (charge && canFit(charge))
			{
				if (charge_)
					charge_->removeEffects(Effect::CATEGORY_GENERIC);
				
				charge_ = charge;
				charge_->addEffects(Effect::CATEGORY_GENERIC);
			}
		}
		else {
			if (charge_) {
				charge_->removeEffects(Effect::CATEGORY_GENERIC);
				charge_ = nullptr;
			}
		}
		
		engine->reset(shared_from_this());
		return charge_;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void Module::clearCharge()
{
	setCharge(0);
}


std::shared_ptr<Charge> Module::getCharge()
{
	return charge_;
}

const std::vector<TypeID>& Module::getChargeGroups()
{
	loadIfNeeded();
	return chargeGroups_;
}

int Module::getChargeSize()
{
	if (hasAttribute(CHARGE_SIZE_ATTRIBUTE_ID))
		return static_cast<int>(getAttribute(CHARGE_SIZE_ATTRIBUTE_ID)->getValue());
	else
		return 0;
}

bool Module::canFit(std::shared_ptr<Charge> charge)
{
	loadIfNeeded();
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
	
	for (auto i: chargeGroups_)
		if (i == chargeGroup)
			return true;
	return false;
}

bool Module::requireTarget()
{
	for (auto i: effects_)
	{
		Effect::Category category = i->getCategory();
		if (category == Effect::CATEGORY_TARGET)
			return true;
	}
	if (charge_)
		for (auto i: charge_->getEffects()) {
			Effect::Category category = i->getCategory();
			if (category == Effect::CATEGORY_TARGET)
				return true;
			
		}
	return false;
}

void Module::setTarget(std::shared_ptr<Ship> target)
{
	loadIfNeeded();
	if (target && target == getOwner())
		throw BadTargetException("self");
	
	std::shared_ptr<Ship> oldTarget = target_.lock();
	if (oldTarget)
	{
		removeEffects(Effect::CATEGORY_TARGET);
		oldTarget->removeProjectedModule(shared_from_this());
	}
	target_ = target;
	if (target)
	{
		target->addProjectedModule(shared_from_this());
		addEffects(Effect::CATEGORY_TARGET);
	}
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
}

void Module::clearTarget()
{
	setTarget(nullptr);
}

std::shared_ptr<Ship> Module::getTarget()
{
	return target_.lock();
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
	loadIfNeeded();
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
	loadIfNeeded();
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
	loadIfNeeded();
	if (volley_ < 0)
		calculateDamageStats();
	return volley_;
}

float Module::getDps()
{
	loadIfNeeded();
	if (dps_ < 0)
		calculateDamageStats();
	return dps_;
}

float Module::getMaxRange()
{
	loadIfNeeded();
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
	loadIfNeeded();
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
	loadIfNeeded();
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
	loadIfNeeded();
	if (lifeTime_ < 0)
	{
		std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(getOwner());
		ship->updateHeatDamage();
	}
	return lifeTime_;
}

void Module::setLifeTime(float lifeTime)
{
	lifeTime_ = lifeTime;
}

void Module::setEnabled(bool enabled) {
	enabled_ = enabled;
}

bool Module::isEnabled() {
	return enabled_;
}

void Module::calculateDamageStats()
{
	loadIfNeeded();
	if (state_ < STATE_ACTIVE)
		dps_ = volley_ = 0;
	else
	{
		volley_ = 0;
		dps_ = 0;
		std::shared_ptr<Item> item = charge_ ?: std::static_pointer_cast<Item>(shared_from_this());
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

void Module::lazyLoad() {
	Item::lazyLoad();
	addExtraAttribute(IS_ONLINE_ATTRIBUTE_ID, 0, 0.0, true, true, "isOnline");
	
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
	else if (hasEffect(TACTICAL_MODE_EFFECT_ID))
		slot_ = SLOT_MODE;
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
	int n = 0;
	
	for (auto i: effects_)
	{
		Effect::Category category = i->getCategory();
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

std::ostream& eufe::operator<<(std::ostream& os, eufe::Module& module)
{
	os << "{\"typeName\":\"" << module.getTypeName() << "\", \"typeID\":\"" << module.typeID_ << "\", \"groupID\":\"" << module.groupID_ << "\", \"attributes\":[";
	
	if (module.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: module.attributes_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i.second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (module.effects_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: module.effects_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "],";
	
	if (module.charge_)
		os << "\"charge\":" << *module.charge_ << ",";

	os << "\"itemModifiers\":[";
	
	if (module.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: module.itemModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (module.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: module.locationModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (module.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: module.locationGroupModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationGroupModifier>(i);
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (module.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: module.locationRequiredSkillModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationRequiredSkillModifier>(i);
		}
	}
	
	os << "]}";
	return os;
}