//
//  ExtractorControlUnit.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Facility.hpp"

namespace dgmpp2 {
	
	class ExtractorControlUnit: public Facility {
	public:
		virtual bool configured() const override;

		std::optional<std::chrono::seconds> launchTime()	const { return launchTime_; }
		std::optional<std::chrono::seconds> installTime()	const { return installTime_; }
		std::optional<std::chrono::seconds> expiryTime()	const { return expiryTime_; }
		std::optional<std::chrono::seconds> cycleTime()	const { return cycleTime_; }
		void launchTime     (std::chrono::seconds value) { launchTime_ = value; }
		void installTime    (std::chrono::seconds value) { installTime_ = value; }
		void expiryTime     (std::chrono::seconds value) { expiryTime_ = value; }
		void cycleTime      (std::chrono::seconds value) { cycleTime_ = value; w_ = value; }
		size_t quantityPerCycle() const { return quantityPerCycle_; };
		void quantityPerCycle (size_t value) { quantityPerCycle_ = value; phaseShift_ = std::pow(value, 0.7); }
		std::optional<Commodity> output() const;
		std::optional<Commodity> yieldAt(std::chrono::seconds time) const;
		
	protected:
		using Facility::Facility;
		virtual std::optional<std::chrono::seconds> nextUpdateTime() const override;
		virtual int priority() const override { return -1000; }
		virtual void update(std::chrono::seconds time) override;
		
	private:
		friend class Planet;
		
		std::optional<std::chrono::seconds> launchTime_;
		std::optional<std::chrono::seconds> installTime_;
		std::optional<std::chrono::seconds> expiryTime_;
		std::optional<std::chrono::seconds> cycleTime_;
		size_t quantityPerCycle_;
		std::chrono::duration<Float, std::ratio<60 * 15>> w_;
		Float phaseShift_ = 0;
		bool updating_ = false;
		
		ProductionCycle* extractionCycle_;
		
		size_t totalYield_ = 0;
		size_t totalWaste_ = 0;
	};
	
}


