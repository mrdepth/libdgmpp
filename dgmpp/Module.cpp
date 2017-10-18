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
#include <cmath>

using namespace dgmpp;

Module::Module(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner) : Item(engine, typeID, owner), state_(STATE_OFFLINE), preferredState_(STATE_UNKNOWN), target_(), reloadTime_(0), forceReload_(false), charge_(nullptr), slot_(SLOT_UNKNOWN), enabled_(true), factorReload_(false), socket_(0)
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

int Module::getSocket() {
	std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(getOwner());
	auto modules = ship->getModules(getSlot(), true);
	return static_cast<int>(std::find(modules.begin(), modules.end(), shared_from_this()) - modules.begin());
}

bool Module::canHaveState(State state)
{
	if (isDummy())
		return false;
	
	loadIfNeeded();
	if (isEnabled()) {
		auto charge = getCharge();
		bool canBeActive = canBeActive_ | (charge ? charge->canBeActive() : false);
		bool canHaveState =	 state == STATE_OFFLINE ||
		(state == STATE_ONLINE && canBeOnline_) ||
		(state == STATE_ACTIVE && canBeActive) ||
		(state == STATE_OVERLOADED && canBeOverloaded_);
		if (canHaveState && state >= STATE_ACTIVE)
		{
			if (getAttribute(ACTIVATION_BLOCKED_ATTRIBUTE_ID)->getValue() > 0)
				return false;
			
			std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(getOwner());
			
			if (hasAttribute(MAX_GROUP_ACTIVE_ATTRIBUTE_ID))
			{
				int maxGroupActive = static_cast<int>(getAttribute(MAX_GROUP_ACTIVE_ATTRIBUTE_ID)->getValue()) - 1;
				
				for (const auto& i: ship->getModules())
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
	if (isDummy())
		return STATE_UNKNOWN;
	loadIfNeeded();
	return isEnabled() ? state_ : STATE_OFFLINE;
}

void Module::setInternalState(State state)
{
	if (isDummy())
		return;
	if (state == state_)
		return;
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
				getEffect(ONLINE_EFFECT_ID)->removeEffect(this);
			}
		}
		else if (state > state_)
		{
			if (state_ < STATE_ONLINE && state >= STATE_ONLINE)
			{
				addEffects(Effect::CATEGORY_PASSIVE);
				getEffect(ONLINE_EFFECT_ID)->addEffect(this);
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
			engine->reset();
	}
}

Module::State Module::getPreferredState() {
	if (isDummy())
		return STATE_UNKNOWN;
	return preferredState_;
}

void Module::setState(State state) {
	if (isDummy())
		return;
	preferredState_ = state;
	setInternalState(state);
}

bool Module::isAssistance() {
	if (isDummy())
		return false;
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::CATEGORY_TARGET)
			return  effect->isAssistance();
	auto charge = getCharge();
	if (charge)
		return charge->isAssistance();
	return false;
}

bool Module::isOffensive() {
	if (isDummy())
		return false;
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::CATEGORY_TARGET)
			return  effect->isOffensive();
	auto charge = getCharge();
	if (charge)
		return charge->isOffensive();
	return false;
}

void Module::addEffects(Effect::Category category)
{
	if (isDummy())
		return;
	loadIfNeeded();
	
	for (const auto& i: effects_)
		if (i->getEffectID() != ONLINE_EFFECT_ID && i->getCategory() == category)
			i->addEffect(this);
	
	if (category == Effect::CATEGORY_GENERIC)
	{
		if (state_ >= STATE_ONLINE)
		{
			addEffects(Effect::CATEGORY_PASSIVE);
			getEffect(ONLINE_EFFECT_ID)->addEffect(this);
		}
		if (state_ >= STATE_ACTIVE)
		{
			addEffects(Effect::CATEGORY_ACTIVE);
			addEffects(Effect::CATEGORY_TARGET);
		}
		if (state_ >= STATE_OVERLOADED)
			addEffects(Effect::CATEGORY_OVERLOADED);
		
	}
	if (charge_)
		charge_->addEffects(category);
}

void Module::removeEffects(Effect::Category category)
{
	if (isDummy())
		return;
	loadIfNeeded();

	for (const auto& i: effects_)
		if (i->getEffectID() != ONLINE_EFFECT_ID && i->getCategory() == category)
			i->removeEffect(this);
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
			getEffect(ONLINE_EFFECT_ID)->removeEffect(this);
		}
		
	}
	if (charge_)
		charge_->removeEffects(category);
}

void Module::reset()
{
	Item::reset();
	shots_ = -1;
	dps_ = volley_ = maxRange_ = falloff_ = accuracyScore_ = signatureResolution_ = miningYield_ = -1;
	lifeTime_ = -1;
	if (charge_)
		charge_->reset();
}

std::shared_ptr<Charge> Module::setCharge(TypeID typeID)
{
	if (isDummy())
		return nullptr;
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
		
		engine->reset();
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
	if (isDummy())
		return 0;
	if (hasAttribute(CHARGE_SIZE_ATTRIBUTE_ID))
		return static_cast<int>(getAttribute(CHARGE_SIZE_ATTRIBUTE_ID)->getValue());
	else
		return 0;
}

bool Module::canFit(std::shared_ptr<Charge> const& charge)
{
	if (isDummy())
		return false;
	loadIfNeeded();
	if (!charge)
		return true;
	Float capacity = getAttribute(CAPACITY_ATTRIBUTE_ID)->getValue();
	if (capacity > 0 && charge->getAttribute(VOLUME_ATTRIBUTE_ID)->getValue() > capacity)
		return false;
	
	int chargeSize = getChargeSize();
	if (chargeSize > 0)
	{
		if (!charge->hasAttribute(CHARGE_SIZE_ATTRIBUTE_ID) || static_cast<int>(charge->getAttribute(CHARGE_SIZE_ATTRIBUTE_ID)->getValue()) != chargeSize)
			return false;
	}
	
	TypeID chargeGroup = charge->getGroupID();
	
	for (const auto& i: chargeGroups_)
		if (i == chargeGroup)
			return true;
	return false;
}

bool Module::requireTarget()
{
	if (isDummy())
		return false;
	for (const auto& i: effects_)
	{
		Effect::Category category = i->getCategory();
		if (category == Effect::CATEGORY_TARGET)
			return true;
	}
	if (charge_)
		for (const auto& i: charge_->getEffects()) {
			Effect::Category category = i->getCategory();
			if (category == Effect::CATEGORY_TARGET)
				return true;
			
		}
	return false;
}

void Module::setTarget(std::shared_ptr<Ship> const& target)
{
	if (isDummy())
		return;
	loadIfNeeded();
	std::shared_ptr<Ship> oldTarget = target_.lock();
	if (oldTarget == target)
		return;

	if (target && target == getOwner())
		throw BadTargetException("self");
	
	
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
		engine->reset();
}

void Module::clearTarget()
{
	setTarget(nullptr);
}

std::shared_ptr<Ship> Module::getTarget()
{
	return target_.lock();
}

Float Module::getReloadTime()
{
	if (isDummy())
		return 0;
	if (hasAttribute(RELOAD_TIME_ATTRIBUTE_ID))
		return getAttribute(RELOAD_TIME_ATTRIBUTE_ID)->getValue() / 1000.0;
	else
		return reloadTime_;
}

//Calculations

Float Module::getCycleTime()
{
	if (isDummy())
		return 0;
	Float reactivation = hasAttribute(MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID) ? getAttribute(MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID)->getValue()  / 1000.0: 0;
	Float speed = getRawCycleTime();
	
	bool factorReload = forceReload_ || factorReload_;
	Float reload = charge_ ? getReloadTime() : 0;
	if (factorReload && reload > 0)
	{
//		Float additionalReloadTime = (reload - reactivation);
		Float numShots = static_cast<Float>(getShots());
		speed = numShots > 0 ? (speed * numShots + std::max(reload, reactivation)) / numShots : speed;
	}
	return speed;
}

Float Module::getRawCycleTime()
{
	if (isDummy())
		return 0;
	Float speed = 0;
	if (hasAttribute(SPEED_ATTRIBUTE_ID))
		speed = getAttribute(SPEED_ATTRIBUTE_ID)->getValue();
	else if (hasAttribute(DURATION_ATTRIBUTE_ID))
		speed = getAttribute(DURATION_ATTRIBUTE_ID)->getValue();
	else if (hasAttribute(MISSILE_LAUNCH_DURATION_ATTRIBUTE_ID))
		speed = getAttribute(MISSILE_LAUNCH_DURATION_ATTRIBUTE_ID)->getValue();
	return speed / 1000.0;
}

bool Module::factorReload() {
	return factorReload_;
}

void Module::setFactorReload(bool factorReload) {
	factorReload_ = factorReload;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

int Module::getCharges()
{
	if (isDummy())
		return 0;
	if (!charge_)
		return 0;
	
	Float chargeVolume = charge_->getAttribute(VOLUME_ATTRIBUTE_ID)->getValue();
	Float containerCapacity = getAttribute(CAPACITY_ATTRIBUTE_ID)->getValue();
	if (!chargeVolume || !containerCapacity)
		return 0;
	return static_cast<int>(containerCapacity / chargeVolume);
}

int Module::getShots()
{
	if (isDummy())
		return 0;
	loadIfNeeded();
	if (!charge_)
		return 0;
	if (shots_ < 0)
	{
		int charges = getCharges();
		if (charges > 0 && hasAttribute(CHARGE_RATE_ATTRIBUTE_ID))
		{
			Float chargeRate = getAttribute(CHARGE_RATE_ATTRIBUTE_ID)->getValue();
			shots_ = static_cast<int>(getCharges() / chargeRate);
		}
		else if (charges > 0 && hasAttribute(CRYSTALS_GET_DAMAGED_ATTRIBUTE_ID))
		{
			Float hp = charge_->getAttribute(HP_ATTRIBUTE_ID)->getValue();
			Float chance = charge_->getAttribute(CRYSTAL_VOLATILITY_CHANCE_ATTRIBUTE_ID)->getValue();
			Float damage = charge_->getAttribute(CRYSTAL_VOLATILITY_DAMAGE_ATTRIBUTE_ID)->getValue();
			shots_ = static_cast<int>(getCharges() * hp / (damage * chance));
		}
		else
			shots_ = 0;
	}
	return shots_;
}

Float Module::getCapUse()
{
	if (isDummy())
		return 0;
	loadIfNeeded();
	if (state_ >= STATE_ACTIVE)
	{
		Float capNeed = 0.0;
		if (hasAttribute(CAPACITOR_NEED_ATTRIBUTE_ID))
			capNeed = getAttribute(CAPACITOR_NEED_ATTRIBUTE_ID)->getValue();
		if (capNeed == 0.0 && hasEffect(ENERGY_NOSFERATU_FALLOFF))
			capNeed = -getAttribute(POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID)->getValue();
		if (capNeed == 0.0 && hasEffect(POWER_BOOSTER_EFFECT_ID) && charge_)
			capNeed = -charge_->getAttribute(CAPACITOR_BONUS_ATTRIBUTE_ID)->getValue();
		
		if (capNeed != 0.0)
		{
			Float cycleTime = getCycleTime();
			return cycleTime != 0.0 ? capNeed / cycleTime : 0.0;
		}
		else
			return 0.0;
		return capNeed;
	}
	else
		return 0.0;
}

Float Module::getCpuUse() {
	if (isDummy())
		return 0;
	loadIfNeeded();
	return getAttribute(CPU_ATTRIBUTE_ID)->getValue();
}

Float Module::getPowerGridUse() {
	if (isDummy())
		return 0;
	loadIfNeeded();
	return getAttribute(POWER_ATTRIBUTE_ID)->getValue();
}

Float Module::getCalibrationUse() {
	if (isDummy())
		return 0;
	loadIfNeeded();
	return getAttribute(UPGRADE_COST_ATTRIBUTE_ID)->getValue();
}


DamageVector Module::getVolley()
{
	if (isDummy())
		return DamageVector();
	loadIfNeeded();
	if (volley_ < 0)
		calculateDamageStats();
	return volley_;
}

DamageVector Module::getDps(const HostileTarget& target)
{
	if (isDummy())
		return DamageVector();
	loadIfNeeded();
	if (dps_ < 0)
		calculateDamageStats();
	auto hardpoint = getHardpoint();
	if (hardpoint == HARDPOINT_TURRET && (target.range > 0 || target.angularVelocity > 0 || target.signature > 0)) {
		Float a = 0;
		if (target.angularVelocity > 0) {
			Float accuracyScore = getAccuracyScore();
			a = accuracyScore > 0 ? target.angularVelocity / accuracyScore : 0;
		}
		
		if (target.signature > 0) {
			Float signatureResolution = getSignatureResolution();
			if (signatureResolution > 0)
				a *= signatureResolution / target.signature;
		}

		Float b = 0;
		if (target.range > 0) {
			Float maxRange = getMaxRange();
			Float falloff = getFalloff();
			b = falloff > 0 ? std::max(0.0, (target.range - maxRange) / falloff) : 0;
		}
		
		Float blob = a * a + b * b;
		Float hitChance = std::pow(0.5, blob);
		Float relativeDPS;
		if (hitChance > 0.01)
			relativeDPS = (hitChance - 0.01) * (0.5 + (hitChance + 0.49)) / 2 + 0.01 * 3;
		else
			relativeDPS = hitChance * 3;
		return dps_ * relativeDPS;
	}
	else if (hardpoint == HARDPOINT_LAUNCHER) {
		auto charge = getCharge();
		if (charge) {
			if (target.range > getMaxRange())
				return 0;
			if (target.velocity > 0) {
				Float missileEntityVelocityMultiplier = 1;
				if (hasAttribute(MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID))
					missileEntityVelocityMultiplier = getAttribute(MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID)->getValue();
				Float maxVelocity = charge_->getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue() * missileEntityVelocityMultiplier;
				if (maxVelocity < target.velocity)
					return 0;
			}
			
			Float a = 1;
			if (target.signature > 0) {
				Float e = charge->getAttribute(AOE_CLOUD_SIZE_ATTRIBUTE_ID)->getValue();
				a = target.signature / e;
			}
			Float b = 1;
			if (target.velocity > 0) {
				Float v = charge->getAttribute(AOE_VELOCITY_ATTRIBUTE_ID)->getValue();
				Float drf = charge->getAttribute(AOE_DAMAGE_REDUCTION_FACTOR_ATTRIBUTE_ID)->getValue();
				Float drs = charge->getAttribute(AOE_DAMAGE_REDUCTION_SENSITIVITY_ATTRIBUTE_ID)->getValue();
				if (drf > 0 && drs > 0 && v > 0)
					b = std::pow(a * v / target.velocity, std::log(drf)/std::log(drs));
			}
			Float relativeDPS = std::min(1.0, std::min(a, b));
			return dps_ * relativeDPS;
		}
	}
	else if (dps_ > 0) {
		Float maxRange = getMaxRange();
		if (maxRange < target.range)
			return 0;
	}
	return dps_;
}

Float Module::getMaxRange()
{
	if (isDummy())
		return 0;
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
				Float missileEntityVelocityMultiplier = 1;
				Float missileEntityFlightTimeMultiplier = 1;
				if (hasAttribute(MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID))
					missileEntityVelocityMultiplier = getAttribute(MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(MISSILE_ENTITY_FLIGHT_TIME_MULTIPLIER_ATTRIBUTE_ID))
					missileEntityFlightTimeMultiplier = getAttribute(MISSILE_ENTITY_FLIGHT_TIME_MULTIPLIER_ATTRIBUTE_ID)->getValue();
				if (missileEntityVelocityMultiplier == 0)
					missileEntityVelocityMultiplier = 1.0;
				if (missileEntityFlightTimeMultiplier == 0)
					missileEntityFlightTimeMultiplier = 1.0;
				
				Float maxVelocity = charge_->getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue() * missileEntityVelocityMultiplier;
				Float flightTime = charge_->getAttribute(EXPLOSION_DELAY_ATTRIBUTE_ID)->getValue() / 1000.0 * missileEntityFlightTimeMultiplier;
				Float mass = charge_->getAttribute(MASS_ATTRIBUTE_ID)->getValue();
				Float agility = charge_->getAttribute(AGILITY_ATTRIBUTE_ID)->getValue();
				
				Float accelTime = std::min(flightTime, static_cast<Float>(mass * agility / 1000000.0));
				Float duringAcceleration = maxVelocity / 2 * accelTime;
				Float fullSpeed = maxVelocity * (flightTime - accelTime);
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

Float Module::getFalloff()
{
	if (isDummy())
		return 0;
	loadIfNeeded();
	if (falloff_ < 0)
	{
		if (hasAttribute(FALLOFF_ATTRIBUTE_ID))
			falloff_ = getAttribute(FALLOFF_ATTRIBUTE_ID)->getValue();
		else if (hasAttribute(SHIP_SCAN_FALLOFF_ATTRIBUTE_ID))
			falloff_ = getAttribute(SHIP_SCAN_FALLOFF_ATTRIBUTE_ID)->getValue();
		else if (hasAttribute(FALLOFF_EFFECTIVENESS_ATTRIBUTE_ID))
			falloff_ = getAttribute(FALLOFF_EFFECTIVENESS_ATTRIBUTE_ID)->getValue();
		else
			falloff_ = 0;
	}
	return falloff_;
}

/*Float Module::getTrackingSpeed()
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
}*/

Float Module::getAccuracyScore()
{
	if (isDummy())
		return 0;
	loadIfNeeded();
	if (accuracyScore_ < 0)
	{
		if (hasAttribute(TRACKING_SPEED_ATTRIBUTE_ID))
			accuracyScore_ = getAttribute(TRACKING_SPEED_ATTRIBUTE_ID)->getValue();
		else
			accuracyScore_ = 0;
	}
	return accuracyScore_;
}

Float Module::getSignatureResolution() {
	if (isDummy())
		return 0;
	loadIfNeeded();
	if (signatureResolution_ < 0)
	{
		if (hasAttribute(OPTIMAL_SIG_RADIUS_ATTRIBUTE_ID))
			signatureResolution_ = getAttribute(OPTIMAL_SIG_RADIUS_ATTRIBUTE_ID)->getValue();
		else
			signatureResolution_ = 0;
	}
	return signatureResolution_;
}

Float Module::getAngularVelocity(Float targetSignature, Float hitChance) {
	if (isDummy())
		return 0;
	Float signatureResolution = getSignatureResolution();
	Float accuracyScore = getAccuracyScore();
	
	Float v = std::sqrt(std::log(hitChance) / std::log(0.5)) * accuracyScore * targetSignature / signatureResolution;
	return v;
}

Float Module::getMiningYield()
{
	if (isDummy())
		return 0;
	if (miningYield_ < 0)
	{
		miningYield_ = 0;
		if (state_ >= STATE_ACTIVE)
		{
			Float volley = 0;
			if (hasAttribute(SPECIALTY_MINING_AMOUNT_ATTRIBUTE_ID))
				volley += getAttribute(SPECIALTY_MINING_AMOUNT_ATTRIBUTE_ID)->getValue();
			else if (hasAttribute(MINING_AMOUNT_ATTRIBUTE_ID))
				volley += getAttribute(MINING_AMOUNT_ATTRIBUTE_ID)->getValue();
			
			Float cycleTime = getCycleTime();
			if (volley > 0 && cycleTime > 0)
			{
				miningYield_ = volley / cycleTime;
			}
		}
	}
	return miningYield_;
}

Float Module::getLifeTime()
{
	if (isDummy())
		return 0;
	loadIfNeeded();
	if (lifeTime_ < 0)
	{
		std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(getOwner());
		ship->updateHeatDamage();
	}
	return lifeTime_;
}

void Module::setLifeTime(Float lifeTime)
{
	lifeTime_ = lifeTime;
}

void Module::setEnabled(bool enabled) {
	enabled_ = enabled;
}

bool Module::isEnabled() {
	if (isDummy())
		return false;
	return enabled_;
}

void Module::calculateDamageStats()
{
	if (isDummy())
		return;
	loadIfNeeded();
	if (state_ < STATE_ACTIVE)
		dps_ = volley_ = 0;
	else
	{
		volley_ = 0;
		dps_ = 0;
		std::shared_ptr<Item> item = charge_ ? charge_  : std::static_pointer_cast<Item>(shared_from_this());
		if (item->hasAttribute(EM_DAMAGE_ATTRIBUTE_ID))
			volley_.emAmount += item->getAttribute(EM_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (item->hasAttribute(KINETIC_DAMAGE_ATTRIBUTE_ID))
			volley_.kineticAmount += item->getAttribute(KINETIC_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (item->hasAttribute(EXPLOSIVE_DAMAGE_ATTRIBUTE_ID))
			volley_.explosiveAmount += item->getAttribute(EXPLOSIVE_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (item->hasAttribute(THERMAL_DAMAGE_ATTRIBUTE_ID))
			volley_.thermalAmount += item->getAttribute(THERMAL_DAMAGE_ATTRIBUTE_ID)->getValue();
		if (hasAttribute(DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
			volley_ *= getAttribute(DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();
		else if (hasAttribute(MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
			volley_ *= getAttribute(MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();

		Float speed = getCycleTime();
		if (speed > 0)
			dps_ = volley_ / speed;
	}
}

void Module::lazyLoad() {
	Item::lazyLoad();
	if (isDummy())
		return;
	addExtraAttribute(IS_ONLINE_ATTRIBUTE_ID, 0.0);
	
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
	else if (getCategoryID() == STARBASE_CATEGORY_ID)
		slot_ = SLOT_STARBASE_STRUCTURE;
	else if (hasEffect(SERVICE_SLOT_EFFECT_ID))
		slot_ = SLOT_SERVICE;
	else
		slot_ = SLOT_NONE;
	
	if (hasAttribute(RELOAD_TIME_ATTRIBUTE_ID))
		reloadTime_ = getAttribute(RELOAD_TIME_ATTRIBUTE_ID)->getValue() / 1000.0;
	else
	{
		if (hasEffect(MINING_LASER_EFFECT_ID) || hasEffect(TARGET_ATTACK_EFFECT_ID) || hasEffect(USE_MISSILES_EFFECT_ID))
			reloadTime_ = 1.0;
		else if (hasEffect(POWER_BOOSTER_EFFECT_ID) || hasEffect(PROJECTILE_FIRED_EFFECT_ID))
			reloadTime_ = 10.0;
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
	
	for (const auto& i: effects_)
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
	dps_ = volley_ = maxRange_ = falloff_ = accuracyScore_ = signatureResolution_ = miningYield_ = -1;
	
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

Item* Module::ship() {
	return getOwner().get();
}

Item* Module::character() {
	return ship()->character();
}

Item* Module::target() {
	return getTarget().get();
}


std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Module& module)
{
	os << "{\"typeName\":\"" << module.getTypeName() << "\", \"typeID\":\"" << module.typeID_ << "\", \"groupID\":\"" << module.groupID_ << "\", \"attributes\":[";
	
	if (module.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: module.attributes_)
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
		for (const auto& i: module.effects_)
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
		for (const auto& list: module.itemModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (module.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: module.locationModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (module.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: module.locationGroupModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (module.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: module.locationRequiredSkillModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}
	
	os << "]}";
	return os;
}
