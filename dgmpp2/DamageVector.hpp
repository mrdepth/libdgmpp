//
//  DamageVector.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 22.11.2017.
//

#pragma once
#include "Utility.hpp"

namespace dgmpp2 {
	
	class DamageVector {
	public:
		DamageVector (HP value = 0)
		: em(value), thermal(value), kinetic(value), explosive(value) {}
		
		DamageVector (HP em, HP thermal, HP kinetic, HP explosive)
		: em(em), thermal(thermal), kinetic(kinetic), explosive(explosive) {}
		
		union {
			struct {
				HP em;
				HP thermal;
				HP kinetic;
				HP explosive;
			};
			HP damageTypes[4];
		};
		
		DamageVector effective (const Resistances::Layer& resistances) const {
			const auto emResonance			= 1.0 - resistances.em;
			const auto thermalResonance		= 1.0 - resistances.thermal;
			const auto kineticResonance		= 1.0 - resistances.kinetic;
			const auto explosiveResonance	= 1.0 - resistances.explosive;
			
			return {
				em		* emResonance,
				thermal	* thermalResonance,
				kinetic	* kineticResonance,
				explosive	* explosiveResonance
			};
		}
		
		DamageVector& operator= (HP value) {
			em = thermal = kinetic = explosive = value / 4;
			return *this;
		}
		
		DamageVector operator/ (HP value) const {
			return {em / value, thermal / value, kinetic / value, explosive / value};
		}
		
		DamageVector operator* (HP value) const {
			return {em * value, thermal * value, kinetic * value, explosive * value};
		}
		
		DamageVector operator+ (HP value) const {
			return {em + value, thermal + value, kinetic + value, explosive + value};
		}
		
		DamageVector operator- (HP value) const {
			return {em - value, thermal - value, kinetic - value, explosive - value};
		}
		
		DamageVector operator/ (const DamageVector& value) const {
			return {em / value.em, thermal / value.thermal, kinetic / value.kinetic, explosive / value.explosive};
		}
		
		DamageVector operator* (const DamageVector& value) const {
			return {em * value.em, thermal * value.thermal, kinetic * value.kinetic, explosive * value.explosive};
		}
		
		DamageVector operator+ (const DamageVector& value) const {
			return {em + value.em, thermal + value.thermal, kinetic + value.kinetic, explosive + value.explosive};
		}
		
		DamageVector operator- (const DamageVector& value) const {
			return {em - value.em, thermal - value.thermal, kinetic - value.kinetic, explosive - value.explosive};
		}
		
		template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
		DamageVector& operator/= (T2 value) {
			em /= value;
			thermal /= value;
			kinetic /= value;
			explosive /= value;
			return *this;
		}
		
		DamageVector& operator*= (HP value) {
			em *= value;
			thermal *= value;
			kinetic *= value;
			explosive *= value;
			return *this;
		}
		
		DamageVector& operator+= (HP value) {
			em += value;
			thermal += value;
			kinetic += value;
			explosive += value;
			return *this;
		}
		
		DamageVector& operator-= (HP value) {
			em -= value;
			thermal -= value;
			kinetic -= value;
			explosive -= value;
			return *this;
		}
		
		DamageVector& operator/= (const DamageVector& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] /= value.damageTypes[i];
			return *this;
		}
		
		DamageVector& operator*= (const DamageVector& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] *= value.damageTypes[i];
			return *this;
		}
		
		DamageVector& operator+= (const DamageVector& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] += value.damageTypes[i];
			return *this;
		}
		DamageVector& operator-= (const DamageVector& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] -= value.damageTypes[i];
			return *this;
		}
		
		HP total() const {
			return em + thermal + kinetic + explosive;
		}
		
		explicit operator HP() const {
			return total();
		}
		
		Multiplier effectivity(const Resistances::Layer& resistances) const {
			return total() / effective(resistances).total();
		}

		
	};
	
	using DamagePerSecond = rate<DamageVector, std::chrono::seconds>;
}

