#include "CombatSimulator.h"
#include "Ship.h"
#include "Engine.h"
#include <limits>
#include <algorithm>

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

CombatSimulator::State::State(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target) : attacker_(attacker), target_(target) {
}

CombatSimulator::OrbitState::OrbitState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, float orbitRadius, float attackerVelocity) : State(attacker, target), orbitRadius_(orbitRadius), attackerVelocity_(attackerVelocity), calculatedAttackerVelocity_(-1), generation_(0) {
}

void CombatSimulator::OrbitState::setOrbitRadius(float orbitRadius) {
	orbitRadius_ = orbitRadius;
	calculatedAttackerVelocity_ = -1;
	generation_ = 0;
}


float CombatSimulator::OrbitState::range() const {
	return orbitRadius_;
}

float CombatSimulator::OrbitState::transversalVelocity() const {
	float Va = attackerVelocity();
	float Vt = targetVelocity();
	return Va > Vt ? std::sqrt(Va * Va - Vt * Vt) : 0;
}

float CombatSimulator::OrbitState::angularVelocity() const {
	float r = range();
	return r > 0 ? transversalVelocity() / r : 0;
}

float CombatSimulator::OrbitState::targetVelocity() const {
	return target_->getVelocity();
}

float CombatSimulator::OrbitState::attackerVelocity() const {
	auto g = target_->getEngine()->getGeneration();
	if (g != generation_ || calculatedAttackerVelocity_ < 0) {
		calculatedAttackerVelocity_ = std::min(attacker_->getMaxVelocityInOrbit(orbitRadius_), attackerVelocity_);
		generation_ = g;
	}
	return calculatedAttackerVelocity_;
}

CombatSimulator::KeepAtRangeState::KeepAtRangeState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, float range) : State(attacker, target), range_(range) {
}

void CombatSimulator::KeepAtRangeState::setRange(float range) {
	range_ = range;
}

float CombatSimulator::KeepAtRangeState::range() const {
	return range_;
}

float CombatSimulator::KeepAtRangeState::transversalVelocity() const {
	return 0;
}

float CombatSimulator::KeepAtRangeState::angularVelocity() const {
	return 0;
}

float CombatSimulator::KeepAtRangeState::targetVelocity() const {
	return target_->getVelocity();
}

float CombatSimulator::KeepAtRangeState::attackerVelocity() const {
	return std::min(attacker_->getVelocity(), targetVelocity());
}

CombatSimulator::ManualState::ManualState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, float range, float attackerVelocity, float targetVelocity) : State(attacker, target), targetPosition(0, 0),  attackerPosition(range, 0),  attackerVelocityVector(0, attackerVelocity), targetVelocityVector(0, targetVelocity) {
}

float CombatSimulator::ManualState::range() const {
	return (attackerPosition - targetPosition).length();
}

float CombatSimulator::ManualState::transversalVelocity() const {
	if (targetPosition == attackerPosition)
		return 0;
	
	Vector dv = targetVelocityVector - attackerVelocityVector;
	float l = dv.length();
	if (l == 0)
		return 0;
	
	float pr = (attackerPosition - targetPosition).project(dv);
	return std::sqrt(l * l - pr * pr);
}

float CombatSimulator::ManualState::angularVelocity() const {
	float r = range();
	return r > 0 ? transversalVelocity() / r : 0;
}

float CombatSimulator::ManualState::targetVelocity() const {
	return targetVelocityVector.length();
}

float CombatSimulator::ManualState::attackerVelocity() const {
	return attackerVelocityVector.length();
}


CombatSimulator::CombatSimulator(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target): attacker_(attacker), target_(target) {
	auto engine = attacker->getEngine();
	engine->beginUpdates();
	auto analyze = [&](std::shared_ptr<Ship> attacker, std::shared_ptr<Ship> target, ModulesList& modulesList) {
		for (const auto& module: attacker->getModules()) {
			auto state = module->getPreferredState();
			if (state == Module::STATE_UNKNOWN)
				state = module->getState();
			
			states_[module] = state;
			targets_[module] = module->getTarget();
			
			if (module->getState() > Module::STATE_ONLINE && module->requireTarget()) {
				if (module->isOffensive()) {
					module->setTarget(target);
					if (module->getDps() == 0) {
						preferredStates_[module] = state;
						modulesList.push_back(module);
						module->setPreferredState(Module::STATE_ONLINE);
					}
				}
				else
					module->setPreferredState(Module::STATE_ONLINE);
			}
		}
		for (const auto& drone: attacker->getDrones()) {
			if (drone->isActive() && drone->isOffensive() && !drone->isAssistance()) {
				targets_[drone] = drone->getTarget();
				drone->setTarget(target);
			}
		}
	};
	
	analyze(attacker, target, attackerOffensiveModules_);
	analyze(target, attacker, targetOffensiveModules_);
	engine->commitUpdates();
}

CombatSimulator::~CombatSimulator() {
	auto engine = attacker_->getEngine();
	engine->beginUpdates();

	for (const auto& module: attacker_->getModules()) {
		module->setTarget(targets_[module]);
		module->setPreferredState(states_[module]);
	}
	for (const auto& module: target_->getModules()) {
		module->setTarget(targets_[module]);
		module->setPreferredState(states_[module]);
	}
	for (const auto& drone: attacker_->getDrones()) {
		if (drone->isActive() && drone->isOffensive() && !drone->isAssistance()) {
			drone->setTarget(targets_[drone]);
		}
	}
	for (const auto& drone: target_->getDrones()) {
		if (drone->isActive() && drone->isOffensive() && !drone->isAssistance()) {
			drone->setTarget(targets_[drone]);
		}
	}
	engine->commitUpdates();
}

void CombatSimulator::setState(const State& state) {
	float range = state.range();
	auto engine = attacker_->getEngine();
	engine->beginUpdates();
	for (const auto& module: attackerOffensiveModules_) {
		float maxRange = module->getMaxRange();
		float falloff = module->getFalloff();
		module->setPreferredState(range > (maxRange + falloff * 2) ? Module::STATE_ONLINE : preferredStates_[module]);
	}
	for (const auto& module: targetOffensiveModules_) {
		float maxRange = module->getMaxRange();
		float falloff = module->getFalloff();
		module->setPreferredState(range > (maxRange + falloff * 2) ? Module::STATE_ONLINE : preferredStates_[module]);
	}
	engine->commitUpdates();

	float targetVelocity = state.targetVelocity();
	float attackerVelocity = state.attackerVelocity();
	float angularVelocity = state.angularVelocity();
	
	attackersHostileTarget_ = HostileTarget(range, angularVelocity, target_->getSignatureRadius(), targetVelocity);
	targetsHostileTarget_ = HostileTarget(range, angularVelocity,  attacker_->getSignatureRadius(), attackerVelocity);
}

DamageVector CombatSimulator::outgoingDps() {
	return attacker_->getWeaponDps(attackersHostileTarget_) + attacker_->getDroneDps(attackersHostileTarget_);
}

DamageVector CombatSimulator::incomingDps() {
	return target_->getWeaponDps(targetsHostileTarget_) + target_->getDroneDps(targetsHostileTarget_);
}

float CombatSimulator::timeToKill() {
	auto vdps = outgoingDps();
	float dps = vdps;
	DamagePattern pattern(dps);
	auto resistances = target_->getResistances();
	auto ehp = pattern.effectiveHitPoints(resistances, target_->getHitPoints());
	auto etank = pattern.effectiveTank(resistances, target_->getTank());
	
	auto shieldDPS = dps - (etank.passiveShield + etank.shieldRepair);
	auto armorDPS = shieldDPS - etank.armorRepair;
	auto hullDPS = armorDPS - etank.hullRepair;
	if (shieldDPS > 0 && armorDPS > 0 && hullDPS > 0)
		return ehp.shield / shieldDPS + ehp.armor / armorDPS + ehp.hull / hullDPS;
	else
		return std::numeric_limits<float>::infinity();
}

float CombatSimulator::timeToDie() {
	auto vdps = incomingDps();
	float dps = vdps;
	DamagePattern pattern(dps);
	auto resistances = attacker_->getResistances();
	auto ehp = pattern.effectiveHitPoints(resistances, attacker_->getHitPoints());
	auto etank = pattern.effectiveTank(resistances, attacker_->getTank());
	
	auto shieldDPS = dps - (etank.passiveShield + etank.shieldRepair);
	auto armorDPS = shieldDPS - etank.armorRepair;
	auto hullDPS = armorDPS - etank.hullRepair;
	if (shieldDPS > 0 && armorDPS > 0 && hullDPS > 0)
		return ehp.shield / shieldDPS + ehp.armor / armorDPS + ehp.hull / hullDPS;
	else
		return std::numeric_limits<float>::infinity();
}

float CombatSimulator::attackerModulesLifeTime() {
	float lifeTime = std::numeric_limits<float>::infinity();
	for (const auto& module: attacker_->getModules()) {
		float v = module->getLifeTime();
		if (v > 0)
			lifeTime = std::min(lifeTime, v);
	}
	return lifeTime;
}

float CombatSimulator::targetModulesLifeTime() {
	float lifeTime = std::numeric_limits<float>::infinity();
	for (const auto& module: target_->getModules()) {
		float v = module->getLifeTime();
		if (v > 0)
			lifeTime = std::min(lifeTime, v);
	}
	return lifeTime;
}
