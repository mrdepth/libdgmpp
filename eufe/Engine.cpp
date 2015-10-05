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

Area* Engine::setArea(TypeID typeID)
{
	try
	{
		Area* area = new Area(this, typeID);
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
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

ControlTower* Engine::setControlTower(TypeID typeID)
{
	try
	{
		ControlTower* controlTower = new ControlTower(this, typeID);
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
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

void Engine::clearArea()
{
	if (area_) {
		area_->removeEffects(Effect::CATEGORY_SYSTEM);
		delete area_;
	}
	area_ = nullptr;
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
