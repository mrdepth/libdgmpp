//
//  Capacitor.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 17.11.2017.
//

#pragma once
#include "Type.hpp"
#include <queue>
#include <functional>

namespace dgmpp2 {
	using namespace std::chrono_literals;

	class Ship;
	class Module;
	
	class Capacitor {
	public:
		bool factorReload() const { return flags_.factorReload; }
		void factorReload (bool factorReload) { flags_.factorReload = factorReload; }

		GigaJoule capacity();
		std::chrono::milliseconds rechargeTime();
		std::chrono::milliseconds lastsTime();
		bool isStable();
		Percent stableLevel();
		GigaJoulePerSecond use();
		GigaJoulePerSecond recharge();
	private:
		friend class Ship;
		Ship& owner_;
		
		struct State {
			std::chrono::milliseconds tNow = 0ms;
			std::chrono::milliseconds duration = 0ms;
			GigaJoule capNeed = 0;
			size_t shot = 0;
			size_t clipSize = 0;
			
			State() {}
			State(std::chrono::milliseconds duration, GigaJoule capNeed, size_t clipSize)
			: duration(duration), capNeed(capNeed), clipSize(clipSize) {}
			

//			std::chrono::milliseconds reloadTime = std::chrono::milliseconds::zero();
//			std::chrono::milliseconds reactivationTime = std::chrono::milliseconds::zero();

			
			bool operator< (const State& other) {
				return tNow < other.tNow;
			}
			bool operator<= (const State& other) {
				return tNow <= other.tNow;
			}
			bool operator> (const State& other) {
				return tNow > other.tNow;
			}
			bool operator>= (const State& other) {
				return tNow >= other.tNow;
			}
			bool operator== (const State& other) {
				return tNow == other.tNow;
			}
		};
		
		struct {
			bool factorReload: 1;
			bool isCalculated_: 1;
		} flags_;
		GigaJoule capacity_;
		std::chrono::milliseconds rechargeTime_;
		rate<GigaJoule, std::chrono::milliseconds> use_;
		rate<GigaJoule, std::chrono::milliseconds> recharge_;
		std::priority_queue<State, std::vector<State>, std::greater<>> states_;
		std::chrono::milliseconds period_;
		std::chrono::milliseconds simulationEndTime_;
		Percent stableLevel_;
		
		Capacitor(Ship& owner) : owner_(owner) {
			flags_.factorReload = false;
			flags_.isCalculated_ = false;
		}
		
		void reset() { flags_.isCalculated_ = false; }
		void prepare();
		void simulate();
	};
}
