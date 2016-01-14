//
//  ExtractorControlUnit.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "ExtractorControlUnit.h"
#include "Planet.h"
#include "Engine.h"
#include <cmath>

using namespace dgmpp;

ExtractorControlUnit::ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), lastLaunchTime_(0), installTime_(0), expiryTime_(0), cycleTime_(0), quantityPerCycle_(0) {
	decayFactor_ = owner->getEngine()->decayFactor();
	noiseFactor_ = owner->getEngine()->noiseFactor();
}

void ExtractorControlUnit::setQuantityPerCycle(double quantityPerCycle) {
	quantityPerCycle_ = quantityPerCycle;
	phaseShift_ = std::pow(quantityPerCycle_, 0.7);
}

double ExtractorControlUnit::getYieldAtTime(double time) const {
	double cycleTimeMinutes = std::trunc(cycleTime_ / 60);
	int cycleIndex = (time - installTime_) / cycleTime_;
	double w = cycleTimeMinutes / 15;
	double t = (cycleIndex + 0.5) * w;
	
	static double f1 = 1.0 / 12.0;
	static double f2 = 1.0 / 5.0;
	static double f3 = 1.0 / 2.0;
	
	double decay = quantityPerCycle_ / (1.0 + t * decayFactor_);
	double sina = std::cos(phaseShift_ + t * f1);
	double sinb = std::cos(phaseShift_ / 2 + t * f2);
	double sinc = std::cos(t * f3);
	double sins = std::max((sina + sinb + sinc) / 3.0, 0.0);
	double h = decay * (1 + noiseFactor_ * sins);
	double yield = w * h;
	return std::trunc(yield);
}