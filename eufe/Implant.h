#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Implant : public Item
	{
	public:
		Implant(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Character> owner);
		virtual ~Implant(void);
		std::shared_ptr<Implant> shared_from_this() {
			return std::static_pointer_cast<Implant>(Item::shared_from_this());
		}
		int getSlot();
		
		virtual Environment getEnvironment();
	protected:
		virtual void lazyLoad();
	private:
		int slot_;
	};
	
}