#pragma once
#include "types.h"
#include <cmath>
#include "DamageVector.h"
#include "Ship.h"

namespace eufe {
	struct Vector;

	struct Point {
		float x, y;
		Point() : x(0), y(0) {};
		Point(float x, float y):x(x), y(y) {};
		Vector operator-(const Point& p) const;
		bool operator == (const Point& p) const;
	};
	
	struct Vector {
		float dx, dy;
		Vector() : dx(0), dy(0) {};
		Vector(float dx, float dy):dx(dx), dy(dy) {};
		float length() const;
		float project(const Vector& v);
		float dotProduct(const Vector& v);
		Vector operator+(const Vector& v) const;
		Vector operator-(const Vector& v) const;
		Vector operator*(float v) const;
		Vector operator/(float v) const;
	};

	class CombatSimulator {
	public:
		class State {
		public:
			State(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target);
			virtual float range() const = 0;
			virtual float transversalVelocity() const = 0;
			virtual float angularVelocity() const = 0;
			virtual float targetVelocity() const = 0;
			virtual float attackerVelocity() const = 0;
		protected:
			std::shared_ptr<Ship> attacker_;
			std::shared_ptr<Ship> target_;
		};
		
		class OrbitState: public State {
		public:
			OrbitState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, float orbitRadius, float attackerVelocity);
			void setOrbitRadius(float orbitRadius);
			virtual float range() const;
			virtual float transversalVelocity() const;
			virtual float angularVelocity() const;
			virtual float targetVelocity() const;
			virtual float attackerVelocity() const;
		private:
			float orbitRadius_;
			float attackerVelocity_;
			mutable float calculatedAttackerVelocity_;
			mutable uint32_t generation_;
		};
		
		class KeepAtRangeState: public State {
		public:
			KeepAtRangeState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, float range);
			void setRange(float range);
			virtual float range() const;
			virtual float transversalVelocity() const;
			virtual float angularVelocity() const;
			virtual float targetVelocity() const;
			virtual float attackerVelocity() const;
		private:
			float range_;
		};
		
		class ManualState: public State {
		public:
			ManualState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, float range = 0, float attackerVelocity = 0, float targetVelocity = 0);
			Point attackerPosition;
			Point targetPosition;
			Vector attackerVelocityVector;
			Vector targetVelocityVector;
			virtual float range() const;
			virtual float transversalVelocity() const;
			virtual float angularVelocity() const;
			virtual float targetVelocity() const;
			virtual float attackerVelocity() const;
		};
		
		
		CombatSimulator(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target);
		virtual ~CombatSimulator();
		
		void setState(const State& state);
		DamageVector outgoingDps();
		DamageVector incomingDps();
		float timeToKill();
		float timeToDie();
		float attackerModulesLifeTime();
		float targetModulesLifeTime();
	private:
		std::shared_ptr<Ship> attacker_;
		std::shared_ptr<Ship> target_;
		ModulesList attackerOffensiveModules_;
		ModulesList targetOffensiveModules_;
		std::map<std::shared_ptr<Module>, Module::State> states_;
		std::map<std::shared_ptr<Item>, std::shared_ptr<Ship>> targets_;
		HostileTarget attackersHostileTarget_;
		HostileTarget targetsHostileTarget_;
		std::map<std::shared_ptr<Module>, Module::State> preferredStates_;
	};
}