#pragma once
#include "types.h"
#include "ThirdParty/sqlite3.h"
#include <boost/exception/all.hpp>
#include <boost/thread/recursive_mutex.hpp>

//#define FACTOR_RELOAD

namespace eufe {

	class Engine : public boost::recursive_mutex
	{
	public:
		struct SqliteException : virtual boost::exception {};

		Engine(const char* databasePath);
		~Engine(void);
		sqlite3* getDb();
		boost::shared_ptr<Area> setArea(const boost::shared_ptr<Area>& area);
		boost::shared_ptr<Area> setArea(TypeID typeID);
		boost::shared_ptr<ControlTower> setControlTower(const boost::shared_ptr<ControlTower>& controlTower);
		boost::shared_ptr<ControlTower> setControlTower(TypeID typeID);
		void clearArea();
		boost::shared_ptr<Gang> getGang();
		boost::shared_ptr<Area> getArea();
		boost::shared_ptr<ControlTower> getControlTower();
		
		void reset(Item* item);

#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Engine& engine);
#endif

	private:
		sqlite3* db_;
		boost::shared_ptr<Gang> gang_;
		boost::shared_ptr<Area> area_;
		boost::shared_ptr<ControlTower> controlTower_;
	};

}