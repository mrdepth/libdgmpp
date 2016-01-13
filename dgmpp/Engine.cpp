#include "Engine.h"
#include "Gang.h"
#include "Area.h"
#include "ControlTower.h"
#include "Planet.h"

using namespace dgmpp;

Engine::Engine(std::shared_ptr<SqlConnector> const& sqlConnector) : sqlConnector_(sqlConnector), gang_(nullptr), area_(nullptr), controlTower_(nullptr), generation_(), updatesCounter_(0)
{
}

Engine::~Engine(void)
{
}

std::shared_ptr<SqlConnector> Engine::getSqlConnector()
{
	return sqlConnector_;
}

std::shared_ptr<Gang> Engine::getGang()
{
	if (!gang_)
		gang_ = std::make_shared<Gang>(shared_from_this());
	return gang_;
}

std::shared_ptr<Area> Engine::setArea(TypeID typeID)
{
	try
	{
		std::shared_ptr<Area> area = std::make_shared<Area>(shared_from_this(), typeID);
		if (area_) {
			area_->removeEffects(Effect::CATEGORY_SYSTEM);
		}
		area_ = area;
		if (area_)
			area_->addEffects(Effect::CATEGORY_SYSTEM);
		reset();
		
		return area_;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

std::shared_ptr<ControlTower> Engine::setControlTower(TypeID typeID)
{
	try
	{
		std::shared_ptr<ControlTower> controlTower = std::make_shared<ControlTower>(shared_from_this(), typeID);
		if (controlTower_)
		{
			controlTower_->removeEffects(Effect::CATEGORY_GENERIC);
			controlTower_->removeEffects(Effect::CATEGORY_ACTIVE);
		}
		controlTower_ = controlTower;
		if (controlTower_)
		{
			controlTower_->addEffects(Effect::CATEGORY_GENERIC);
			controlTower_->addEffects(Effect::CATEGORY_ACTIVE);
		}
		
		reset();
		return controlTower_;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void Engine::clearArea()
{
	if (area_) {
		area_->removeEffects(Effect::CATEGORY_SYSTEM);
		reset();
	}
	area_ = nullptr;
}

std::shared_ptr<Area> Engine::getArea()
{
	return area_;
}

std::shared_ptr<ControlTower> Engine::getControlTower()
{
	return controlTower_;
}

std::shared_ptr<Planet> Engine::setPlanet(TypeID typeID) {
	planet_ = std::make_shared<Planet>(shared_from_this(), typeID);
	return planet_;
}

std::shared_ptr<Planet> Engine::getPlanet() {
	return planet_;
}


void Engine::reset()
{
	if (updatesCounter_ > 0)
		return;
	generation_++;
	if (gang_)
		gang_->reset();
	if (controlTower_)
		controlTower_->reset();
}

void Engine::beginUpdates() {
	updatesCounter_++;
}

void Engine::commitUpdates() {
	updatesCounter_--;
	if (updatesCounter_ <= 0) {
		updatesCounter_ = 0;
		reset();
	}
}


//std::lock_guard<std::recursive_mutex> Engine::lock() {
//	return std::lock_guard<std::recursive_mutex>(mutex_);
//}


std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Engine& engine)
{
	os << "{\"gang\":" << *engine.getGang() << ',';
	if (engine.getControlTower())
		os << "\"controlTower\":" << *engine.getControlTower();
	os << '}';
	return os;
}
