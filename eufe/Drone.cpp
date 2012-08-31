#include "Drone.h"
#include "Ship.h"
#include "Effect.h"
#include "Attribute.h"
#include "Engine.h"
#include "Area.h"
#include "Charge.h"

using namespace eufe;

Drone::Drone(Engine* engine, TypeID typeID, Ship* owner) : Item(engine, typeID, owner), isActive_(true), target_(nullptr), charge_(nullptr)
{
	if (hasAttribute(ENTITY_MISSILE_TYPE_ID_ATTRIBUTE_ID))
	{
		TypeID typeID = static_cast<TypeID>(getAttribute(ENTITY_MISSILE_TYPE_ID_ATTRIBUTE_ID)->getValue());
		charge_ = new Charge(engine, typeID, this);
		//charge_->addEffects(Effect::CATEGORY_GENERIC);
	}
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
}

Drone::Drone(const Drone& from) : Item(from), isActive_(from.isActive_), target_(nullptr), charge_(nullptr)
{
	if (from.charge_)
	{
		charge_ = new Charge(*from.charge_);
		charge_->setOwner(this);
		//charge_->addEffects(Effect::CATEGORY_GENERIC);
	}
	dps_ = maxRange_ = falloff_ = volley_ = trackingSpeed_ = -1;
}

Drone::~Drone(void)
{
	if (charge_)
		delete charge_;
	if (target_)
		clearTarget();
}

Environment Drone::getEnvironment()
{
	Environment environment;
	environment["Self"] = this;
	Item* ship = getOwner();
	Item* character = ship ? ship->getOwner() : nullptr;
	Item* gang = character ? character->getOwner() : nullptr;
	
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

void Drone::setTarget(Ship* target)
{
	if (target == getOwner())
		throw BadDroneTargetException() << BadDroneTargetExceptionInfo(target);

	removeEffects(Effect::CATEGORY_TARGET);
	if (target_)
		target_->removeProjectedDrone(this);
	target_ = target;
	if (target)
		target->addProjectedDrone(this);
	addEffects(Effect::CATEGORY_TARGET);
	engine_->reset(this);
}

void Drone::clearTarget()
{
	setTarget(nullptr);
}

Ship* Drone::getTarget()
{
	return target_;
}

bool Drone::dealsDamage()
{
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

Charge* Drone::getCharge()
{
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
	engine_->reset(this);
}

bool Drone::isActive()
{
	return isActive_;
}

void Drone::addEffects(Effect::Category category)
{
	Item::addEffects(category);
	if (category == Effect::CATEGORY_GENERIC && charge_)
		charge_->addEffects(category);
}

void Drone::removeEffects(Effect::Category category)
{
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
	if (volley_ < 0)
		calculateDamageStats();
	return volley_;
}

float Drone::getDps()
{
	if (dps_ < 0)
		calculateDamageStats();
	return dps_;
}

float Drone::getMaxRange()
{
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
				float flightTime = charge_->getAttribute(EXPLOSION_DELAY_ATTRIBUTE_ID)->getValue() / 1000.0;
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

float Drone::getFalloff()
{
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
	if (!dealsDamage() || !isActive_)
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
		dps_ = volley_ / (getCycleTime() / 1000.0);
	}
}