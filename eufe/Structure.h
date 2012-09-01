#pragma once
#include "Module.h"

namespace eufe {
	
	class Structure : public Module
	{
	public:
		Structure(Engine* engine, TypeID typeID, Item* owner = NULL);
		Structure(const Structure& from);
		virtual ~Structure(void);

		virtual void setState(State state);
		
		virtual void reset();
		
		//Tank
		const Resistances& getResistances();
		const Tank& getTank();
		const Tank& getEffectiveTank();
		
		const HitPoints& getHitPoints();
		const HitPoints& getEffectiveHitPoints();
		
		float getShieldRecharge();

	private:
		Resistances resistances_;
		Tank tank_;
		Tank effectiveTank_;
		HitPoints hitPoints_;
		HitPoints effectiveHitPoints_;
		float shieldRecharge_;
	};
}