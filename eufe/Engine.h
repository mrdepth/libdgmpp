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
		Area* setArea(Area* area);
		Area* setArea(TypeID typeID);
		ControlTower* setControlTower(ControlTower* controlTower);
		ControlTower* setControlTower(TypeID typeID);
		void clearArea();
		Gang* getGang();
		Area* getArea();
		ControlTower* getControlTower();
		
		void reset(Item* item);

#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Engine& engine);
#endif

	private:
		sqlite3* db_;
		Gang* gang_;
		Area* area_;
		ControlTower* controlTower_;
	};

}