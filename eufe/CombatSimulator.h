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
		struct State {
			Point attackerPosition;
			Point targetPosition;
			Vector attackerVelocity;
			Vector targetVelocity;

			float range() const;
			float transversalVelocity() const;
			float angularVelocity() const;
		};
		
		CombatSimulator(std::shared_ptr<Ship> attacker, std::shared_ptr<Ship> target);
		virtual ~CombatSimulator();
		
		void setState(const State& state);
		DamageVector dealtDPS();
		DamageVector receivedDPS();
	private:
		std::shared_ptr<Ship> attacker_;
		std::shared_ptr<Ship> target_;
		ModulesList attackerOffensiveModules_;
		ModulesList targetOffensiveModules_;
		State state_;
		std::map<std::shared_ptr<Module>, Module::State> states_;
		std::map<std::shared_ptr<Module>, std::shared_ptr<Ship>> targets_;
		
	};
}