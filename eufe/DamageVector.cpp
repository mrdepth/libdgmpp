#include "DamageVector.h"

using namespace eufe;

DamageVector::DamageVector(float value): emAmount(value), thermalAmount(value), kineticAmount(value), explosiveAmount(value) {
	
}

DamageVector::DamageVector(float em, float thermal, float kinetic, float explosive) : emAmount(em), thermalAmount(thermal), kineticAmount(kinetic), explosiveAmount(explosive)
{
}

DamageVector DamageVector::effectiveDamage(const ResistancesLayer& resistances) const {
	float emResonance		 = 1.0f - resistances.em;
	float thermalResonance	 = 1.0f - resistances.thermal;
	float kineticResonance	 = 1.0f - resistances.kinetic;
	float explosiveResonance = 1.0f - resistances.explosive;

	DamageVector damage(0);
	damage.emAmount = emAmount * emResonance;
	damage.thermalAmount = thermalAmount * thermalResonance;
	damage.kineticAmount = kineticAmount * kineticResonance;
	damage.explosiveAmount = explosiveAmount * explosiveResonance;
	return damage;
}

DamageVector& DamageVector::operator=(float value) {
	emAmount = thermalAmount = kineticAmount = explosiveAmount = value;
	return *this;
}

DamageVector DamageVector::operator/(float value) const {
	return DamageVector(emAmount / value, thermalAmount / value, kineticAmount / value, explosiveAmount / value);
}

DamageVector DamageVector::operator*(float value) const {
	return DamageVector(emAmount * value, thermalAmount * value, kineticAmount * value, explosiveAmount * value);
}

DamageVector DamageVector::operator+(float value) const {
	return DamageVector(emAmount + value, thermalAmount + value, kineticAmount + value, explosiveAmount + value);
}

DamageVector DamageVector::operator-(float value)  const{
	return DamageVector(emAmount - value, thermalAmount - value, kineticAmount - value, explosiveAmount - value);
}

DamageVector& DamageVector::operator/=(float value) {
	emAmount /= value;
	thermalAmount /= value;
	kineticAmount /= value;
	explosiveAmount /= value;
	return *this;
}

DamageVector& DamageVector::operator*=(float value) {
	emAmount *= value;
	thermalAmount *= value;
	kineticAmount *= value;
	explosiveAmount *= value;
	return *this;
}

DamageVector& DamageVector::operator+=(float value) {
	emAmount += value;
	thermalAmount += value;
	kineticAmount += value;
	explosiveAmount += value;
	return *this;
}

DamageVector& DamageVector::operator-=(float value) {
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

DamageVector::operator float() const {
	return emAmount + thermalAmount + kineticAmount + explosiveAmount;
}
