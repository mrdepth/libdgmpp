//
//  DamageVector.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 22.11.2017.
//

#pragma once
#include "Utility.hpp"

namespace dgmpp2 {
	
	template <typename T>
	class DamageVector {
	public:
		DamageVector (T value = 0)
		: emAmount(value), thermalAmount(value), kineticAmount(value), explosiveAmount(value) {}
		
		template <typename T2>
		explicit DamageVector (const DamageVector<T2>& other)
		: emAmount(other.emAmount), thermalAmount(other.thermalAmount), kineticAmount(other.kineticAmount), explosiveAmount(other.explosiveAmount) {}
		
		DamageVector (T em, T thermal, T kinetic, T explosive)
		: emAmount(em), thermalAmount(thermal), kineticAmount(kinetic), explosiveAmount(explosive) {}
		
		union {
			struct {
				T emAmount;
				T thermalAmount;
				T kineticAmount;
				T explosiveAmount;
			};
			T damageTypes[4];
		};
		
		DamageVector<T> effectiveDamage (const ResistancesLayer& resistances) const {
			auto emResonance		= 1.0 - resistances.em;
			auto thermalResonance	= 1.0 - resistances.thermal;
			auto kineticResonance	= 1.0 - resistances.kinetic;
			auto explosiveResonance	= 1.0 - resistances.explosive;
			
			return {
				emAmount		* emResonance,
				thermalAmount	* thermalResonance,
				kineticAmount	* kineticResonance,
				explosiveAmount	* explosiveResonance
			};
		}
		
		DamageVector<T>& operator= (T value) {
			emAmount = thermalAmount = kineticAmount = explosiveAmount = value / 4;
		}
		
		template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
		DamageVector<T> operator/ (T2 value) const {
			return {emAmount / value, thermalAmount / value, kineticAmount / value, explosiveAmount / value};
		}
		
		template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
		DamageVector<T> operator* (T2 value) const {
			return {emAmount * value, thermalAmount * value, kineticAmount * value, explosiveAmount * value};
		}
		
		DamageVector<T> operator+ (T value) const {
			return {emAmount + value, thermalAmount + value, kineticAmount + value, explosiveAmount + value};
		}
		
		DamageVector<T> operator- (T value) const {
			return {emAmount - value, thermalAmount - value, kineticAmount - value, explosiveAmount - value};
		}
		
		DamageVector<T> operator/ (const DamageVector<T>& value) const {
			return {emAmount / value.emAmount, thermalAmount / value.thermalAmount, kineticAmount / value.kineticAmount, explosiveAmount / value.explosiveAmount};
		}
		
		DamageVector<T> operator* (const DamageVector<T>& value) const {
			return {emAmount * value.emAmount, thermalAmount * value.thermalAmount, kineticAmount * value.kineticAmount, explosiveAmount * value.explosiveAmount};
		}
		
		DamageVector<T> operator+ (const DamageVector<T>& value) const {
			return {emAmount + value.emAmount, thermalAmount + value.thermalAmount, kineticAmount + value.kineticAmount, explosiveAmount + value.explosiveAmount};
		}
		
		DamageVector<T> operator- (const DamageVector<T>& value) const {
			return {emAmount - value.emAmount, thermalAmount - value.thermalAmount, kineticAmount - value.kineticAmount, explosiveAmount - value.explosiveAmount};
		}
		
		template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
		DamageVector<T>& operator/= (T2 value) {
			emAmount /= value;
			thermalAmount /= value;
			kineticAmount /= value;
			explosiveAmount /= value;
			return *this;
		}
		
		template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
		DamageVector<T>& operator*= (T2 value) {
			emAmount *= value;
			thermalAmount *= value;
			kineticAmount *= value;
			explosiveAmount *= value;
			return *this;
		}
		
		DamageVector<T>& operator+= (T value) {
			emAmount += value;
			thermalAmount += value;
			kineticAmount += value;
			explosiveAmount += value;
			return *this;
		}
		
		DamageVector<T>& operator-= (T value) {
			emAmount -= value;
			thermalAmount -= value;
			kineticAmount -= value;
			explosiveAmount -= value;
			return *this;
		}
		
		DamageVector<T>& operator/= (const DamageVector<T>& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] /= value.damageTypes[i];
			return *this;
		}
		
		DamageVector<T>& operator*= (const DamageVector<T>& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] *= value.damageTypes[i];
			return *this;
		}
		
		DamageVector<T>& operator+= (const DamageVector<T>& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] += value.damageTypes[i];
			return *this;
		}
		DamageVector<T>& operator-= (const DamageVector<T>& value) {
			for (int i = 0; i < 4; i++)
				damageTypes[i] -= value.damageTypes[i];
			return *this;
		}
		
		T total() const {
			return emAmount + thermalAmount + kineticAmount + explosiveAmount;
		}
		
		explicit operator T() const {
			return total();
		}
		
	};
	
	using DamagePerSecond = rate<DamageVector<HP>, std::chrono::seconds>;
}

