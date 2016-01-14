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
#include "Route.h"
#include "Commodity.h"
#include <cmath>

using namespace dgmpp;

ExtractorControlUnit::ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), lastLaunchTime_(0), installTime_(0), expiryTime_(0), cycleTime_(0), quantityPerCycle_(0) {
	decayFactor_ = owner->getEngine()->decayFactor();
	noiseFactor_ = owner->getEngine()->noiseFactor();
}

void ExtractorControlUnit::setCycleTime(double cycleTime) {
	cycleTime_ = cycleTime;
	double cycleTimeMinutes = std::trunc(cycleTime_ / 60);
	w_ = cycleTimeMinutes / 15;
};

void ExtractorControlUnit::setQuantityPerCycle(double quantityPerCycle) {
	quantityPerCycle_ = quantityPerCycle;
	phaseShift_ = std::pow(quantityPerCycle_, 0.7);
}

int32_t ExtractorControlUnit::getYieldAtTime(double time) const {
	int cycleIndex = (time - installTime_) / cycleTime_;
	double t = (cycleIndex + 0.5) * w_;
	
	static double f1 = 1.0 / 12.0;
	static double f2 = 1.0 / 5.0;
	static double f3 = 1.0 / 2.0;
	
	double decay = quantityPerCycle_ / (1.0 + t * decayFactor_);
	double sina = std::cos(phaseShift_ + t * f1);
	double sinb = std::cos(phaseShift_ / 2 + t * f2);
	double sinc = std::cos(t * f3);
	double sins = std::max((sina + sinb + sinc) / 3.0, 0.0);
	double h = decay * (1 + noiseFactor_ * sins);
	double yield = w_ * h;
	return std::trunc(yield);
}

double ExtractorControlUnit::getCycleEndTime() const {
	double cycleEndTime = Facility::getCycleEndTime();
	if (cycleEndTime <= getExpiryTime())
		return cycleEndTime;
	else
		return 0;
}

void ExtractorControlUnit::finishCycle() {
	auto outputs = getOutputs();
	if (outputs.size() > 0) {
		Commodity commodity = Commodity(outputs.front()->getCommodity(), getYieldAtTime(getLastLaunchTime()));
		for (auto output: getOutputs()) {
			if (commodity.getQuantity() > 0) {
				int32_t free = output->getDestination()->getFreeStorage(commodity);
				if (free > 0) {
					int32_t quantity = std::min(commodity.getQuantity(), free);
					output->getDestination()->addCommodity(Commodity(commodity, quantity));
					commodity.extract(quantity);
				}
			}
		}
	}
	setLastLaunchTime(0);
}

void ExtractorControlUnit::startCycle(double cycleTime) {
	if (cycleTime + getCycleTime() <= getExpiryTime())
		setLastLaunchTime(cycleTime);
}