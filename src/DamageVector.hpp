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

		DamageVector(const DamageVector& other) = default;

		template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, HP>>>
		DamageVector(T value)
			: em(static_cast<HP>(value)), thermal(static_cast<HP>(value)), kinetic(static_cast<HP>(value)), explosive(static_cast<HP>(value)) {}
		
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
		
		template <typename T2, typename = std::enable_if_t<std::is_convertible_v<T2, HP>>>
		DamageVector& operator/= (T2 value) noexcept {
			auto v = static_cast<HP>(value);
			em /= v;
			thermal /= v;
			kinetic /= v;
			explosive /= v;
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
}

