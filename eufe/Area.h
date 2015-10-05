#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {

	class Area : public Item
	{
	public:
		Area(std::shared_ptr<Engine> engine, TypeID typeID);
		virtual ~Area(void);
		void addEffectsToShip(std::shared_ptr<Item> ship);
		void removeEffectsFromShip(std::shared_ptr<Item> ship);

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		virtual Environment getEnvironment();
		
	};

}