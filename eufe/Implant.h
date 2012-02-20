#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Implant : public Item
	{
	public:
		Implant(Engine* engine, TypeID typeID, Character* owner);
		virtual ~Implant(void);
		int getSlot();
		
		virtual boost::shared_ptr<Environment> getEnvironment();
	private:
		int slot_;
	};
	
}