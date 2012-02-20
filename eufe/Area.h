#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {

	class Area : public Item
	{
	public:
		Area(Engine* engine, TypeID typeID);
		virtual ~Area(void);
		void addEffectsToShip(Ship* ship);
		void removeEffectsFromShip(Ship* ship);

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		virtual boost::shared_ptr<Environment> getEnvironment();
		
	};

}