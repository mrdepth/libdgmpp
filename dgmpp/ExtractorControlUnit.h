#pragma once
#include "Facility.h"

namespace dgmpp {
	class ExtractorControlUnit: public Facility {
	public:
		enum {
			GROUP_ID = 1063
		};
		ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() {return GROUP_ID;};
		
		void setLastLaunchTime(double lastLaunchTime) {lastLaunchTime_ = lastLaunchTime;};
		double getLastLaunchTime() const {return lastLaunchTime_;};
		void setInstallTime(double installTime) {installTime_ = installTime;};
		double getInstallTime() const {return installTime_;};
		void setExpiryTime(double expiryTime) {expiryTime_ = expiryTime;};
		double getExpiryTime() const {return expiryTime_;};
		void setCycleTime(double cycleTime) {cycleTime_ = cycleTime;};
		double getCycleTime() const {return cycleTime_;};
		void setQuantityPerCycle(double quantityPerCycle);
		double getQuantityPerCycle() const {return quantityPerCycle_;};
		
		double getYieldAtTime(double time) const;
	private:
		double lastLaunchTime_;
		double installTime_;
		double expiryTime_;
		double cycleTime_;
		double quantityPerCycle_;
		float decayFactor_;
		float noiseFactor_;
		double phaseShift_;
	};
}