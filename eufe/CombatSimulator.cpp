#include "CombatSimulator.h"
#include "Ship.h"

using namespace eufe;

Vector Point::operator-(const eufe::Point &p) const  {
	return Vector(x - p.x, y - p.y);
}

bool Point::operator == (const Point& p) const {
	return p.x == x && p.y == y;
}

float Vector::length() const {
	return std::sqrt(dx * dx + dy * dy);
}

float Vector::project(const Vector& v) {
	return dotProduct(v) / length();
}

float Vector::dotProduct(const Vector& v) {
	return dx * v.dx + dy * v.dy;
}

Vector Vector::operator+(const Vector& v) const {
	return Vector(dx + v.dx, dy + v.dy);
}

Vector Vector::operator-(const Vector& v) const {
	return Vector(dx - v.dx, dy - v.dy);
}

Vector Vector::operator*(float v) const {
	return Vector(dx * v, dy * v);
}

Vector Vector::operator/(float v) const {
	return Vector(dx / v, dy / v);
}

float CombatSimulator::CombatSimulatorState::range() const {
	return (attackerPosition - targetPosition).length();
}

float CombatSimulator::CombatSimulatorState::transversalVelocity() const {
	if (targetPosition == attackerPosition)
		return 0;
	
	Vector dv = targetVelocity - attackerVelocity;
	float l = dv.length();
	if (l == 0)
		return 0;
	
	float pr = (attackerPosition - targetPosition).project(dv);
	return sqrt(l * l - pr * pr);
}

float CombatSimulator::CombatSimulatorState::angularVelocity() const {
	float r = range();
	return r > 0 ? transversalVelocity() / r : 0;
}

CombatSimulator::CombatSimulator(std::shared_ptr<Ship> attacker, std::shared_ptr<Ship> target): attacker_(attacker), target_(target) {
	auto analyze = [](std::shared_ptr<Ship> attacker, std::shared_ptr<Ship> target, ModulesList& modulesList) {
		for (auto module: attacker->getModules()) {
			if (module->getState() > Module::STATE_ONLINE && module->requireTarget()) {
				if (module->isOffensive() && !module->isAssistance()) {
					module->setTarget(target);
					if (module->getDps() == 0)
						modulesList.push_back(module);
				}
				else
					module->setState(Module::STATE_ONLINE);
			}
		}
	};
	
	analyze(attacker, target, attackerOffensiveModules_);
	analyze(target, attacker, targetOffensiveModules_);
}

void CombatSimulator::setState(const CombatSimulatorState& state) {
	state_ = state;
	float range = state.range();
	for (auto module: attackerOffensiveModules_) {
		float maxRange = module->getMaxRange();
		module->setState(range > maxRange ? Module::STATE_ONLINE : Module::STATE_ACTIVE);
	}
	for (auto module: targetOffensiveModules_) {
		float maxRange = module->getMaxRange();
		module->setState(range > maxRange ? Module::STATE_ONLINE : Module::STATE_ACTIVE);
	}
	
	float v0 = state.attackerVelocity.length();
	float v1 = attacker_->getVelocity();
	if (v1 < v0)
		state_.attackerVelocity = state_.attackerVelocity * (v1 / v0);
	
	v0 = state.targetVelocity.length();
	v1 = target_->getVelocity();
	if (v1 < v0)
		state_.targetVelocity = state_.targetVelocity * (v1 / v0);
}

DamageVector CombatSimulator::dealtDPS() {
	float range = state_.range();
	float angularVelocity = state_.angularVelocity();
	HostileTarget target = HostileTarget(range, angularVelocity, target_->getSignatureRadius(), state_.targetVelocity.length());
	return attacker_->getWeaponDps(target) + attacker_->getDroneDps();
}

DamageVector CombatSimulator::receivedDPS() {
	float range = state_.range();
	float angularVelocity = state_.angularVelocity();
	HostileTarget target = HostileTarget(range, angularVelocity, attacker_->getSignatureRadius(), state_.attackerVelocity.length());
	return target_->getWeaponDps(target) + target_->getDroneDps();
}

