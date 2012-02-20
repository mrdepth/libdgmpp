#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Booster : public Item
	{
	public:
		Booster(Engine* engine, TypeID typeID, Character* owner);
		virtual ~Booster(void);
		int getSlot();
		
		virtual boost::shared_ptr<Environment> getEnvironment();
	private:
		int slot_;
		
	};
	
}