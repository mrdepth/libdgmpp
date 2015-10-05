#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Booster : public Item
	{
	public:
		int getSlot();
		
		virtual Environment getEnvironment();
	protected:
		friend class Character;
		Booster(Engine* engine, TypeID typeID, Character* owner);
		virtual ~Booster(void);

	private:
		int slot_;
		
	};
	
}