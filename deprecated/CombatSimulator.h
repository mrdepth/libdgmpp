#pragma once
#include "types.h"
#include <cmath>
#include "DamageVector.h"
#include "Ship.h"

namespace dgmpp {
	struct Vector;

	struct Point {
		Float x, y;
		Point() : x(0), y(0) {};
		Point(Float x, Float y):x(x), y(y) {};
		Vector operator-(const Point& p) const;
		bool operator == (const Point& p) const;
	};
	
	struct Vector {
		Float dx, dy;
		Vector() : dx(0), dy(0) {};
		Vector(Float dx, Float dy):dx(dx), dy(dy) {};
		Float length() const;
		Float project(const Vector& v);
		Float dotProduct(const Vector& v);
		Vector operator+(const Vector& v) const;
		Vector operator-(const Vector& v) const;
		Vector operator*(Float v) const;
		Vector operator/(Float v) const;
	};

	class CombatSimulator {
	public:
		class State {
		public:
			State(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target);
			virtual Float range() const = 0;
			virtual Float transversalVelocity() const = 0;
			virtual Float angularVelocity() const = 0;
			virtual Float targetVelocity() const = 0;
			virtual Float attackerVelocity() const = 0;
		protected:
			std::shared_ptr<Ship> attacker_;
			std::shared_ptr<Ship> target_;
		};
		
		class OrbitState: public State {
		public:
			OrbitState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, Float orbitRadius, Float attackerVelocity);
			void setOrbitRadius(Float orbitRadius);
			virtual Float range() const;
			virtual Float transversalVelocity() const;
			virtual Float angularVelocity() const;
			virtual Float targetVelocity() const;
			virtual Float attackerVelocity() const;
		private:
			Float orbitRadius_;
			Float attackerVelocity_;
			mutable Float calculatedAttackerVelocity_;
			mutable uint32_t generation_;
		};
		
		class KeepAtRangeState: public State {
		public:
			KeepAtRangeState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, Float range);
			void setRange(Float range);
			virtual Float range() const;
			virtual Float transversalVelocity() const;
			virtual Float angularVelocity() const;
			virtual Float targetVelocity() const;
			virtual Float attackerVelocity() const;
		private:
			Float range_;
		};
		
		class ManualState: public State {
		public:
			ManualState(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target, Float range = 0, Float attackerVelocity = 0, Float targetVelocity = 0);
			Point attackerPosition;
			Point targetPosition;
			Vector attackerVelocityVector;
			Vector targetVelocityVector;
			virtual Float range() const;
			virtual Float transversalVelocity() const;
			virtual Float angularVelocity() const;
			virtual Float targetVelocity() const;
			virtual Float attackerVelocity() const;
		};
		
		
		CombatSimulator(std::shared_ptr<Ship> const& attacker, std::shared_ptr<Ship> const& target);
		virtual ~CombatSimulator();
		
		void setState(const State& state);
		DamageVector outgoingDps();
		DamageVector incomingDps();
		Float timeToKill();
		Float timeToDie();
		Float attackerModulesLifeTime();
		Float targetModulesLifeTime();
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
