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
		return installTime_ && expiryTime_ && cycleTime_ && output();
	}

	std::optional<Commodity> ExtractorControlUnit::output() const {
		if (!outputs_.empty())
			return outputs_.begin()->commodity;
		else
			return std::nullopt;
	}
	
	std::optional<Commodity> ExtractorControlUnit::yieldAt(std::chrono::seconds time) const {
		if (!configured())
			return std::nullopt;
		
		auto product = *output();

		if (time >= expiryTime_ || time < installTime_)
			product = 0;
		else {
			auto cycleIndex = std::trunc((time - *installTime_) / *cycleTime_);
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
		if (!configured())
			return std::nullopt;
		
		if (extractionCycle_)
			return extractionCycle_->end();
		else {
			if (cycleTime_->count() > 0) {
				if (!launchTime_ || *launchTime_ < *installTime_)
					return installTime_;
				else
					return launchTime_;
			}
			else
				return std::nullopt;
		}
	}
	
	void ExtractorControlUnit::update(std::chrono::seconds time) {
		if (updating_ || !configured())
			return;
		updating_ = true;
		
		if (extractionCycle_) {
			const auto isCycleFinished = extractionCycle_->end() == time;
			
			if (isCycleFinished) {
				auto product = *yieldAt(extractionCycle_->start);
				
				add(product);
				Facility::update(time);
				const auto left = (*this)[product];
				extractionCycle_->yield = product - left;
				extractionCycle_->waste = left;
				commodities_.clear();

				totalYield_ = extractionCycle_->yield.quantity();
				totalWaste_ = extractionCycle_->waste.quantity();
				
				extractionCycle_ = nullptr;
				
				const auto sum = totalYield_ + totalWaste_;
				const Percent efficiency = sum > 0 ? static_cast<Float>(totalYield_) / static_cast<Float>(sum) : 0;
				auto state = new ProductionState(time, nullptr, efficiency);
				states_.emplace_back(state);
			}
		}
		
		if (!extractionCycle_) {
			auto isNewCycle = false;
			if (launchTime_) {
				if (*launchTime_ < *installTime_) {
					if (time == *installTime_)
						isNewCycle = true;
				}
				else if (time == *launchTime_)
					isNewCycle = true;
			}
			else if (time <= *expiryTime_ - *cycleTime_)
				isNewCycle = true;
			if (isNewCycle) {
				launchTime_ = std::nullopt;
				auto product = *output();
				extractionCycle_ = new ProductionCycle{time, *cycleTime_, product, product};
				if (states_.empty())
					states_.emplace_back(new ProductionState(time, extractionCycle_, 0));
				else
					(dynamic_cast<ProductionState*>(states_.back().get()))->cycle.reset(extractionCycle_);
			}
		}
		
		updating_ = false;
	}
	
}
