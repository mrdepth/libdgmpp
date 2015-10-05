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

		Engine(std::shared_ptr<SqlConnector> sqlConnector);
		virtual ~Engine(void);
		std::shared_ptr<SqlConnector> getSqlConnector();
		std::shared_ptr<Area> setArea(TypeID typeID);
		std::shared_ptr<ControlTower> setControlTower(TypeID typeID);
		void clearArea();
		std::shared_ptr<Gang> getGang();
		std::shared_ptr<Area> getArea();
		std::shared_ptr<ControlTower> getControlTower();
		
		void reset(std::shared_ptr<Item> item);
		
		friend std::ostream& operator<<(std::ostream& os, Engine& engine);

	private:
		std::shared_ptr<SqlConnector> sqlConnector_;
		std::shared_ptr<Gang> gang_;
		std::shared_ptr<Area> area_;
		std::shared_ptr<ControlTower> controlTower_;
		std::recursive_mutex mutex_;
	};

}