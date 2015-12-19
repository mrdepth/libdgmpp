#pragma once
#include "types.h"
#include <sqlite3.h>
#include <stdexcept>
#include <mutex>
#include "SqlConnector.h"
#include "EffectPrototype.h"

//#define FACTOR_RELOAD

namespace eufe {
	class Engine : public std::enable_shared_from_this<Engine>
	{
	public:
		class ScopedLock : public std::lock_guard<std::recursive_mutex> {
		public:
			ScopedLock(std::shared_ptr<Engine> const& engine): std::lock_guard<std::recursive_mutex>(engine->mutex_) {
			};
		};
		
		//struct SqliteException : virtual boost::exception {};
        typedef std::runtime_error SqliteException;

		Engine(std::shared_ptr<SqlConnector> const& sqlConnector);
		virtual ~Engine(void);
		std::shared_ptr<SqlConnector> getSqlConnector();
		std::shared_ptr<Area> setArea(TypeID typeID);
		std::shared_ptr<ControlTower> setControlTower(TypeID typeID);
		void clearArea();
		std::shared_ptr<Gang> getGang();
		std::shared_ptr<Area> getArea();
		std::shared_ptr<ControlTower> getControlTower();
		
		void reset();
		void beginUpdates();
		void commitUpdates();
		
		friend std::ostream& operator<<(std::ostream& os, Engine& engine);
		
		std::map<TypeID, std::shared_ptr<eufe::EffectPrototype> >& getReusableEffectPrototypes() {
			return reusableEffectPrototypes_;
		}
		std::map<TypeID, std::shared_ptr<eufe::EffectPrototype::ModifierPrototype> >& getReusableModifierPrototypes() {
			return reusableModifierPrototypes_;
		}
		
		uint32_t getGeneration() const {
			return generation_;
		}
		
	private:
		std::shared_ptr<SqlConnector> sqlConnector_;
		std::shared_ptr<Gang> gang_;
		std::shared_ptr<Area> area_;
		std::shared_ptr<ControlTower> controlTower_;
		std::recursive_mutex mutex_;
		
		std::map<TypeID, std::shared_ptr<eufe::EffectPrototype> > reusableEffectPrototypes_;
		std::map<TypeID, std::shared_ptr<eufe::EffectPrototype::ModifierPrototype> > reusableModifierPrototypes_;
		uint32_t generation_;
		int32_t updatesCounter_;

	};

}