#pragma once
#include "types.h"

namespace dgmpp {
	
	class DamageVector
	{
	public:
		DamageVector(Float value = 0);
		DamageVector(Float em, Float thermal, Float kinetic, Float explosive);
		union {
			struct {
				Float emAmount;
				Float thermalAmount;
				Float kineticAmount;
				Float explosiveAmount;
			};
			Float damageTypes[4];
		};
		
		DamageVector effectiveDamage(const ResistancesLayer& resistances) const;
		
		DamageVector& operator=(Float value);
		
		DamageVector operator/(Float value) const;
		DamageVector operator*(Float value) const;
		DamageVector operator+(Float value) const;
		DamageVector operator-(Float value) const;

		DamageVector operator/(const DamageVector& value) const;
		DamageVector operator*(const DamageVector& value) const;
		DamageVector operator+(const DamageVector& value) const;
		DamageVector operator-(const DamageVector& value) const;
		
		DamageVector& operator/=(Float value);
		DamageVector& operator*=(Float value);
		DamageVector& operator+=(Float value);
		DamageVector& operator-=(Float value);
		
		DamageVector& operator/=(const DamageVector& value);
		DamageVector& operator*=(const DamageVector& value);
		DamageVector& operator+=(const DamageVector& value);
		DamageVector& operator-=(const DamageVector& value);
		
		
		operator Float() const;

	};
}
