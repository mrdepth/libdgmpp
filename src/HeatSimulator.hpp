//
//  HeatSimulator.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 07.12.2017.
//

#pragma once
#include "Type.hpp"
#include "Module.hpp"

namespace dgmpp {
	using namespace std::chrono_literals;
	
	class Ship;
	
	class HeatSimulator {
	public:
		void simulate();
		
	private:
		friend class Ship;
		Ship& owner_;
		
		struct State {
			std::chrono::milliseconds tNow = 0ms;
			std::chrono::milliseconds cycleTime = 0ms;
			std::chrono::milliseconds reloadTime = 0ms;
			HP heatDamage = 0;
			std::size_t shot = 0;
			std::size_t clipSize = 0;
			Module::Socket socket = 0;
			
			State (std::chrono::milliseconds cycleTime, std::chrono::milliseconds reloadTime, HP heatDamage, std::size_t clipSize, Module::Socket socket)
			: cycleTime(cycleTime), reloadTime(reloadTime), heatDamage(heatDamage), clipSize(clipSize), socket(socket) {}
			
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
		Float heatGenerationMultiplier_;
		
		HeatSimulator(Ship& owner) : owner_(owner) {
			flags_.isCalculated_ = false;
		}
		
		void reset_() { flags_.isCalculated_ = false; }
		void run_ (Module::Slot slot);
		
		bool factorReload_() const noexcept;

	};
}

