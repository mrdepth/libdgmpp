#pragma once
#include "Item.h"

namespace dgmpp {
	class Storage {
	public:
		virtual void addCommodity(std::shared_ptr<Commodity> const& commodity);
		virtual void extractCommodity(std::shared_ptr<Commodity> const& commodity);
		std::shared_ptr<Commodity> getCommodity(TypeID typeID);
	protected:
		std::map<TypeID, std::shared_ptr<Commodity>> commodities_;
	};
}