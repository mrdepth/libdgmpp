#include "Drone.h"
#include "Ship.h"
#include "Effect.h"
#include "Attribute.h"
#include "Engine.h"
#include "Area.h"
#include "Charge.h"
#include <cmath>
#include <algorithm>

using namespace dgmpp;

Drone::Drone(std::shared_ptr<Engine> const& engine, TypeID typeID, int squadronTag, std::shared_ptr<Ship> const& owner) : Item(engine, typeID, owner), isActive_(true), target_(), charge_(nullptr), squadronTag_(squadronTag)
{
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = miningYield_ = -1;
}

Drone::~Drone(void)
{
}


void Drone::setTarget(std::shared_ptr<Ship> const& target)
{
	loadIfNeeded();
	std::shared_ptr<Ship> oldTarget = target_.lock();
	if (oldTarget == target)
		return;
	
	if (target && target == getOwner())
		throw BadDroneTargetException("self");

	if (oldTarget) {
		removeEffects(Effect::Category::target);
		oldTarget->removeProjectedDrone(shared_from_this());
	}
	target_ = target;
	if (target) {
		target->addProjectedDrone(shared_from_this());
		addEffects(Effect::Category::target);
	}
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

void Drone::clearTarget()
{
	setTarget(nullptr);
}

std::shared_ptr<Ship> Drone::getTarget()
{
	return target_.lock();
}

bool Drone::dealsDamage()
{
	loadIfNeeded();
	if (!isActive_)
		return false;
	
	bool hasDamageAttribute =	hasAttribute(AttributeID::emDamage) ||
								hasAttribute(AttributeID::explosiveDamage) ||
								hasAttribute(AttributeID::kineticDamage) ||
								hasAttribute(AttributeID::thermalDamage) ||
								hasAttribute(AttributeID::fighterAbilityMissilesDamageMultiplier) ||
								hasAttribute(AttributeID::fighterAbilityAttackMissileDamageMultiplier) ||
								hasAttribute(AttributeID::fighterAbilityAttackTurretDamageMultiplier);
	if (hasDamageAttribute)
		return hasDamageAttribute;
	
	bool chargeHasDamageAttribute = charge_ ?	charge_->hasAttribute(AttributeID::emDamage) ||
												charge_->hasAttribute(AttributeID::explosiveDamage) ||
												charge_->hasAttribute(AttributeID::kineticDamage) ||
												charge_->hasAttribute(AttributeID::thermalDamage) : false;
	return chargeHasDamageAttribute;
}

std::shared_ptr<Charge> Drone::getCharge()
{
	loadIfNeeded();
	return charge_;
}

void Drone::setActive(bool active)
{
	if (isActive_ == active)
		return;
	
	if (!isActive_ && active)
	{
		addEffects(Effect::Category::generic);
		addEffects(Effect::Category::target);
	}
	else if (isActive_ && !active)
	{
		removeEffects(Effect::Category::generic);
		removeEffects(Effect::Category::target);
	}
	isActive_ = active;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

bool Drone::isActive()
{
	loadIfNeeded();
	return isActive_;
}

bool Drone::isAssistance() {
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::Category::target)
			return  effect->isAssistance();
	auto charge = getCharge();
	if (charge)
		return charge->isAssistance();
	return false;
}

bool Drone::isOffensive() {
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::Category::target)
			return effect->isOffensive();
	auto charge = getCharge();
	if (charge)
		return charge->isOffensive();
	return false;
}

void Drone::addEffects(Effect::Category category)
{
	loadIfNeeded();
	Item::addEffects(category);
	if (category == Effect::Category::generic && charge_)
		charge_->addEffects(category);
}

void Drone::removeEffects(Effect::Category category)
{
	loadIfNeeded();
	Item::removeEffects(category);
	if (category == Effect::Category::generic && charge_)
		charge_->removeEffects(category);
}

void Drone::reset() {
	Item::reset();
	dps_ = volley_ = maxRange_ = falloff_ = trackingSpeed_ = miningYield_ = -1;
	if (charge_)
		charge_->reset();
}

Drone::FighterSquadron Drone::getSquadron() {
	loadIfNeeded();
	return squadron_;
}

int Drone::getSquadronSize() {
	return getAttribute(AttributeID::fighterSquadronMaxSize)->getValue();
}

int Drone::getSquadronTag() {
	return squadronTag_;
}

void Drone::setSquadronTag(int squadronTag) {
	squadronTag_ = squadronTag;
	auto engine = getEngine();
	if (engine)
		engine->reset();
}

//Calculations

Float Drone::getCycleTime()
{
	if (hasAttribute(AttributeID::speed))
		return getAttribute(AttributeID::speed)->getValue() / 1000.0;
	else if (hasAttribute(AttributeID::duration))
		return getAttribute(AttributeID::duration)->getValue() / 1000.0;
	else
		return 0;
}

DamageVector Drone::getVolley()
{
	loadIfNeeded();
	if (volley_ < 0)
		calculateDamageStats();
	return volley_;
}

DamageVector Drone::getDps(const HostileTarget& target)
{
	loadIfNeeded();
	if (dps_ < 0)
		calculateDamageStats();
	
	if (dps_ > 0  && target.signature > 0) {
		Float range = getAttribute(AttributeID::entityFlyRange)->getValue();
		Float orbitVelocity = getAttribute(AttributeID::entityCruiseSpeed)->getValue();
		if (range == 0)
			range = getAttribute(AttributeID::fighterSquadronOrbitRange)->getValue();
		if (orbitVelocity == 0)
			orbitVelocity = getAttribute(AttributeID::maxVelocity)->getValue();
		
		if (target.velocity > 0) {
			Float velocity = getAttribute(AttributeID::maxVelocity)->getValue();
			
			if (velocity < target.velocity)
				return 0;
			
			Float v = std::sqrt(velocity * velocity - target.velocity * target.velocity);
			orbitVelocity = std::min(orbitVelocity, v);
		}
		
		Float angularVelocity = range > 0 ? orbitVelocity / range : 0;
		
		Float a = 0;
		if (angularVelocity > 0) {
			Float accuracyScore = getAccuracyScore();
			a = accuracyScore > 0 ? angularVelocity / accuracyScore : 0;
		}
		
		Float signatureResolution = getAttribute(AttributeID::optimalSigRadius)->getValue();
		if (signatureResolution > 0)
			a *= signatureResolution / target.signature;
		
		Float b = 0;
		if (target.range > 0) {
			Float maxRange = getMaxRange();
			Float falloff = getFalloff();
			b = falloff > 0 ? std::max(0.0, (range - maxRange) / falloff) : 0;
			
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
	
	return dps_;
}

Float Drone::getMaxRange()
{
	loadIfNeeded();
	if (maxRange_ < 0)
	{
		
		AttributeID attributes[] = {
			AttributeID::shieldTransferRange,
			AttributeID::powerTransferRange,
			AttributeID::energyNeutralizerRangeOptimal,
			AttributeID::empFieldRange,
			AttributeID::ecmBurstRange,
			AttributeID::maxRange,
			AttributeID::fighterAbilityAttackMissileRangeOptimal,
			AttributeID::fighterAbilityAttackTurretRangeOptimal,
			AttributeID::fighterAbilityECMRangeOptimal,
			AttributeID::fighterAbilityEnergyNeutralizerOptimalRange,
			AttributeID::fighterAbilityStasisWebifierOptimalRange,
			AttributeID::fighterAbilityWarpDisruptionRange};
		
		for (auto attributeID: attributes) {
			if (hasAttribute(attributeID))
			{
				maxRange_ = getAttribute(attributeID)->getValue();
				return maxRange_;
			}
		}
		
		if (charge_)
		{
			if (charge_->hasAttribute(AttributeID::maxVelocity) && charge_->hasAttribute(AttributeID::explosionDelay))
			{
				Float maxVelocity = charge_->getAttribute(AttributeID::maxVelocity)->getValue();
				Float flightTime = charge_->getAttribute(AttributeID::explosionDelay)->getValue() / 1000.0;
				maxRange_ = flightTime / 1000.0 * maxVelocity;
			}
			else
				maxRange_ = 0;
		}
		else
			maxRange_ = 0;
	}
	return maxRange_;
}

Float Drone::getFalloff()
{
	loadIfNeeded();
	if (falloff_ < 0)
	{
		AttributeID attributes[] = {
			AttributeID::falloff,
			AttributeID::fighterAbilityAttackMissileRangeFalloff,
			AttributeID::fighterAbilityAttackTurretRangeFalloff,
			AttributeID::fighterAbilityECMRangeFalloff,
			AttributeID::fighterAbilityEnergyNeutralizerFalloffRange,
			AttributeID::fighterAbilityStasisWebifierFalloffRange};
		
		for (auto attributeID: attributes) {
			if (hasAttribute(attributeID))
			{
				falloff_ = getAttribute(attributeID)->getValue();
				return falloff_;
			}
		}
		falloff_ = 0;
	}
	return falloff_;
}

Float Drone::getAccuracyScore()
{
	loadIfNeeded();
	if (trackingSpeed_ < 0)
	{
		if (hasAttribute(AttributeID::trackingSpeed))
			trackingSpeed_ = getAttribute(AttributeID::trackingSpeed)->getValue();
		else
			trackingSpeed_ = 0;
	}
	return trackingSpeed_;
}

Float Drone::getMiningYield()
{
	if (miningYield_ < 0)
	{
		miningYield_ = 0;
		if (isActive_)
		{
			Float volley = 0;
			if (hasAttribute(AttributeID::miningAmount))
				volley += getAttribute(AttributeID::miningAmount)->getValue();
			if (hasAttribute(AttributeID::specialtyMiningAmount))
				volley += getAttribute(AttributeID::specialtyMiningAmount)->getValue();
			
			Float cycleTime = getCycleTime();
			if (volley > 0 && cycleTime > 0)
			{
				miningYield_ = volley / cycleTime;
			}
		}
	}
	return miningYield_;
}

Float Drone::getVelocity()
{
	return getAttribute(AttributeID::maxVelocity)->getValue();
}

void Drone::calculateDamageStats()
{
	loadIfNeeded();
	if (!dealsDamage() || !isActive_)
		dps_ = volley_ = 0;
	else
	{
		volley_ = 0;
		dps_ = 0;
		Float cycleTime = getCycleTime();
		if (cycleTime > 0) {
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
			dps_ = volley_ / getCycleTime();
		}
		
		if (hasAttribute(AttributeID::fighterAbilityAttackMissileDuration)) {
			DamageVector fighterMissileVolley = 0;
			Float cycleTime = getAttribute(AttributeID::fighterAbilityAttackMissileDuration)->getValue();
			if (cycleTime > 0) {
				if (hasAttribute(AttributeID::fighterAbilityAttackMissileDamageEM))
					fighterMissileVolley.emAmount += getAttribute(AttributeID::fighterAbilityAttackMissileDamageEM)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackMissileDamageKin))
					fighterMissileVolley.kineticAmount += getAttribute(AttributeID::fighterAbilityAttackMissileDamageKin)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackMissileDamageExp))
					fighterMissileVolley.explosiveAmount += getAttribute(AttributeID::fighterAbilityAttackMissileDamageExp)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackMissileDamageTherm))
					fighterMissileVolley.thermalAmount += getAttribute(AttributeID::fighterAbilityAttackMissileDamageTherm)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackMissileDamageMultiplier))
					fighterMissileVolley *= getAttribute(AttributeID::fighterAbilityAttackMissileDamageMultiplier)->getValue();
				dps_ += fighterMissileVolley / (cycleTime / 1000);
				volley_ += fighterMissileVolley;
			}
		}
		
		if (hasAttribute(AttributeID::fighterAbilityMissilesDuration)) {
			DamageVector fighterMissilesVolley = 0;
			Float cycleTime = getAttribute(AttributeID::fighterAbilityMissilesDuration)->getValue();
			if (cycleTime > 0) {
				if (hasAttribute(AttributeID::fighterAbilityMissilesDamageEM))
					fighterMissilesVolley.emAmount += getAttribute(AttributeID::fighterAbilityMissilesDamageEM)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityMissilesDamageKin))
					fighterMissilesVolley.kineticAmount += getAttribute(AttributeID::fighterAbilityMissilesDamageKin)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityMissilesDamageExp))
					fighterMissilesVolley.explosiveAmount += getAttribute(AttributeID::fighterAbilityMissilesDamageExp)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityMissilesDamageTherm))
					fighterMissilesVolley.thermalAmount += getAttribute(AttributeID::fighterAbilityMissilesDamageTherm)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityMissilesDamageMultiplier))
					fighterMissilesVolley *= getAttribute(AttributeID::fighterAbilityMissilesDamageMultiplier)->getValue();
				dps_ += fighterMissilesVolley / (cycleTime / 1000);
				volley_ += fighterMissilesVolley;
			}
		}
		
		if (hasAttribute(AttributeID::fighterAbilityAttackTurretDuration)) {
			DamageVector fighterTurretVolley = 0;
			Float cycleTime = getAttribute(AttributeID::fighterAbilityAttackTurretDuration)->getValue();
			if (cycleTime > 0) {
				if (hasAttribute(AttributeID::fighterAbilityAttackTurretDamageEM))
					fighterTurretVolley.emAmount += getAttribute(AttributeID::fighterAbilityAttackTurretDamageEM)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackTurretDamageKin))
					fighterTurretVolley.kineticAmount += getAttribute(AttributeID::fighterAbilityAttackTurretDamageKin)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackTurretDamageExp))
					fighterTurretVolley.explosiveAmount += getAttribute(AttributeID::fighterAbilityAttackTurretDamageExp)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackTurretDamageTherm))
					fighterTurretVolley.thermalAmount += getAttribute(AttributeID::fighterAbilityAttackTurretDamageTherm)->getValue();
				if (hasAttribute(AttributeID::fighterAbilityAttackTurretDamageMultiplier))
					fighterTurretVolley *= getAttribute(AttributeID::fighterAbilityAttackTurretDamageMultiplier)->getValue();
				dps_ += fighterTurretVolley / (cycleTime / 1000);
				volley_ += fighterTurretVolley;
			}
		}
	}
}

void Drone::lazyLoad() {
	Item::lazyLoad();
	auto engine = getEngine();
	if (!engine)
		return;
	
	if (hasAttribute(AttributeID::entityMissileTypeID))
	{
		TypeID typeID = static_cast<TypeID>(getAttribute(AttributeID::entityMissileTypeID)->getValue());
		charge_ = std::make_shared<Charge>(engine, typeID, shared_from_this());
		//charge_->addEffects(Effect::Category::generic);
	}
	
	if (hasAttribute(AttributeID::fighterSquadronIsHeavy))
		squadron_ = Drone::FighterSquadron::heavy;
	else if (hasAttribute(AttributeID::fighterSquadronIsLight))
		squadron_ = Drone::FighterSquadron::light;
	else if (hasAttribute(AttributeID::fighterSquadronIsSupport))
		squadron_ = Drone::FighterSquadron::support;
	else
		squadron_ = Drone::FighterSquadron::none;
}

Item* Drone::ship() {
	return getOwner().get();
}

Item* Drone::character() {
	return ship()->character();
}

Item* Drone::target() {
	return getTarget().get();
}

std::insert_iterator<ModifiersList> Drone::getModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	if (typeID_ == TypeID::none)
		return outIterator;
	
	auto i = itemModifiers_.find(attribute->getAttributeID());
	if (i != itemModifiers_.end()) {
		outIterator = std::copy(i->second.begin(), i->second.end(), outIterator);
	}
	auto owner = getOwner();
	if (owner)
	{
		owner = owner->getOwner();
		if (owner) {
			outIterator = owner->getLocationModifiers(attribute, outIterator);
			outIterator = owner->getModifiersMatchingItem(this, attribute, outIterator);
		}
	}
	return outIterator;
}
