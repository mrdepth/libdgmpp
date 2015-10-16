#include "Engine.h"
#include "Gang.h"
#include "Area.h"
#include "ControlTower.h"

using namespace eufe;

Engine::Engine(std::shared_ptr<SqlConnector> sqlConnector) : sqlConnector_(sqlConnector), gang_(nullptr), area_(nullptr), controlTower_(nullptr)
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
		reset(getGang());
		
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
		
		reset(controlTower_);
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

void Engine::reset(std::shared_ptr<Item> item)
{
	if (!item)
		return;
	
	std::shared_ptr<Item> owner = item->getOwner();
	
	while (owner) {
		item = owner;
		owner = item->getOwner();
	}
	item->reset();
}

//std::lock_guard<std::recursive_mutex> Engine::lock() {
//	return std::lock_guard<std::recursive_mutex>(mutex_);
//}


std::ostream& eufe::operator<<(std::ostream& os, eufe::Engine& engine)
{
	os << "{\"gang\":" << *engine.getGang() << ',';
	if (engine.getControlTower())
		os << "\"controlTower\":" << *engine.getControlTower();
	os << '}';
	return os;
}
