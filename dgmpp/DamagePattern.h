#pragma once
#include "DamageVector.h"

namespace dgmpp {
	
	class DamagePattern: public DamageVector
	{
	public:
		DamagePattern();
		DamagePattern(const DamageVector& damage);
		DamagePattern(float em, float thermal, float kinetic, float explosive);
		~DamagePattern(void);
		
		HitPoints effectiveHitPoints(const Resistances& resistances, const HitPoints& hitPoints) const;
		Tank effectiveTank(const Resistances& resistances, const Tank& tank) const;

	private:
		float effectivity(const ResistancesLayer& resistances, float amount) const;
	};
	
}