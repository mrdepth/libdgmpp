#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Charge : public Item
	{
	public:
		Charge(Engine* engine, TypeID typeID, Item* owner);
		virtual ~Charge(void);
		
		virtual Environment getEnvironment();
		
	};
	
}