#pragma once
#include "types.h"
#include "Item.h"

namespace dgmpp {

	class Area : public Item
	{
	public:
		Area(std::shared_ptr<Engine> const& engine, TypeID typeID);
		virtual ~Area(void);
		std::shared_ptr<Area> shared_from_this() {
			return std::static_pointer_cast<Area>(Item::shared_from_this());
		}
		void addEffectsToShip(std::shared_ptr<Item> const& ship);
		void removeEffectsFromShip(std::shared_ptr<Item> const& ship);

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
	};

}