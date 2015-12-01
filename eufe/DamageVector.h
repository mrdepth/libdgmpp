#pragma once
#include "types.h"

namespace eufe {
	
	class DamageVector
	{
	public:
		DamageVector(float value = 0);
		DamageVector(float em, float thermal, float kinetic, float explosive);
		union {
			struct {
				float emAmount;
				float thermalAmount;
				float kineticAmount;
				float explosiveAmount;
			};
			float damageTypes[4];
		};
		
		DamageVector effectiveDamage(const ResistancesLayer& resistances) const;
		
		DamageVector& operator=(float value);
		
		DamageVector operator/(float value) const;
		DamageVector operator*(float value) const;
		DamageVector operator+(float value) const;
		DamageVector operator-(float value) const;
		
		DamageVector& operator/=(float value);
		DamageVector& operator*=(float value);
		DamageVector& operator+=(float value);
		DamageVector& operator-=(float value);
		
		DamageVector& operator/=(const DamageVector& value);
		DamageVector& operator*=(const DamageVector& value);
		DamageVector& operator+=(const DamageVector& value);
		DamageVector& operator-=(const DamageVector& value);
		
		operator float() const;

	};
}