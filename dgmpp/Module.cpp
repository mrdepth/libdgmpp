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

Module::Module(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner) : Item(engine, typeID, owner), state_(State::offline), preferredState_(State::unknown), target_(), reloadTime_(0), forceReload_(false), charge_(nullptr), slot_(Slot::unknown), enabled_(true), factorReload_(false), socket_(0)
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
		bool canHaveState =	 state == State::offline ||
		(state == State::online && canBeOnline_) ||
		(state == State::active && canBeActive) ||
		(state == State::overloaded && canBeOverloaded_);
		if (canHaveState && state >= State::active)
		{
			if (getAttribute(AttributeID::activationBlocked)->getValue() > 0)
				return false;
			
			std::shared_ptr<Ship> ship = std::dynamic_pointer_cast<Ship>(getOwner());
			
			if (hasAttribute(AttributeID::maxGroupActive))
			{
				int maxGroupActive = static_cast<int>(getAttribute(AttributeID::maxGroupActive)->getValue()) - 1;
				
				for (const auto& i: ship->getModules())
					if (i.get() != this && i->getState() >= Module::State::active && i->getGroupID() == groupID_)
						maxGroupActive--;
				if (maxGroupActive < 0)
					canHaveState = false;
			}
		}
		return canHaveState;
	}
	else
		return state == State::offline;
}

Module::State Module::getState()
{
	if (isDummy())
		return State::unknown;
	loadIfNeeded();
	return isEnabled() ? state_ : State::offline;
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
			if (state_ >= State::overloaded && state < State::overloaded)
				removeEffects(Effect::Category::overloaded);
			if (state_ >= State::active && state < State::active)
			{
				removeEffects(Effect::Category::active);
				removeEffects(Effect::Category::target);
			}
			if (state_ >= State::online && state < State::online)
			{
				removeEffects(Effect::Category::passive);
				getEffect(EffectID::online)->removeEffect(this);
			}
		}
		else if (state > state_)
		{
			if (state_ < State::online && state >= State::online)
			{
				addEffects(Effect::Category::passive);
				getEffect(EffectID::online)->addEffect(this);
			}
			if (state_ < State::active && state >= State::active)
			{
				addEffects(Effect::Category::active);
				addEffects(Effect::Category::target);
			}
			if (state_ < State::overloaded && state >= State::overloaded)
				addEffects(Effect::Category::overloaded);
		}
		state_ = state;
		auto engine = getEngine();
		if (engine)
			engine->reset();
	}
}

Module::State Module::getPreferredState() {
	if (isDummy())
		return State::unknown;
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
		if (effect->getCategory() == Effect::Category::target)
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
		if (effect->getCategory() == Effect::Category::target)
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
		if (i->getEffectID() != EffectID::online && i->getCategory() == category)
			i->addEffect(this);
	
	if (category == Effect::Category::generic)
	{
		if (state_ >= State::online)
		{
			addEffects(Effect::Category::passive);
			getEffect(EffectID::online)->addEffect(this);
		}
		if (state_ >= State::active)
		{
			addEffects(Effect::Category::active);
			addEffects(Effect::Category::target);
		}
		if (state_ >= State::overloaded)
			addEffects(Effect::Category::overloaded);
		
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
		if (i->getEffectID() != EffectID::online && i->getCategory() == category)
			i->removeEffect(this);
//	if (category == Effect::Category::generic && charge_ != nullptr)
//		charge_->removeEffects(category);
	if (category == Effect::Category::generic)
	{
		if (state_ >= State::overloaded)
			removeEffects(Effect::Category::overloaded);
		if (state_ >= State::active)
		{
			removeEffects(Effect::Category::active);
			removeEffects(Effect::Category::target);
		}
		if (state_ >= State::online)
		{
			removeEffects(Effect::Category::passive);
			getEffect(EffectID::online)->removeEffect(this);
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
		
		if (typeID != TypeID::none) {
			std::shared_ptr<Charge> charge = std::make_shared<Charge>(engine, typeID, shared_from_this());
			if (charge && canFit(charge))
			{
				if (charge_)
					charge_->removeEffects(Effect::Category::generic);
				
				charge_ = charge;
				charge_->addEffects(Effect::Category::generic);
			}
		}
		else {
			if (charge_) {
				charge_->removeEffects(Effect::Category::generic);
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
	setCharge(TypeID::none);
}


std::shared_ptr<Charge> Module::getCharge()
{
	return charge_;
}

const std::vector<GroupID>& Module::getChargeGroups()
{
	loadIfNeeded();
	return chargeGroups_;
}

int Module::getChargeSize()
{
	if (isDummy())
		return 0;
	if (hasAttribute(AttributeID::chargeSize))
		return static_cast<int>(getAttribute(AttributeID::chargeSize)->getValue());
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
	Float capacity = getAttribute(AttributeID::capacity)->getValue();
	if (capacity > 0 && charge->getAttribute(AttributeID::volume)->getValue() > capacity)
		return false;
	
	int chargeSize = getChargeSize();
	if (chargeSize > 0)
	{
		if (!charge->hasAttribute(AttributeID::chargeSize) || static_cast<int>(charge->getAttribute(AttributeID::chargeSize)->getValue()) != chargeSize)
			return false;
	}
	
	GroupID chargeGroup = charge->getGroupID();
	
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
		if (category == Effect::Category::target)
			return true;
	}
	if (charge_)
		for (const auto& i: charge_->getEffects()) {
			Effect::Category category = i->getCategory();
			if (category == Effect::Category::target)
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
		removeEffects(Effect::Category::target);
		oldTarget->removeProjectedModule(shared_from_this());
	}
	target_ = target;
	if (target)
	{
		target->addProjectedModule(shared_from_this());
		addEffects(Effect::Category::target);
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
	if (hasAttribute(AttributeID::reloadTime))
		return getAttribute(AttributeID::reloadTime)->getValue() / 1000.0;
	else
		return reloadTime_;
}

//Calculations

Float Module::getCycleTime()
{
	if (isDummy())
		return 0;
	Float reactivation = hasAttribute(AttributeID::moduleReactivationDelay) ? getAttribute(AttributeID::moduleReactivationDelay)->getValue()  / 1000.0: 0;
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
	if (hasAttribute(AttributeID::speed))
		speed = getAttribute(AttributeID::speed)->getValue();
	else if (hasAttribute(AttributeID::duration))
		speed = getAttribute(AttributeID::duration)->getValue();
	else if (hasAttribute(AttributeID::missileLaunchDuration))
		speed = getAttribute(AttributeID::missileLaunchDuration)->getValue();
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
	
	Float chargeVolume = charge_->getAttribute(AttributeID::volume)->getValue();
	Float containerCapacity = getAttribute(AttributeID::capacity)->getValue();
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
		if (charges > 0 && hasAttribute(AttributeID::chargeRate))
		{
			Float chargeRate = getAttribute(AttributeID::chargeRate)->getValue();
			shots_ = static_cast<int>(getCharges() / chargeRate);
		}
		else if (charges > 0 && hasAttribute(AttributeID::crystalsGetDamaged))
		{
			Float hp = charge_->getAttribute(AttributeID::hp)->getValue();
			Float chance = charge_->getAttribute(AttributeID::crystalVolatilityChance)->getValue();
			Float damage = charge_->getAttribute(AttributeID::crystalVolatilityDamage)->getValue();
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
	if (state_ >= State::active)
	{
		Float capNeed = 0.0;
		
		if (hasAttribute(AttributeID::capacitorNeed))
			capNeed = getAttribute(AttributeID::capacitorNeed)->getValue();
		if (capNeed == 0.0 && hasEffect(EffectID::energyNosferatuFalloff))
			capNeed = -getAttribute(AttributeID::powerTransferAmount)->getValue();
		if (capNeed == 0.0 && hasEffect(EffectID::powerBooster) && charge_)
			capNeed = -charge_->getAttribute(AttributeID::capacitorBonus)->getValue();
		
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
	return getAttribute(AttributeID::cpu)->getValue();
}

Float Module::getPowerGridUse() {
	if (isDummy())
		return 0;
	loadIfNeeded();
	return getAttribute(AttributeID::power)->getValue();
}

Float Module::getCalibrationUse() {
	if (isDummy())
		return 0;
	loadIfNeeded();
	return getAttribute(AttributeID::upgradeCost)->getValue();
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
	if (hardpoint == Module::Hardpoint::turret && (target.range > 0 || target.angularVelocity > 0 || target.signature > 0)) {
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
	else if (hardpoint == Module::Hardpoint::launcher) {
		auto charge = getCharge();
		if (charge) {
			if (target.range > getMaxRange())
				return 0;
			if (target.velocity > 0) {
				Float missileEntityVelocityMultiplier = 1;
				
				if (hasAttribute(AttributeID::missileEntityVelocityMultiplier))
					missileEntityVelocityMultiplier = getAttribute(AttributeID::missileEntityVelocityMultiplier)->getValue();
				Float maxVelocity = charge_->getAttribute(AttributeID::maxVelocity)->getValue() * missileEntityVelocityMultiplier;
				if (maxVelocity < target.velocity)
					return 0;
			}
			
			Float a = 1;
			if (target.signature > 0) {
				Float e = charge->getAttribute(AttributeID::aoeCloudSize)->getValue();
				a = target.signature / e;
			}
			Float b = 1;
			if (target.velocity > 0) {
				Float v = charge->getAttribute(AttributeID::aoeVelocity)->getValue();
				Float drf = charge->getAttribute(AttributeID::aoeDamageReductionFactor)->getValue();
				Float drs = charge->getAttribute(AttributeID::aoeDamageReductionSensitivity)->getValue();
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
		AttributeID attributes[] = {
			AttributeID::maxRange, AttributeID::shieldTransferRange, AttributeID::powerTransferRange, AttributeID::energyNeutralizerRangeOptimal,
			AttributeID::empFieldRange, AttributeID::ecmBurstRange, AttributeID::warpScrambleRange, AttributeID::cargoScanRange,
			AttributeID::shipScanRange, AttributeID::surveyScanRange};
		for (int i = 0; i < 10; i++)
			if (hasAttribute(attributes[i]))
			{
				maxRange_ = getAttribute(attributes[i])->getValue();
				return maxRange_;
			}
		
		if (charge_)
		{
			if (charge_->hasAttribute(AttributeID::maxVelocity) && charge_->hasAttribute(AttributeID::explosionDelay) &&
				charge_->hasAttribute(AttributeID::mass) && charge_->hasAttribute(AttributeID::agility))
			{
				Float missileEntityVelocityMultiplier = 1;
				Float missileEntityFlightTimeMultiplier = 1;
				if (hasAttribute(AttributeID::missileEntityVelocityMultiplier))
					missileEntityVelocityMultiplier = getAttribute(AttributeID::missileEntityVelocityMultiplier)->getValue();
				if (hasAttribute(AttributeID::missileEntityFlightTimeMultiplier))
					missileEntityFlightTimeMultiplier = getAttribute(AttributeID::missileEntityFlightTimeMultiplier)->getValue();
				if (missileEntityVelocityMultiplier == 0)
					missileEntityVelocityMultiplier = 1.0;
				if (missileEntityFlightTimeMultiplier == 0)
					missileEntityFlightTimeMultiplier = 1.0;
				
				Float maxVelocity = charge_->getAttribute(AttributeID::maxVelocity)->getValue() * missileEntityVelocityMultiplier;
				Float flightTime = charge_->getAttribute(AttributeID::explosionDelay)->getValue() / 1000.0 * missileEntityFlightTimeMultiplier;
				Float mass = charge_->getAttribute(AttributeID::mass)->getValue();
				Float agility = charge_->getAttribute(AttributeID::agility)->getValue();
				
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
		if (hasAttribute(AttributeID::falloff))
			falloff_ = getAttribute(AttributeID::falloff)->getValue();
		else if (hasAttribute(AttributeID::shipScanFalloff))
			falloff_ = getAttribute(AttributeID::shipScanFalloff)->getValue();
		else if (hasAttribute(AttributeID::falloffEffectiveness))
			falloff_ = getAttribute(AttributeID::falloffEffectiveness)->getValue();
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
		if (hasAttribute(AttributeID::trackingSpeed))
			accuracyScore_ = getAttribute(AttributeID::trackingSpeed)->getValue();
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
		if (hasAttribute(AttributeID::optimalSigRadius))
			signatureResolution_ = getAttribute(AttributeID::optimalSigRadius)->getValue();
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
		if (state_ >= State::active)
		{
			Float volley = 0;
			if (hasAttribute(AttributeID::specialtyMiningAmount))
				volley += getAttribute(AttributeID::specialtyMiningAmount)->getValue();
			else if (hasAttribute(AttributeID::miningAmount))
				volley += getAttribute(AttributeID::miningAmount)->getValue();
			
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
	if (state_ < State::active)
		dps_ = volley_ = 0;
	else
	{
		volley_ = 0;
		dps_ = 0;
		std::shared_ptr<Item> item = charge_ ? charge_  : std::static_pointer_cast<Item>(shared_from_this());
		if (item->hasAttribute(AttributeID::emDamage))
			volley_.emAmount += item->getAttribute(AttributeID::emDamage)->getValue();
		if (item->hasAttribute(AttributeID::kineticDamage))
			volley_.kineticAmount += item->getAttribute(AttributeID::kineticDamage)->getValue();
		if (item->hasAttribute(AttributeID::explosiveDamage))
			volley_.explosiveAmount += item->getAttribute(AttributeID::explosiveDamage)->getValue();
		if (item->hasAttribute(AttributeID::thermalDamage))
			volley_.thermalAmount += item->getAttribute(AttributeID::thermalDamage)->getValue();
		if (hasAttribute(AttributeID::damageMultiplier))
			volley_ *= getAttribute(AttributeID::damageMultiplier)->getValue();
		else if (hasAttribute(AttributeID::missileDamageMultiplier))
			volley_ *= getAttribute(AttributeID::missileDamageMultiplier)->getValue();

		Float speed = getCycleTime();
		if (speed > 0)
			dps_ = volley_ / speed;
	}
}

void Module::lazyLoad() {
	Item::lazyLoad();
	if (isDummy())
		return;
	addExtraAttribute(AttributeID::isOnline, 0.0);
	
	if (hasEffect(EffectID::loPower))
		slot_ = Module::Slot::low;
	else if (hasEffect(EffectID::medPower))
		slot_ = Module::Slot::med;
	else if (hasEffect(EffectID::hiPower))
		slot_ = Module::Slot::hi;
	else if (hasEffect(EffectID::rigSlot))
		slot_ = Module::Slot::rig;
	else if (hasEffect(EffectID::subSystem))
		slot_ = Module::Slot::subsystem;
	else if (hasEffect(EffectID::tacticalMode))
		slot_ = Module::Slot::mode;
	else if (getCategoryID() == CategoryID::starbase)
		slot_ = Module::Slot::starbaseStructure;
	else if (hasEffect(EffectID::serviceSlot))
		slot_ = Module::Slot::service;
	else
		slot_ = Module::Slot::none;
	
	if (hasAttribute(AttributeID::reloadTime))
		reloadTime_ = getAttribute(AttributeID::reloadTime)->getValue() / 1000.0;
	else
	{
		if (hasEffect(EffectID::miningLaser) || hasEffect(EffectID::targetAttack) || hasEffect(EffectID::useMissiles))
			reloadTime_ = 1.0;
		else if (hasEffect(EffectID::powerBooster) || hasEffect(EffectID::projectileFired))
			reloadTime_ = 10.0;
	}
	
	if (hasEffect(EffectID::turretFitted))
		hardpoint_ = Module::Hardpoint::turret;
	else if (hasEffect(EffectID::launcherFitted))
		hardpoint_ = Module::Hardpoint::launcher;
	else
		hardpoint_ = Module::Hardpoint::none;
	
	canBeOnline_ = hasEffect(EffectID::online) || hasEffect(EffectID::onlineForStructures);
	
	state_ = State::offline;
	
	canBeActive_ = false;
	canBeOverloaded_ = false;
	int n = 0;
	
	for (const auto& i: effects_)
	{
		Effect::Category category = i->getCategory();
		if (category == Effect::Category::active)
		{
			n++;
			if (n >= 2)
			{
				canBeActive_ = true;
			}
		}
		else if (category == Effect::Category::target)
		{
			canBeActive_ = true;
		}
		else if (category == Effect::Category::overloaded)
		{
			canBeActive_ = true;
			canBeOverloaded_ = true;
		}
	}
	
	forceReload_ = groupID_ == GroupID::capacitorBooster;
	
	shots_ = -1;
	dps_ = volley_ = maxRange_ = falloff_ = accuracyScore_ = signatureResolution_ = miningYield_ = -1;
	
	AttributeID attributes[] = {AttributeID::chargeGroup1, AttributeID::chargeGroup2, AttributeID::chargeGroup3, AttributeID::chargeGroup4, AttributeID::chargeGroup5};
	for (int i = 0; i < 5; i++)
		if (hasAttribute(attributes[i]))
		{
			GroupID groupID = static_cast<GroupID>(getAttribute(attributes[i])->getValue());
			if (groupID != GroupID::none) {
				chargeGroups_.push_back(groupID);
				
				if (!forceReload_ && (groupID == GroupID::capacitorBoosterCharge || groupID == GroupID::naniteRepairPaste))
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
	os << "{\"typeName\":\"" << module.getTypeName() << "\", \"typeID\":\"" << static_cast<int>(module.typeID_) << "\", \"groupID\":\"" << static_cast<int>(module.groupID_) << "\", \"attributes\":[";
	
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
