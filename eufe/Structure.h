#pragma once
#include "Module.h"

namespace eufe {
	
	class Structure : public Module
	{
	public:
		Structure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<ControlTower> const& owner = nullptr);
		virtual ~Structure(void);
		std::shared_ptr<Structure> shared_from_this() {
			return std::static_pointer_cast<Structure>(Item::shared_from_this());
		}

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