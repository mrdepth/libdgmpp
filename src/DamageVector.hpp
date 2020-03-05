//
//  DamageVector.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 22.11.2017.
//

#pragma once
#include "Utility.hpp"
#include <type_traits>

namespace dgmpp {
	
	class DamageVector {
	public:

		DamageVector (HP value = 0)
		: em(value), thermal(value), kinetic(value), explosive(value) {}

		//template<typename T, std::enable_if_t<std::is_arithmetic_v<std::decay_t<T>>>>
		//DamageVector(T value)
		//	: em(value), thermal(value), kinetic(value), explosive(value) {}
		
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
		
		DamageVector effective (const Resistances::Layer& resistances) const noexcept {
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
		
		DamageVector& operator= (HP value) noexcept {
			em = thermal = kinetic = explosive = value / 4;
			return *this;
		}
		
		DamageVector operator/ (HP value) const noexcept {
			return {em / value, thermal / value, kinetic / value, explosive / value};
		}
		
		DamageVector operator* (HP value) const noexcept {
			return {em * value, thermal * value, kinetic * value, explosive * value};
		}
		
		DamageVector operator+ (HP value) const noexcept {
			return {em + value, thermal + value, kinetic + value, explosive + value};
		}
		
		DamageVector operator- (HP value) const noexcept {
			return {em - value, thermal - value, kinetic - value, explosive - value};
		}
		
		DamageVector operator/ (const DamageVector& value) const noexcept {
			return {em / value.em, thermal / value.thermal, kinetic / value.kinetic, explosive / value.explosive};
		}
		
		DamageVector operator* (const DamageVector& value) const noexcept {
			return {em * value.em, thermal * value.thermal, kinetic * value.kinetic, explosive * value.explosive};
		}
		
		DamageVector operator+ (const DamageVector& value) const noexcept {
			return {em + value.em, thermal + value.thermal, kinetic + value.kinetic, explosive + value.explosive};
		}
		
		DamageVector operator- (const DamageVector& value) const noexcept {
			return {em - value.em, thermal - value.thermal, kinetic - value.kinetic, explosive - value.explosive};
		}
		
		template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
		DamageVector& operator/= (T2 value) noexcept {
			em /= value;
			thermal /= value;
			kinetic /= value;
			explosive /= value;
			return *this;
		}
		
		DamageVector& operator*= (HP value) noexcept {
			em *= value;
			thermal *= value;
			kinetic *= value;
			explosive *= value;
			return *this;
		}
		
		DamageVector& operator+= (HP value) noexcept {
			em += value;
			thermal += value;
			kinetic += value;
			explosive += value;
			return *this;
		}
		
		DamageVector& operator-= (HP value) noexcept {
			em -= value;
			thermal -= value;
			kinetic -= value;
			explosive -= value;
			return *this;
		}
		
		DamageVector& operator/= (const DamageVector& value) noexcept {
			for (int i = 0; i < 4; i++)
				damageTypes[i] /= value.damageTypes[i];
			return *this;
		}
		
		DamageVector& operator*= (const DamageVector& value) noexcept {
			for (int i = 0; i < 4; i++)
				damageTypes[i] *= value.damageTypes[i];
			return *this;
		}
		
		DamageVector& operator+= (const DamageVector& value) noexcept {
			for (int i = 0; i < 4; i++)
				damageTypes[i] += value.damageTypes[i];
			return *this;
		}
		DamageVector& operator-= (const DamageVector& value) noexcept {
			for (int i = 0; i < 4; i++)
				damageTypes[i] -= value.damageTypes[i];
			return *this;
		}
		
		HP total() const noexcept {
			return em + thermal + kinetic + explosive;
		}
		
		explicit operator HP() const noexcept {
			return total();
		}
		
		Multiplier effectivity(const Resistances::Layer& resistances) const noexcept {
			return total() / effective(resistances).total();
		}

		
	};
	
	using DamagePerSecond = rate<DamageVector, std::chrono::seconds>;

	template<typename Period>
	auto make_rate(const DamageVector& value, const Period& period) noexcept {
		auto c = period.count();
		return rate<DamageVector, Period>(c > 0 ? value / static_cast<HP>(c) : DamageVector(0.0));
	}
}

