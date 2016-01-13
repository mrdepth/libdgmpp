#pragma once
#include "Item.h"

namespace dgmpp {
	class Facility: public Item {
	public:
		std::shared_ptr<Facility> Construct(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner = std::shared_ptr<Item>(nullptr));
		
		Facility(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner = std::shared_ptr<Item>(nullptr));
		int64_t identifier;
		void addInput(Route* route);
		void addOutput(Route* route);
		void removeInput(Route* route);
		void removeOutput(Route* route);
	protected:
		std::list<Route*> inputs_;
		std::list<Route*> outputs_;
	};
}