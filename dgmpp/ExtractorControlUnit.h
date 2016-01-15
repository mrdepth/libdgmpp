#pragma once
#include "Facility.h"

namespace dgmpp {
	class ExtractorControlUnit: public Facility {
	public:
		enum {
			GROUP_ID = 1063
		};
		ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() const {return GROUP_ID;};
		

		virtual double getLastLaunchTime() const {return lastLaunchTime_;};
		virtual double getInstallTime() const {return installTime_;};
		virtual double getExpiryTime() const {return expiryTime_;};
		virtual double getCycleTime() const {return cycleTime_;};

		void setLastLaunchTime(double lastLaunchTime) {lastLaunchTime_ = std::max(lastLaunchTime, 0.0);};
		void setInstallTime(double installTime) {installTime_ = std::max(installTime, 0.0);};
		void setExpiryTime(double expiryTime) {expiryTime_ = std::max(expiryTime, 0.0);};
		void setCycleTime(double cycleTime);
		void setQuantityPerCycle(double quantityPerCycle);
		double getQuantityPerCycle() const {return quantityPerCycle_;};
		
		int32_t getYieldAtTime(double time) const;
		
		virtual double getCycleEndTime() const;
		virtual void finishCycle(double cycleTime);
		virtual void startCycle(double cycleTime);
		virtual int priority() const {return 2;};
	private:
		double lastLaunchTime_;
		double installTime_;
		double expiryTime_;
		double cycleTime_;
		double quantityPerCycle_;
		float decayFactor_;
		float noiseFactor_;
		
		double phaseShift_;
		double w_;
	};
}