#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Booster : public Item
	{
	public:
		Booster(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Character> owner);
		virtual ~Booster(void);
		std::shared_ptr<Booster> shared_from_this() {
			return std::static_pointer_cast<Booster>(Item::shared_from_this());
		}
		int getSlot();
		
		virtual Environment getEnvironment();
	protected:
		virtual void lazyLoad();

	private:
		int slot_;
		
	};
	
}