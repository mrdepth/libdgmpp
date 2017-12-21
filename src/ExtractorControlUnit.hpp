//
//  ExtractorControlUnit.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Facility.hpp"

namespace dgmpp {
	
	class ExtractorControlUnit: public Facility {
	public:
		virtual bool configured() const override;

		std::chrono::seconds launchTime()	const noexcept { return launchTime_; }
		std::chrono::seconds installTime()	const noexcept { return installTime_; }
		std::chrono::seconds expiryTime()	const noexcept { return expiryTime_; }
		std::chrono::seconds cycleTime()	const noexcept { return cycleTime_; }
		void launchTime     (std::chrono::seconds value) noexcept { launchTime_ = value; }
		void installTime    (std::chrono::seconds value) noexcept { installTime_ = value; }
		void expiryTime     (std::chrono::seconds value) noexcept { expiryTime_ = value; }
		void cycleTime      (std::chrono::seconds value) noexcept { cycleTime_ = value; w_ = value; }
		std::size_t quantityPerCycle() const noexcept { return quantityPerCycle_; };
		void quantityPerCycle (std::size_t value) noexcept { quantityPerCycle_ = value; phaseShift_ = std::pow(value, 0.7); }
		std::optional<Commodity> output() const noexcept;
		
		const std::list<std::unique_ptr<ProductionState>>& states() const noexcept { return states_; }
		const std::list<std::unique_ptr<ProductionCycle>>& cycles() const noexcept { return cycles_; }

	protected:
		std::list<std::unique_ptr<ProductionState>> states_;
		std::list<std::unique_ptr<ProductionCycle>> cycles_;

		using Facility::Facility;
		virtual std::optional<std::chrono::seconds> nextUpdateTime() const noexcept override;
		virtual int priority() const noexcept override { return -1000; }
		virtual void update(std::chrono::seconds time) override;
	private:
		friend class Planet;
		
		std::chrono::seconds launchTime_ = std::chrono::seconds::zero();
		std::chrono::seconds installTime_ = std::chrono::seconds::zero();
		std::chrono::seconds expiryTime_ = std::chrono::seconds::zero();
		std::chrono::seconds cycleTime_ = std::chrono::seconds::zero();
		std::size_t quantityPerCycle_ = 0;
		std::chrono::duration<Float, std::ratio<60 * 15>> w_;
		Float phaseShift_ = 0;
		bool updating_ = false;
		
		ProductionCycle* extraction_ = nullptr;
		
		std::size_t totalYield_ = 0;
		std::size_t totalWaste_ = 0;
		
		std::optional<Commodity> yieldAt(std::chrono::seconds time) const noexcept;
		void finishCycle(ProductionCycle& cycle, std::chrono::seconds time);
		ProductionCycle* startCycle(std::chrono::seconds time);

	};
	
}


