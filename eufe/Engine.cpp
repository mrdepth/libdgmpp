#include "Engine.h"
#include "Gang.h"
#include "Area.h"
#include "ControlTower.h"

using namespace eufe;

Engine::Engine(const char* databasePath) : db_(NULL)
{
	int result = sqlite3_open(databasePath, &db_);
	if (result != SQLITE_OK)
		throw SqliteException() << boost::errinfo_errno(result);
	gang_.reset(new Gang(this));
	//gang_->addEffects(Effect::CATEGORY_GENERIC);
}

Engine::~Engine(void)
{
	gang_.reset();
	if (db_)
		sqlite3_close(db_);
}

sqlite3* Engine::getDb()
{
	return db_;
}

boost::shared_ptr<Gang> Engine::getGang()
{
	return gang_;
}

boost::shared_ptr<Area> Engine::setArea(const boost::shared_ptr<Area>& area)
{
	if (area_ != NULL)
		area_->removeEffects(Effect::CATEGORY_SYSTEM);
	area_ = area;
	if (area_ != NULL)
		area_->addEffects(Effect::CATEGORY_SYSTEM);
	reset(gang_.get());
//	if (controlTower_ != NULL)
//		reset(controlTower_.get());
	return area_;
}

boost::shared_ptr<Area> Engine::setArea(TypeID typeID)
{
	return setArea(boost::shared_ptr<Area>(new Area(this, typeID)));
}

boost::shared_ptr<ControlTower> Engine::setControlTower(const boost::shared_ptr<ControlTower>& controlTower)
{
	if (controlTower_ != NULL)
	{
		controlTower_->removeEffects(Effect::CATEGORY_GENERIC);
		controlTower_->removeEffects(Effect::CATEGORY_ACTIVE);
	}
	controlTower_ = controlTower;
	if (controlTower_ != NULL)
	{
		controlTower_->addEffects(Effect::CATEGORY_GENERIC);
		controlTower_->addEffects(Effect::CATEGORY_ACTIVE);
	}
	return controlTower_;
	
}

boost::shared_ptr<ControlTower> Engine::setControlTower(TypeID typeID)
{
	return setControlTower(boost::shared_ptr<ControlTower>(new ControlTower(this, typeID)));
}

void Engine::clearArea()
{
	setArea(boost::shared_ptr<Area>());
}

boost::shared_ptr<Area> Engine::getArea()
{
	return area_;
}

boost::shared_ptr<ControlTower> Engine::getControlTower()
{
	return controlTower_;
}

void Engine::reset(Item* item)
{
	if (item == NULL)
		return;
	
	Item* owner = item->getOwner();
	
	while (owner != NULL) {
		item = owner;
		owner = item->getOwner();
	}
	item->reset();
}

#if _DEBUG

std::ostream& eufe::operator<<(std::ostream& os, eufe::Engine& engine)
{
	os << "{\"gang\":" << *engine.getGang() << ',';
	os << "\"controlTower\":" << *engine.getControlTower() << '}';
	return os;
}

#endif