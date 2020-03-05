//
//  Capacitor.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 17.11.2017.
//

#include "Capacitor.hpp"
#include "Ship.hpp"
#include <numeric>

namespace dgmpp {
	
	using namespace std::chrono_literals;
	
	GigaJoule Capacitor::capacity() {
		LOCK(&owner_);
		return capacity_();
	}
	
	std::chrono::milliseconds Capacitor::rechargeTime() {
		LOCK(&owner_);
		return rechargeTime_();
	}
	
	std::chrono::milliseconds Capacitor::lastsTime() {
		LOCK(&owner_);
		return lastsTime_();
	}
	
	bool Capacitor::isStable() {
		LOCK(&owner_);
		return isStable_();
	}
	
	Percent Capacitor::stableLevel() {
		LOCK(&owner_);
		return stableLevel_();
	}
	
	GigaJoulePerSecond Capacitor::use() {
		LOCK(&owner_);
		return use_();
	}
	
	GigaJoulePerSecond Capacitor::recharge() {
		LOCK(&owner_);
		return recharge_();
	}

	
	GigaJoule Capacitor::capacity_() {
		return owner_.attribute_(AttributeID::capacitorCapacity)->value_();
	}
	
	std::chrono::milliseconds Capacitor::rechargeTime_() {
		return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(owner_.attribute_(AttributeID::rechargeRate)->value_()));
	}
	
	std::chrono::milliseconds Capacitor::lastsTime_() {
		return isStable_() ? std::chrono::milliseconds::max() : simulationEndTime_;
	}

	bool Capacitor::isStable_() {
		return stableLevel_() > 0;
	}
	
	Percent Capacitor::stableLevel_() {
		if (!flags_.isCalculated_)
			simulate_();
		return stableLevelValue_;
	}
	
	GigaJoulePerSecond Capacitor::use_() {
		if (!flags_.isCalculated_)
			simulate_();
		return useValue_;
	}
	
	GigaJoulePerSecond Capacitor::recharge_() {
		if (!flags_.isCalculated_)
			simulate_();
		return rechargeValue_;
	}

	void Capacitor::prepare_() {

		std::list<Module*> modules;
		std::list<Drone*> drones;
		
		for (const auto& i: owner_.modulesSet_) {
			auto m = std::get<std::unique_ptr<Module>>(i).get();
			if (m->state_() >= Module::State::active)
				modules.push_back(m);
		}

		std::copy_if(owner_.projectedModules_.begin(), owner_.projectedModules_.end(), std::back_inserter(modules), [](auto i) {
			return i->state_() >= Module::State::active;
		});

		std::copy_if(owner_.projectedDrones_.begin(), owner_.projectedDrones_.end(), std::back_inserter(drones), [](auto i) {
			return i->active_() && i->effect_(EffectID::entityEnergyNeutralizerFalloff) != nullptr;
		});

		decltype(states_)::container_type states;
		states.reserve(modules.size() + drones.size());
		
		capacityValue_ = capacity_();
		rechargeTimeValue_ = rechargeTime_();
		rechargeValue_ = make_rate(10.0 * config::capacitorPeakRecharge * (1.0 - config::capacitorPeakRecharge) * capacityValue_, rechargeTimeValue_);
		
		useValue_ = decltype(useValue_)(0.0);
		period_ = 1ms;
		
		auto isDisallowedOffense = owner_.isDisallowedOffense_();
		auto isDisallowedAssistance = owner_.isDisallowedAssistance_();
		auto disablePeriod = false;
		auto factorReload = factorReload_();

		for (auto module: modules) {
			decltype(period_) cycleTime {module->cycleTime_()};
			period_ = decltype(period_)(std::lcm(period_.count(), cycleTime.count()));

			auto isProjected = module->parent_() != &owner_;
			GigaJoule capNeed;
			
			if (isProjected) {
				GigaJoule value = 0;
				if (module->effect_(EffectID::energyNosferatuFalloff))
					value = module->attribute_(AttributeID::powerTransferAmount)->value_();
				else if (module->effect_(EffectID::energyNeutralizerFalloff))
					value = module->attribute_(AttributeID::energyNeutralizerAmount)->value_();
				else if (module->effect_(EffectID::shipModuleRemoteCapacitorTransmitter))
					value = -module->attribute_(AttributeID::powerTransferAmount)->value_();
				
				if ((value > 0 && !isDisallowedOffense) || (value < 0 && !isDisallowedAssistance))
					capNeed = value;
				else
					continue;
			}
			else
				capNeed = module->capUse_() * cycleTime;
			
			auto clipSize = module->shots_();

			if (capNeed > 0) {
				useValue_ += make_rate(capNeed, cycleTime);
				if (!factorReload)
					clipSize = 0;
			}
			else if (capNeed < 0)
				rechargeValue_ -= make_rate(capNeed, cycleTime);
			else
				continue;

			if (clipSize > 0)
				disablePeriod = true;
			
			
			
			std::chrono::milliseconds reactivationTime(0);
			if (auto attribute = module->attribute_(AttributeID::moduleReactivationDelay))
				reactivationTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
			states.emplace_back(module->rawCycleTime_() + reactivationTime, capNeed, clipSize);
		}
		
		for (auto drone: drones) {
			decltype(period_) cycleTime {drone->cycleTime_()};
			auto capNeed = static_cast<GigaJoule>(drone->attribute_(AttributeID::energyNeutralizerAmount)->value_());

			if ((capNeed > 0 && !isDisallowedAssistance) || (capNeed < 0 && !isDisallowedOffense)) {
				useValue_ += make_rate(capNeed, cycleTime);
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

	
	void Capacitor::simulate_() {
		prepare_();
		if (states_.empty()) {
			stableLevelValue_ = 1.0;
			simulationEndTime_ = 0ms;
		}
		else {
			const auto tau = rechargeTimeValue_.count() / 5.0;
			auto capWrap = capacityValue_;
			auto capLowest = capacityValue_;
			auto capLowestPre = capacityValue_;
			auto cap = capacityValue_;
			auto tWrap = period_;
			auto tNow = 0ms;
			auto tLast = 0ms;
			
			while(true) {
				auto state = states_.top();
				states_.pop();

				tNow = state.tNow;
				if (tNow > config::capacitorSimulationMaxTime)
					break;
				
				auto s = ((1.0 + (std::sqrt(cap / capacityValue_) - 1.0) * std::exp((tLast.count() - tNow.count()) / tau)));
				cap = std::pow(s, 2) * capacityValue_;
				
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
				cap = std::min(cap, capacityValue_);

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
				stableLevelValue_ = std::min((capLowest + capLowestPre) / (2 * capacityValue_), 1.0);
			else
				stableLevelValue_ = 0;

		}
		flags_.isCalculated_ = true;
	}

	bool Capacitor::factorReload_() const noexcept {
		return owner_.factorReload_();
	}

}
