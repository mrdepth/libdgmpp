//
//  Capacitor.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 17.11.2017.
//

#include "Capacitor.hpp"
#include "Ship.hpp"
#include <numeric>

namespace dgmpp2 {
	
	using namespace std::chrono_literals;
	
	GigaJoule Capacitor::capacity() {
		return owner_[AttributeID::capacitorCapacity]->value();
	}
	
	std::chrono::milliseconds Capacitor::rechargeTime() {
		return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(owner_[AttributeID::rechargeRate]->value()));
	}
	
	std::chrono::milliseconds Capacitor::lastsTime() {
		return isStable() ? std::chrono::milliseconds::max() : simulationEndTime_;
	}

	bool Capacitor::isStable() {
		return stableLevel() > 0;
	}
	
	Percent Capacitor::stableLevel() {
		if (!flags_.isCalculated_)
			simulate();
		return stableLevel_;
	}
	
	rate<GigaJoule, std::chrono::milliseconds> Capacitor::use() {
		if (!flags_.isCalculated_)
			simulate();
		return use_;
	}
	
	rate<GigaJoule, std::chrono::milliseconds> Capacitor::recharge() {
		if (!flags_.isCalculated_)
			simulate();
		return recharge_;
	}

	void Capacitor::prepare() {

		std::list<Module*> modules;
		std::list<Drone*> drones;
		
		for (const auto& i: owner_.modules()) {
			auto m = std::get<std::unique_ptr<Module>>(i).get();
			if (m->state() >= Module::State::active)
				modules.push_back(m);
		}

		std::copy_if(owner_.projectedModules().begin(), owner_.projectedModules().end(), std::back_inserter(modules), [](auto i) {
			return i->state() >= Module::State::active;
		});

		std::copy_if(owner_.projectedDrones().begin(), owner_.projectedDrones().end(), std::back_inserter(drones), [](auto i) {
			return i->active() && (*i)[EffectID::entityEnergyNeutralizerFalloff] != nullptr;
		});

		for (const auto& i: owner_.modules()) {
			if (std::get<std::unique_ptr<Module>>(i)->state() < Module::State::active)
				continue;
		}
		
		decltype(states_)::container_type states;
		states.reserve(modules.size() + drones.size());
		
		capacity_ = capacity();
		rechargeTime_ = rechargeTime();
		recharge_ = make_rate(10.0 * config::capacitorPeakRecharge * (1.0 - config::capacitorPeakRecharge) * capacity_, rechargeTime_);
		
		use_ = decltype(use_)(0);
		period_ = 1ms;
		
		auto isDisallowedOffense = owner_.isDisallowedOffense();
		auto isDisallowedAssistance = owner_.isDisallowedAssistance();
		auto disablePeriod = false;

		for (auto module: modules) {
			decltype(period_) cycleTime {module->cycleTime()};
			period_ = decltype(period_)(std::lcm(period_.count(), cycleTime.count()));

			auto isProjected = module->parent() != &owner_;
			GigaJoule capNeed;
			
			if (isProjected) {
				GigaJoule value = 0;
				if ((*module)[EffectID::energyNosferatuFalloff])
					value = (*module)[AttributeID::powerTransferAmount]->value();
				else if ((*module)[EffectID::energyNeutralizerFalloff])
					value = (*module)[AttributeID::energyNeutralizerAmount]->value();
				else if ((*module)[EffectID::shipModuleRemoteCapacitorTransmitter])
					value = (*module)[AttributeID::powerTransferAmount]->value();
				
				if ((value > 0 && !isDisallowedAssistance) || (value < 0 && !isDisallowedOffense))
					capNeed = value;
				else
					continue;
			}
			else
				capNeed = module->capUse() * cycleTime;
			
			auto clipSize = module->shots();
			
			if (capNeed > 0) {
				use_ += make_rate(capNeed, cycleTime);
				if (!flags_.factorReload)
					clipSize = 0;
			}
			else if (capNeed < 0)
				recharge_ -= make_rate(capNeed, cycleTime);
			else
				continue;

			if (clipSize > 0)
				disablePeriod = true;
			
			
			
			std::chrono::milliseconds reactivationTime(0);
			if (auto attribute = (*module)[AttributeID::moduleReactivationDelay])
				reactivationTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value()));
			states.emplace_back(module->rawCycleTime() + reactivationTime, capNeed, clipSize);
		}
		
		for (auto drone: drones) {
			decltype(period_) cycleTime {drone->cycleTime()};
			auto capNeed = static_cast<GigaJoule>((*drone)[AttributeID::energyNeutralizerAmount]->value());

			if ((capNeed > 0 && !isDisallowedAssistance) || (capNeed < 0 && !isDisallowedOffense)) {
				use_ += make_rate(capNeed, cycleTime);
				period_ = decltype(period_)(std::lcm(period_.count(), cycleTime.count()));
				states.emplace_back(cycleTime, capNeed, 0);
			}
		}
		if (disablePeriod)
			period_ = config::capacitorSimulationMaxTime;
		
		
		
//		auto averageDrain = std::accumulate(states.begin(), states.end(), rate<GigaJoule, std::chrono::seconds>(0), [](auto a, const auto& b) {
//			return make_rate(b.capNeed, b.duration);
//		});
		
//		const auto tau = capacitorRechargeRate_.count() / 5.0;
//		Float a = - (2.0 * averageDrain.count() * tau - capacitorCapacity_) / capacitorCapacity_;
//		if (a < 0.0)
//			capStableEVE_ = 0;
//		else {
//			Float t = (1.0 + std::sqrt(a));
//			capStableEVE_ = 0.25 * t * t;
//		}

		states_ = decltype(states_)(decltype(states_)::value_compare(), std::move(states));

	}

	
	void Capacitor::simulate() {
		prepare();
		if (states_.empty()) {
			stableLevel_ = 1.0;
			simulationEndTime_ = 0ms;
		}
		else {
			const auto tau = rechargeTime_.count() / 5.0;
			auto capWrap = capacity_;
			auto capLowest = capacity_;
			auto capLowestPre = capacity_;
			auto cap = capacity_;
			auto tWrap = period_;
			auto tNow = 0ms;
			auto tLast = 0ms;
			
			while(true) {
				auto state = states_.top();
				states_.pop();

				tNow = state.tNow;
				if (tNow > config::capacitorSimulationMaxTime)
					break;
				
				auto s = ((1.0 + (std::sqrt(cap / capacity_) - 1.0) * std::exp((tLast.count() - tNow.count()) / tau)));
				cap = s * s * capacity_;
				
				if (tNow != tLast) {
					if (cap < capLowestPre)
						capLowestPre = cap;
					if (tNow == tWrap) {
						if (cap >= capWrap)
							break;
						capWrap = cap;
						tWrap += period_;
					}
				}
				
				cap -= state.capNeed;
				cap = std::min(cap, capacity_);

				tLast = tNow;
				
				if (cap < capLowest) {
					if (cap < 0.0)
						break;
					capLowest = cap;
				}
				
				tNow += state.duration;
				state.shot++;
				
				if (state.clipSize > 0) {
					if (state.shot % state.clipSize == 0) {
						state.shot = 0;
						tNow += 10s;
					}
				}
				state.tNow = tNow;
				states_.push(state);
			}
			
			simulationEndTime_ = tLast;
			if (cap > 0.0)
				stableLevel_ = std::min((capLowest + capLowestPre) / (2 * capacity_), 1.0);
			else
				stableLevel_ = 0;

		}
		flags_.isCalculated_ = true;
	}
	
}
