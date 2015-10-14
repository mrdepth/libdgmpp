#include "Drone.h"
#include "Ship.h"
#include "Effect.h"
#include "Attribute.h"
#include "Engine.h"
#include "Area.h"
#include "Charge.h"

using namespace eufe;

Drone::Drone(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Ship> owner) : Item(engine, typeID, owner), isActive_(true), target_(), charge_(nullptr)
{
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
}

Drone::~Drone(void)
{
}

Environment Drone::getEnvironment()
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

void Drone::setTarget(std::shared_ptr<Ship> target)
{
	if (target == getOwner())
		throw BadDroneTargetException("self");

	removeEffects(Effect::CATEGORY_TARGET);
	std::shared_ptr<Ship> oldTarget = target_.lock();
	if (oldTarget)
		oldTarget->removeProjectedDrone(shared_from_this());
	target_ = target;
	if (target)
		target->addProjectedDrone(shared_from_this());
	addEffects(Effect::CATEGORY_TARGET);
	auto engine = getEngine();
	if (engine)
		engine->reset(shared_from_this());
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
								hasAttribute(THERMAL_DAMAGE_ATTRIBUTE_ID);
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
		engine->reset(shared_from_this());
}

bool Drone::isActive()
{
	loadIfNeeded();
	return isActive_;
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
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
	if (charge_)
		charge_->reset();
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

float Drone::getVolley()
{
	loadIfNeeded();
	if (volley_ < 0)
		calculateDamageStats();
	return volley_;
}

float Drone::getDps()
{
	loadIfNeeded();
	if (dps_ < 0)
		calculateDamageStats();
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
		dps_ = volley_ / (getCycleTime() / 1000.0f);
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
}
