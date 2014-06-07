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
	Gang* gangTmp = gang_;
	Area* areaTmp = area_;
	ControlTower* controlTowerTmp = controlTower_;
	SqlConnector* sqlConnectorTmp = sqlConnector_;
	
	gang_ = NULL;
	area_ = NULL;
	controlTower_ = NULL;
	sqlConnector_ = NULL;
	
	if (gangTmp)
		delete gangTmp;
	if (areaTmp)
		delete areaTmp;
	if (controlTowerTmp)
		delete controlTowerTmp;
	if (sqlConnectorTmp)
		delete sqlConnectorTmp;
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
	try
	{
		return setArea(new Area(this, typeID));
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
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
	try
	{
		return setControlTower(new ControlTower(this, typeID));
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
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