#pragma once
#include "types.h"
#include "Item.h"

namespace dgmpp {
	
	class Implant : public Item
	{
	public:
		Implant(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner);
		virtual ~Implant(void);
		std::shared_ptr<Implant> shared_from_this() {
			return std::static_pointer_cast<Implant>(Item::shared_from_this());
		}
		int getSlot();
		
		virtual Item* character();
		virtual Item* ship();
	protected:
		virtual void lazyLoad();
	private:
		int slot_;
	};
	
}