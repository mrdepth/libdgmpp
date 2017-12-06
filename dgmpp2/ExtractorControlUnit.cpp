//
//  ExtractorControlUnit.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "ExtractorControlUnit.hpp"
#include "SDE.hpp"

namespace dgmpp2 {
	
	bool ExtractorControlUnit::configured() const {
		return launchTime_ < expiryTime_ && installTime_ < expiryTime_ && output() && cycleTime_.count() > 0;
	}

	std::optional<Commodity> ExtractorControlUnit::output() const {
		if (!outputs_.empty())
			return outputs_.begin()->commodity;
		else
			return std::nullopt;
	}
	
	std::optional<Commodity> ExtractorControlUnit::yieldAt(std::chrono::seconds time) const {
		auto product = *output();

		if (time >= expiryTime_ || time < installTime_)
			product = 0;
		else {
			auto cycleIndex = std::trunc((time - installTime_) / cycleTime_);
			auto t = (cycleIndex + 0.5) * w_.count();
			
			static auto decayFactor = SDE::get(AttributeID::ecuDecayFactor).defaultValue;
			static auto noiseFactor = SDE::get(AttributeID::ecuNoiseFactor).defaultValue;
			
			constexpr auto f1 = 1.0 / 12.0;
			constexpr auto f2 = 1.0 / 5.0;
			constexpr auto f3 = 1.0 / 2.0;
			
			auto decay = quantityPerCycle_ / (1.0 + t * decayFactor);
			auto sina = std::cos(phaseShift_ + t * f1);
			auto sinb = std::cos(phaseShift_ / 2 + t * f2);
			auto sinc = std::cos(t * f3);
			auto sins = std::max((sina + sinb + sinc) / 3.0, 0.0);
			auto h = decay * (1 + noiseFactor * sins);
			auto yield = w_.count() * h;
			product = std::trunc(yield);
		}
		
		return product;
	}
	
	std::optional<std::chrono::seconds> ExtractorControlUnit::nextUpdateTime() const {
		if (!cycles_.empty()) {
			if (extraction_)
				return extraction_->end();
			else
				return std::nullopt;
		}
		else
			return std::max(launchTime_, installTime_);
	}
	
	void ExtractorControlUnit::update(std::chrono::seconds time) {
		if (updating_ || !configured())
			return;
		updating_ = true;
		
		if (cycles_.empty()) {
			if (auto cycle = startCycle(time)) {
				extraction_ = cycle;
				states_.emplace_back(new ProductionState(time, cycle, percentage(totalYield_, totalYield_ + totalWaste_)));
			}
		}
		else if (extraction_) {
			auto& cycle = *extraction_;
			const auto isCycleFinished = cycle.end() == time;
			
			if (isCycleFinished) {
				finishCycle(cycle, time);
				extraction_ = startCycle(time);
				states_.emplace_back(new ProductionState(time, extraction_, percentage(totalYield_, totalYield_ + totalWaste_)));
			}
		}
		
		updating_ = false;
	}
	
	void ExtractorControlUnit::finishCycle(ProductionCycle& cycle, std::chrono::seconds time) {
		auto product = *yieldAt(cycle.start);
		
		add(product);
		Facility::update(time);
		const auto left = (*this)[product];
		cycle.yield = product - left;
		cycle.waste = left;
		commodities_.clear();
		
		totalYield_ = cycle.yield.quantity();
		totalWaste_ = cycle.waste.quantity();
	}
	
	ProductionCycle* ExtractorControlUnit::startCycle(std::chrono::seconds time) {
		if ((!cycles_.empty() && time <= expiryTime_ - cycleTime_) ||
			(time == std::max(launchTime_, installTime_))) {
			
			auto product = *output();
			return cycles_.emplace_back(new ProductionCycle{time, cycleTime_, product, product}).get();
		}
		else
			return nullptr;
	}

	
}
