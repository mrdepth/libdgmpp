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

		std::chrono::seconds launchTime()	const { return launchTime_; }
		std::chrono::seconds installTime()	const { return installTime_; }
		std::chrono::seconds expiryTime()	const { return expiryTime_; }
		std::chrono::seconds cycleTime()	const { return cycleTime_; }
		void launchTime     (std::chrono::seconds value) { launchTime_ = value; }
		void installTime    (std::chrono::seconds value) { installTime_ = value; }
		void expiryTime     (std::chrono::seconds value) { expiryTime_ = value; }
		void cycleTime      (std::chrono::seconds value) { cycleTime_ = value; w_ = value; }
		size_t quantityPerCycle() const { return quantityPerCycle_; };
		void quantityPerCycle (size_t value) { quantityPerCycle_ = value; phaseShift_ = std::pow(value, 0.7); }
		std::optional<Commodity> output() const;
		
		const std::list<std::unique_ptr<ProductionState>>& states() const noexcept { return states_; }
		const std::list<std::unique_ptr<ProductionCycle>>& cycles() const noexcept { return cycles_; }

	protected:
		std::list<std::unique_ptr<ProductionState>> states_;
		std::list<std::unique_ptr<ProductionCycle>> cycles_;

		using Facility::Facility;
		virtual std::optional<std::chrono::seconds> nextUpdateTime() const override;
		virtual int priority() const override { return -1000; }
		virtual void update(std::chrono::seconds time) override;
	private:
		friend class Planet;
		
		std::chrono::seconds launchTime_ = std::chrono::seconds::zero();
		std::chrono::seconds installTime_ = std::chrono::seconds::zero();
		std::chrono::seconds expiryTime_ = std::chrono::seconds::zero();
		std::chrono::seconds cycleTime_ = std::chrono::seconds::zero();;
		size_t quantityPerCycle_ = 0;
		std::chrono::duration<Float, std::ratio<60 * 15>> w_;
		Float phaseShift_ = 0;
		bool updating_ = false;
		
		ProductionCycle* extraction_ = nullptr;
		
		size_t totalYield_ = 0;
		size_t totalWaste_ = 0;
		
		std::optional<Commodity> yieldAt(std::chrono::seconds time) const;
		void finishCycle(ProductionCycle& cycle, std::chrono::seconds time);
		ProductionCycle* startCycle(std::chrono::seconds time);

	};
	
}


