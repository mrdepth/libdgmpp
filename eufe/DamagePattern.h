#pragma once
#include "types.h"

namespace eufe {
	
	class DamagePattern
	{
	public:
		DamagePattern();
		DamagePattern(float em, float thermal, float kinetic, float explosive);
		~DamagePattern(void);
		
		HitPoints effectiveHitPoints(const Resistances& resistances, const HitPoints& hitPoints) const;
		Tank effectiveTank(const Resistances& resistances, const Tank& tank) const;

		union {
			struct {
				float emAmount;
				float thermalAmount;
				float kineticAmount;
				float explosiveAmount;
			};
			float damageTypes[4];
		};
		
	private:
		float effectivity(const ResistancesLayer& resistances, float amount) const;
	};
	
}