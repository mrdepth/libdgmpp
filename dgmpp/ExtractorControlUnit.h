#pragma once
#include "Facility.h"
#include "ProductionState.h"

namespace dgmpp {
	class ExtractorControlUnit: public Facility {
	public:
		enum: TypeID {
			GROUP_ID = 1063
		};
		ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() const {return GROUP_ID;};
		

		virtual double getLaunchTime() const {return launchTime_;};
		virtual double getInstallTime() const {return installTime_;};
		virtual double getExpiryTime() const {return expiryTime_;};
		virtual double getCycleTime() const {return cycleTime_;};

		void setLaunchTime(double launchTime) {launchTime_ = launchTime;};
		void setInstallTime(double installTime) {installTime_ = installTime;};
		void setExpiryTime(double expiryTime) {expiryTime_ = expiryTime;};
		void setCycleTime(double cycleTime);
		void setQuantityPerCycle(uint32_t quantityPerCycle);
		uint32_t getQuantityPerCycle() const {return quantityPerCycle_;};
		
		uint32_t getYieldAtTime(double time) const;
		
		Commodity getOutput() const;

		virtual bool routed() const;

	protected:
		virtual double getNextUpdateTime() const;
		virtual void update(double time);
		virtual int priority() const {return 1000;};
	private:
		double launchTime_;
		double installTime_;
		double expiryTime_;
		double cycleTime_;
		uint32_t quantityPerCycle_;
		
		float decayFactor_;
		float noiseFactor_;
		double phaseShift_;
		double w_;
		uint32_t yield_;
		uint32_t waste_;
		
		std::shared_ptr<ProductionCycle> extractionCycle_;
	};
}