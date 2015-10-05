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
		Booster(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Character> owner);
		virtual ~Booster(void);

	private:
		int slot_;
		
	};
	
}