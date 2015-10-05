#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Implant : public Item
	{
	public:
		int getSlot();
		
		virtual Environment getEnvironment();
	protected:
		friend class Character;
		Implant(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Character> owner);
		virtual ~Implant(void);

	private:
		int slot_;
	};
	
}