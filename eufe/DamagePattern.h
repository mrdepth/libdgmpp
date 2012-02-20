#pragma once
#include "types.h"

namespace eufe {
	
	class DamagePattern
	{
	public:
		DamagePattern();
		DamagePattern(float em, float thermal, float kinetic, float explosive);
		~DamagePattern(void);
		
		HitPoints effectiveHitPoints(const Resistances& resistances, const HitPoints& hitPoints);
		Tank effectiveTank(const Resistances& resistances, const Tank& tank);

		float emAmount;
		float thermalAmount;
		float kineticAmount;
		float explosiveAmount;
		
	private:
		float effectivity(const Resistances::Layer& resistances, float amount);
	};
	
}