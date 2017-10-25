#pragma once
#include "Ship.h"

namespace dgmpp {
	
	class Structure : public Ship
	{
	public:
		Structure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner = std::shared_ptr<Character>(nullptr));
		virtual ~Structure(void);

		std::shared_ptr<Structure> shared_from_this() {
			return std::static_pointer_cast<Structure>(Item::shared_from_this());
		}
		virtual std::vector<CategoryID> getSupportedModuleCategories() const;
		virtual std::vector<CategoryID> getSupportedDroneCategories() const;
		
		virtual Float getTotalDroneBay();
		TypeID getFuelBlockTypeID();
		Float getCycleFuelNeed();
		Float getCycleTime();
	};
}
