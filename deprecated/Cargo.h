#pragma once
#include "types.h"
#include "Item.h"

namespace dgmpp {
	
	class Cargo
	{
	public:
		Cargo(std::shared_ptr<Item> const& item, size_t count = 1);
		virtual ~Cargo(void);
		std::shared_ptr<Item> getItem();
		size_t count;
	private:
		std::shared_ptr<Item> item_;
	};
	
}
