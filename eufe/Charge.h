#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Charge : public Item
	{
	public:
		virtual Environment getEnvironment();
	protected:
		friend class Module;
		friend class Drone;
		Charge(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Item> owner);
		virtual ~Charge(void);
	};
	
}