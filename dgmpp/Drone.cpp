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

Drone::Drone(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Ship> const& owner) : Item(engine, typeID, owner), isActive_(true), target_(), charge_(nullptr)
{
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
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
		removeEffects(Effect::CATEGORY_TARGET);
		oldTarget->removeProjectedDrone(shared_from_this());
	}
	target_ = target;
	if (target) {
		target->addProjectedDrone(shared_from_this());
		addEffects(Effect::CATEGORY_TARGET);
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
	
	bool hasDamageAttribute =	hasAttribute(EM_DAMAGE_ATTRIBUTE_ID) ||
								hasAttribute(EXPLOSIVE_DAMAGE_ATTRIBUTE_ID) ||
								hasAttribute(KINETIC_DAMAGE_ATTRIBUTE_ID) ||
								hasAttribute(THERMAL_DAMAGE_ATTRIBUTE_ID) ||
								hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_MULTIPLIER_ATTRIBUTE_ID) ||
								hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID) ||
								hasAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_MULTIPLIER_ATTRIBUTE_ID);
	if (hasDamageAttribute)
		return hasDamageAttribute;
	
	bool chargeHasDamageAttribute = charge_ ?	charge_->hasAttribute(EM_DAMAGE_ATTRIBUTE_ID) ||
												charge_->hasAttribute(EXPLOSIVE_DAMAGE_ATTRIBUTE_ID) ||
												charge_->hasAttribute(KINETIC_DAMAGE_ATTRIBUTE_ID) ||
												charge_->hasAttribute(THERMAL_DAMAGE_ATTRIBUTE_ID) : false;
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
		addEffects(Effect::CATEGORY_GENERIC);
		addEffects(Effect::CATEGORY_TARGET);
	}
	else if (isActive_ && !active)
	{
		removeEffects(Effect::CATEGORY_GENERIC);
		removeEffects(Effect::CATEGORY_TARGET);
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
		if (effect->getCategory() == Effect::CATEGORY_TARGET)
			return  effect->isAssistance();
	auto charge = getCharge();
	if (charge)
		return charge->isAssistance();
	return false;
}

bool Drone::isOffensive() {
	for (const auto& effect: getEffects())
		if (effect->getCategory() == Effect::CATEGORY_TARGET)
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
	if (category == Effect::CATEGORY_GENERIC && charge_)
		charge_->addEffects(category);
}

void Drone::removeEffects(Effect::Category category)
{
	loadIfNeeded();
	Item::removeEffects(category);
	if (category == Effect::CATEGORY_GENERIC && charge_)
		charge_->removeEffects(category);
}

void Drone::reset() {
	Item::reset();
	dps_ = volley_ = maxRange_ = falloff_ = trackingSpeed_ = -1;
	if (charge_)
		charge_->reset();
}

Drone::FighterSquadron Drone::getSquadron() {
	loadIfNeeded();
	return squadron_;
}

int Drone::getSquadronSize() {
	int size = getAttribute(FIGHTER_SQUADRON_MAX_SIZE_ATTRIBUTE_ID)->getValue();
	if (size > 0)
		return size;
	else
		return 1;
}


//Calculations

float Drone::getCycleTime()
{
	if (hasAttribute(SPEED_ATTRIBUTE_ID))
		return getAttribute(SPEED_ATTRIBUTE_ID)->getValue();
	else if (hasAttribute(DURATION_ATTRIBUTE_ID))
		return getAttribute(DURATION_ATTRIBUTE_ID)->getValue();
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
		float range = getAttribute(ENTITY_FLY_RANGE_ATTRIBUTE_ID)->getValue();
		float orbitVelocity = getAttribute(ENTITY_CRUISE_SPEED_ATTRIBUTE_ID)->getValue();
		if (range == 0)
			range = getAttribute(FIGHTER_SQUADRON_ORBIT_RANGE_ATTRIBUTE_ID)->getValue();
		if (orbitVelocity == 0)
			orbitVelocity = getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue();
		
		if (target.velocity > 0) {
			float velocity = getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue();
			
			if (velocity < target.velocity)
				return 0;
			
			float v = sqrtf(velocity * velocity - target.velocity * target.velocity);
			orbitVelocity = std::min(orbitVelocity, v);
		}
		
		float angularVelocity = range > 0 ? orbitVelocity / range : 0;
		
		float a = 0;
		if (angularVelocity > 0) {
			float trackingSpeed = getTrackingSpeed();
			a = trackingSpeed > 0 ? angularVelocity / trackingSpeed : 0;
		}
		
		float signatureResolution = getAttribute(OPTIMAL_SIG_RADIUS_ATTRIBUTE_ID)->getValue();
		if (signatureResolution > 0)
			a *= signatureResolution / target.signature;
		
		float b = 0;
		if (target.range > 0) {
			float maxRange = getMaxRange();
			float falloff = getFalloff();
			b = falloff > 0 ? std::max(0.0f, (range - maxRange) / falloff) : 0;
			
		}
		
		float blob = a * a + b * b;
		float hitChance = std::pow(0.5f, blob);
		float relativeDPS;
		if (hitChance > 0.01)
			relativeDPS = (hitChance - 0.01) * (0.5 + (hitChance + 0.49)) / 2 + 0.01 * 3;
		else
			relativeDPS = hitChance * 3;
		return dps_ * relativeDPS;
	}
	
	return dps_;
}

float Drone::getMaxRange()
{
	loadIfNeeded();
	if (maxRange_ < 0)
	{
		TypeID attributes[] = {SHIELD_TRANSFER_RANGE_ATTRIBUTE_ID, POWER_TRANSFER_RANGE_ATTRIBUTE_ID, ENERGY_DESTABILIZATION_RANGE_ATTRIBUTE_ID,
			EMP_FIELD_RANGE_ATTRIBUTE_ID, ECM_BURST_RANGE_ATTRIBUTE_ID, MAX_RANGE_ATTRIBUTE_ID};
		
		for (int i = 0; i < 10; i++)
			if (hasAttribute(attributes[i]))
			{
				maxRange_ = getAttribute(attributes[i])->getValue();
				return maxRange_;
			}
		
		if (charge_)
		{
			if (charge_->hasAttribute(MAX_VELOCITY_ATTRIBUTE_ID) && charge_->hasAttribute(EXPLOSION_DELAY_ATTRIBUTE_ID))
			{
				float maxVelocity = charge_->getAttribute(MAX_VELOCITY_ATTRIBUTE_ID)->getValue();
				float flightTime = charge_->getAttribute(EXPLOSION_DELAY_ATTRIBUTE_ID)->getValue() / 1000.0f;
				maxRange_ = flightTime / 1000.0f * maxVelocity;
			}
			else
				maxRange_ = 0;
		}
		else
			maxRange_ = 0;
	}
	return maxRange_;
}

float Drone::getFalloff()
{
	loadIfNeeded();
	if (falloff_ < 0)
	{
		if (hasAttribute(FALLOFF_ATTRIBUTE_ID))
			falloff_ = getAttribute(FALLOFF_ATTRIBUTE_ID)->getValue();
		else
			falloff_ = 0;
	}
	return falloff_;
}

float Drone::getTrackingSpeed()
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

void Drone::calculateDamageStats()
{
	loadIfNeeded();
	if (!dealsDamage() || !isActive_)
		dps_ = volley_ = 0;
	else
	{
		volley_ = 0;
		dps_ = 0;
		float cycleTime = getCycleTime();
		if (cycleTime > 0) {
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
			dps_ = volley_ / (getCycleTime() / 1000.0f);
		}
		
		if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DURATION_ATTRIBUTE_ID)) {
			DamageVector fighterMissileVolley = 0;
			float cycleTime = getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DURATION_ATTRIBUTE_ID)->getValue();
			if (cycleTime > 0) {
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EM_ATTRIBUTE_ID))
					fighterMissileVolley.emAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EM_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_KIN_ATTRIBUTE_ID))
					fighterMissileVolley.kineticAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_KIN_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EXP_ATTRIBUTE_ID))
					fighterMissileVolley.explosiveAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EXP_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_THERM_ATTRIBUTE_ID))
					fighterMissileVolley.thermalAmount += getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_THERM_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
					fighterMissileVolley *= getAttribute(FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();
				dps_ += fighterMissileVolley / (cycleTime / 1000);
				volley_ += fighterMissileVolley;
			}
		}
		if (hasAttribute(FIGHTER_ABILITY_MISSILES_DURATION_ATTRIBUTE_ID)) {
			DamageVector fighterMissilesVolley = 0;
			float cycleTime = getAttribute(FIGHTER_ABILITY_MISSILES_DURATION_ATTRIBUTE_ID)->getValue();
			if (cycleTime > 0) {
				if (hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_EM_ATTRIBUTE_ID))
					fighterMissilesVolley.emAmount += getAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_EM_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_KIN_ATTRIBUTE_ID))
					fighterMissilesVolley.kineticAmount += getAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_KIN_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_EXP_ATTRIBUTE_ID))
					fighterMissilesVolley.explosiveAmount += getAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_EXP_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_THERM_ATTRIBUTE_ID))
					fighterMissilesVolley.thermalAmount += getAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_THERM_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
					fighterMissilesVolley *= getAttribute(FIGHTER_ABILITY_MISSILES_DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();
				dps_ += fighterMissilesVolley / (cycleTime / 1000);
				volley_ += fighterMissilesVolley;
			}
		}
		if (hasAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DURATION_ATTRIBUTE_ID)) {
			DamageVector fighterTurretVolley = 0;
			float cycleTime = getAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DURATION_ATTRIBUTE_ID)->getValue();
			if (cycleTime > 0) {
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_EM_ATTRIBUTE_ID))
					fighterTurretVolley.emAmount += getAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_EM_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_KIN_ATTRIBUTE_ID))
					fighterTurretVolley.kineticAmount += getAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_KIN_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_EXP_ATTRIBUTE_ID))
					fighterTurretVolley.explosiveAmount += getAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_EXP_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_THERM_ATTRIBUTE_ID))
					fighterTurretVolley.thermalAmount += getAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_THERM_ATTRIBUTE_ID)->getValue();
				if (hasAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_MULTIPLIER_ATTRIBUTE_ID))
					fighterTurretVolley *= getAttribute(FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_MULTIPLIER_ATTRIBUTE_ID)->getValue();
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

	if (hasAttribute(ENTITY_MISSILE_TYPE_ID_ATTRIBUTE_ID))
	{
		TypeID typeID = static_cast<TypeID>(getAttribute(ENTITY_MISSILE_TYPE_ID_ATTRIBUTE_ID)->getValue());
		charge_ = std::make_shared<Charge>(engine, typeID, shared_from_this());
		//charge_->addEffects(Effect::CATEGORY_GENERIC);
	}
	
	if (hasAttribute(FIGHTER_SQUADRON_IS_HEAVY_ATTRIBUTE_ID))
		squadron_ = FIGHTER_SQUADRON_HEAVY;
	else if (hasAttribute(FIGHTER_SQUADRON_IS_LIGHT_ATTRIBUTE_ID))
		squadron_ = FIGHTER_SQUADRON_LIGHT;
	else if (hasAttribute(FIGHTER_SQUADRON_IS_SUPPORT_ATTRIBUTE_ID))
		squadron_ = FIGHTER_SQUADRON_SUPPORT;
	else
		squadron_ = FIGHTER_SQUADRON_NONE;
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
