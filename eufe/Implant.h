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
		Implant(Engine* engine, TypeID typeID, Character* owner);
		virtual ~Implant(void);

	private:
		int slot_;
	};
	
}