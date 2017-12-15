#pragma once
#include "DamageVector.h"

namespace dgmpp {
	
	class DamagePattern: public DamageVector
	{
	public:
		DamagePattern();
		DamagePattern(const DamageVector& damage);
		DamagePattern(Float em, Float thermal, Float kinetic, Float explosive);
		~DamagePattern(void);
		
		HitPoints effectiveHitPoints(const Resistances& resistances, const HitPoints& hitPoints) const;
		Tank effectiveTank(const Resistances& resistances, const Tank& tank) const;

	private:
		Float effectivity(const ResistancesLayer& resistances, Float amount) const;
	};
	
}
