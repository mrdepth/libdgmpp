#include "DamageVector.h"

using namespace dgmpp;

DamageVector::DamageVector(Float value): emAmount(value), thermalAmount(value), kineticAmount(value), explosiveAmount(value) {
	
}

DamageVector::DamageVector(Float em, Float thermal, Float kinetic, Float explosive) : emAmount(em), thermalAmount(thermal), kineticAmount(kinetic), explosiveAmount(explosive)
{
}

DamageVector DamageVector::effectiveDamage(const ResistancesLayer& resistances) const {
	Float emResonance		 = 1.0 - resistances.em;
	Float thermalResonance	 = 1.0 - resistances.thermal;
	Float kineticResonance	 = 1.0 - resistances.kinetic;
	Float explosiveResonance = 1.0 - resistances.explosive;

	DamageVector damage(0);
	damage.emAmount = emAmount * emResonance;
	damage.thermalAmount = thermalAmount * thermalResonance;
	damage.kineticAmount = kineticAmount * kineticResonance;
	damage.explosiveAmount = explosiveAmount * explosiveResonance;
	return damage;
}

DamageVector& DamageVector::operator=(Float value) {
	emAmount = thermalAmount = kineticAmount = explosiveAmount = value / 4;
	return *this;
}

DamageVector DamageVector::operator/(Float value) const {
	return DamageVector(emAmount / value, thermalAmount / value, kineticAmount / value, explosiveAmount / value);
}

DamageVector DamageVector::operator*(Float value) const {
	return DamageVector(emAmount * value, thermalAmount * value, kineticAmount * value, explosiveAmount * value);
}

DamageVector DamageVector::operator+(Float value) const {
	value /= 4;
	return DamageVector(emAmount + value, thermalAmount + value, kineticAmount + value, explosiveAmount + value);
}

DamageVector DamageVector::operator-(Float value)  const{
	value /= 4;
	return DamageVector(emAmount - value, thermalAmount - value, kineticAmount - value, explosiveAmount - value);
}

DamageVector DamageVector::operator/(const DamageVector& value) const {
	return DamageVector(emAmount / value.emAmount, thermalAmount / value.thermalAmount, kineticAmount / value.kineticAmount, explosiveAmount / value.explosiveAmount);
}

DamageVector DamageVector::operator*(const DamageVector& value) const {
	return DamageVector(emAmount * value.emAmount, thermalAmount * value.thermalAmount, kineticAmount * value.kineticAmount, explosiveAmount * value.explosiveAmount);
}

DamageVector DamageVector::operator+(const DamageVector& value) const {
	return DamageVector(emAmount + value.emAmount, thermalAmount + value.thermalAmount, kineticAmount + value.kineticAmount, explosiveAmount + value.explosiveAmount);
}

DamageVector DamageVector::operator-(const DamageVector& value) const {
	return DamageVector(emAmount - value.emAmount, thermalAmount - value.thermalAmount, kineticAmount - value.kineticAmount, explosiveAmount - value.explosiveAmount);
}


DamageVector& DamageVector::operator/=(Float value) {
	emAmount /= value;
	thermalAmount /= value;
	kineticAmount /= value;
	explosiveAmount /= value;
	return *this;
}

DamageVector& DamageVector::operator*=(Float value) {
	emAmount *= value;
	thermalAmount *= value;
	kineticAmount *= value;
	explosiveAmount *= value;
	return *this;
}

DamageVector& DamageVector::operator+=(Float value) {
	emAmount += value;
	thermalAmount += value;
	kineticAmount += value;
	explosiveAmount += value;
	return *this;
}

DamageVector& DamageVector::operator-=(Float value) {
	emAmount -= value;
	thermalAmount -= value;
	kineticAmount -= value;
	explosiveAmount -= value;
	return *this;
}

DamageVector& DamageVector::operator/=(const DamageVector& value) {
	for (int i = 0; i < 4; i++)
		damageTypes[i] /= value.damageTypes[i];
	return *this;
}

DamageVector& DamageVector::operator*=(const DamageVector& value) {
	for (int i = 0; i < 4; i++)
		damageTypes[i] *= value.damageTypes[i];
	return *this;
}

DamageVector& DamageVector::operator+=(const DamageVector& value) {
	for (int i = 0; i < 4; i++)
		damageTypes[i] += value.damageTypes[i];
	return *this;
}

DamageVector& DamageVector::operator-=(const DamageVector& value) {
	for (int i = 0; i < 4; i++)
		damageTypes[i] -= value.damageTypes[i];
	return *this;
}

DamageVector::operator Float() const {
	return emAmount + thermalAmount + kineticAmount + explosiveAmount;
}
