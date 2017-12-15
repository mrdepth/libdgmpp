#pragma once
#include "Facility.h"
#include "ProductionState.h"

namespace dgmpp {
	class ExtractorControlUnit: public Facility {
	public:
		
		static const GroupID groupID = GroupID::extractorControlUnits;
		
		ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual GroupID getGroupID() const {return groupID;};
		

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
		
		Float decayFactor_;
		Float noiseFactor_;
		double phaseShift_;
		double w_;
		uint32_t yield_;
		uint32_t waste_;
		bool updating_;
		
		std::shared_ptr<ProductionCycle> extractionCycle_;
	};
}
