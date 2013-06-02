#include "Engine.h"
#include "Gang.h"
#include "Area.h"
#include "ControlTower.h"

using namespace eufe;

Engine::Engine(SqlConnector* sqlConnector) : sqlConnector_(sqlConnector), gang_(NULL), area_(NULL), controlTower_(NULL)
{
	gang_ = new Gang(this);
}

Engine::~Engine(void)
{
	if (gang_)
		delete gang_;
	if (area_)
		delete area_;
	if (controlTower_)
		delete controlTower_;
	if (sqlConnector_)
		delete sqlConnector_;
}

SqlConnector* Engine::getSqlConnector()
{
	return sqlConnector_;
}

Gang* Engine::getGang()
{
	return gang_;
}

Area* Engine::setArea(Area* area)
{
	if (area_) {
		area_->removeEffects(Effect::CATEGORY_SYSTEM);
		delete area_;
	}
	area_ = area;
	if (area_)
		area_->addEffects(Effect::CATEGORY_SYSTEM);
	reset(gang_);

	return area_;
}

Area* Engine::setArea(TypeID typeID)
{
	return setArea(new Area(this, typeID));
}

ControlTower* Engine::setControlTower(ControlTower* controlTower)
{
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
	return controlTower_;
	
}

ControlTower* Engine::setControlTower(TypeID typeID)
{
	return setControlTower(new ControlTower(this, typeID));
}

void Engine::clearArea()
{
	setArea((Area*)NULL);
}

Area* Engine::getArea()
{
	return area_;
}

ControlTower* Engine::getControlTower()
{
	return controlTower_;
}

void Engine::reset(Item* item)
{
	if (!item)
		return;
	
	Item* owner = item->getOwner();
	
	while (owner) {
		item = owner;
		owner = item->getOwner();
	}
	item->reset();
}

#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Engine& engine)
{
	os << "{\"gang\":" << *engine.getGang() << ',';
	if (engine.getControlTower())
		os << "\"controlTower\":" << *engine.getControlTower();
	os << '}';
	return os;
}

#endif