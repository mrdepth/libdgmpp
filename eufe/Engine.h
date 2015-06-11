#pragma once
#include "types.h"
#include "ThirdParty/sqlite3.h"
//#include <boost/exception/all.hpp>
#include <stdexcept>
#include "Mutex.h"
#include "SqlConnector.h"


//#define FACTOR_RELOAD

namespace eufe {

	class Engine : public Mutex
	{
	public:
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

#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Engine& engine);
#endif

	private:
		SqlConnector* sqlConnector_;
		Gang* gang_;
		Area* area_;
		ControlTower* controlTower_;
	};

}