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
		Charge(Engine* engine, TypeID typeID, Item* owner);
		virtual ~Charge(void);
	};
	
}