#include "CombatSimulator.h"
#include "Ship.h"
#include "Engine.h"
#include <limits>

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

CombatSimulator::State::State() {
	
}

CombatSimulator::State::State(float range, float attackerVelocity, float targetVelocity): targetPosition(0, 0),  attackerPosition(range, 0),  attackerVelocity(0, attackerVelocity), targetVelocity(0, targetVelocity) {
}

float CombatSimulator::State::range() const {
	return (attackerPosition - targetPosition).length();
}

float CombatSimulator::State::transversalVelocity() const {
	if (targetPosition == attackerPosition)
		return 0;
	
	Vector dv = targetVelocity - attackerVelocity;
	float l = dv.length();
	if (l == 0)
		return 0;
	
	float pr = (attackerPosition - targetPosition).project(dv);
	return sqrt(l * l - pr * pr);
}

float CombatSimulator::State::angularVelocity() const {
	float r = range();
	return r > 0 ? transversalVelocity() / r : 0;
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
						preferredStates_[module] = module->getPreferredState();
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
	state_ = state;
	float range = state.range();
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
	
	float v0 = state.attackerVelocity.length();
	float v1 = attacker_->getMaxVelocityInOrbit(range);
	
	if (v1 < v0)
		state_.attackerVelocity = state_.attackerVelocity * (v1 / v0);
	
	v0 = state.targetVelocity.length();
	v1 = target_->getMaxVelocityInOrbit(range);
	if (v1 < v0)
		state_.targetVelocity = state_.targetVelocity * (v1 / v0);

	float angularVelocity = state_.angularVelocity();
	attackersHostileTarget_ = HostileTarget(range, angularVelocity, target_->getSignatureRadius(), state_.targetVelocity.length());
	targetsHostileTarget_ = HostileTarget(range, angularVelocity,  attacker_->getSignatureRadius(), state_.attackerVelocity.length());
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
