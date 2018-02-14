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

namespace dgmpp {
	using namespace std::chrono_literals;

	class Ship;
	class Module;
	
	class Capacitor {
	public:
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
			std::size_t shot = 0;
			std::size_t clipSize = 0;
			
			State() {}
			State(std::chrono::milliseconds duration, GigaJoule capNeed, std::size_t clipSize)
			: duration(duration), capNeed(capNeed), clipSize(clipSize) {}
			

			bool operator< (const State& other) const noexcept {
				return tNow < other.tNow;
			}
			bool operator<= (const State& other) const noexcept {
				return tNow <= other.tNow;
			}
			bool operator> (const State& other) const noexcept {
				return tNow > other.tNow;
			}
			bool operator>= (const State& other) const noexcept {
				return tNow >= other.tNow;
			}
			bool operator== (const State& other) const noexcept {
				return tNow == other.tNow;
			}
		};
		
		struct {
			bool isCalculated_: 1;
		} flags_;
		GigaJoule capacityValue_;
		std::chrono::milliseconds rechargeTimeValue_;
		rate<GigaJoule, std::chrono::milliseconds> useValue_;
		rate<GigaJoule, std::chrono::milliseconds> rechargeValue_;
		std::priority_queue<State, std::vector<State>, std::greater<>> states_;
		std::chrono::milliseconds period_;
		std::chrono::milliseconds simulationEndTime_;
		Percent stableLevelValue_;
		
		Capacitor(Ship& owner) : owner_(owner) {
			flags_.isCalculated_ = false;
		}
		
		void reset_() noexcept { flags_.isCalculated_ = false; }
		void prepare_();
		void simulate_();
		
		bool factorReload_() const noexcept;

		
		GigaJoule capacity_();
		std::chrono::milliseconds rechargeTime_();
		std::chrono::milliseconds lastsTime_();
		bool isStable_();
		Percent stableLevel_();
		GigaJoulePerSecond use_();
		GigaJoulePerSecond recharge_();

	};
}
