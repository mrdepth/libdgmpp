//
//  ExtractorControlUnit.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "ExtractorControlUnit.hpp"
#include "SDE.hpp"

namespace dgmpp2 {
	
	size_t ExtractorControlUnit::yieldAt(std::chrono::seconds time) const {
		if (time >= expiryTime_ || time < installTime_)
			return 0;
		
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
		return std::trunc(yield);
	}
	
	std::optional<std::chrono::seconds> ExtractorControlUnit::nextUpdateTime() const {
		if (extractionCycle_)
			return extractionCycle_->launchTime + extractionCycle_->cycleTime;
		else {
			auto cycleTime = cycleTime_;
			if (cycleTime.count() > 0) {
				if (launchTime_ < installTime_)
					return installTime_;
				else
					return launchTime_;
			}
			else
				return std::nullopt;
		}
	}
	
}
