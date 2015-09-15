#pragma once
#include "types.h"
#include <sqlite3.h>
//#include <boost/exception/all.hpp>
#include <stdexcept>
#include <mutex>
#include "SqlConnector.h"


//#define FACTOR_RELOAD

namespace eufe {

	class Engine
	{
	public:
		class ScopedLock : public std::lock_guard<std::recursive_mutex> {
		public:
			ScopedLock(Engine* engine): std::lock_guard<std::recursive_mutex>(engine->mutex_) {
			};
		};
		
		//struct SqliteException : virtual boost::exception {};
        typedef std::runtime_error SqliteException;

		Engine(SqlConnector* sqlConnector);
		virtual ~Engine(void);
		SqlConnector* getSqlConnector();
		Area* setArea(Area* area);
		Area* setArea(TypeID typeID);
		ControlTower* setControlTower(ControlTower* controlTower);
		ControlTower* setControlTower(TypeID typeID);
		void clearArea();
		Gang* getGang();
		Area* getArea();
		ControlTower* getControlTower();
		
		void reset(Item* item);
		
		//std::lock_guard<std::recursive_mutex> lock();

#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Engine& engine);
#endif

	private:
		SqlConnector* sqlConnector_;
		Gang* gang_;
		Area* area_;
		ControlTower* controlTower_;
		std::recursive_mutex mutex_;
	};

}