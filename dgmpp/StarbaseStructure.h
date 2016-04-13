#pragma once
#include "Module.h"

namespace dgmpp {
	
	class StarbaseStructure : public Module
	{
	public:
		StarbaseStructure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<ControlTower> const& owner = std::shared_ptr<ControlTower>(nullptr));
		virtual ~StarbaseStructure(void);
		std::shared_ptr<StarbaseStructure> shared_from_this() {
			return std::static_pointer_cast<StarbaseStructure>(Item::shared_from_this());
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