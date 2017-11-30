#pragma once
#include "types.h"

namespace dgmpp {
	class Cycle {
	public:
		Cycle(double launchTime, double cycleTime);
		virtual ~Cycle() {};
		virtual double getLaunchTime() const {return launchTime_;};
		virtual double getCycleTime() const {return cycleTime_;};
		virtual void setLaunchTime(double launchTime) {launchTime_ = launchTime;};
		virtual void setCycleTime(double cycleTime) {cycleTime_ = cycleTime;};
	private:
		double launchTime_;
		double cycleTime_;
	};
}
