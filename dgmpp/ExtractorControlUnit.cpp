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
#include <iostream>

using namespace dgmpp;

ExtractorControlUnit::ExtractorControlUnit(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), launchTime_(0), installTime_(0), expiryTime_(0), cycleTime_(0), quantityPerCycle_(0) {
	decayFactor_ = owner->getEngine()->decayFactor();
	noiseFactor_ = owner->getEngine()->noiseFactor();
}

void ExtractorControlUnit::setCycleTime(double cycleTime) {
	cycleTime_ = std::max(cycleTime, 0.0);
	double cycleTimeMinutes = std::trunc(cycleTime_ / 60);
	w_ = cycleTimeMinutes / 15;
};

void ExtractorControlUnit::setQuantityPerCycle(double quantityPerCycle) {
	quantityPerCycle_ = quantityPerCycle;
	phaseShift_ = std::pow(quantityPerCycle_, 0.7);
}

int32_t ExtractorControlUnit::getYieldAtTime(double time) const {
	if (time >= expiryTime_ || time < installTime_)
		return 0;
	
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

double ExtractorControlUnit::getNextUpdateTime() const {
	double cycleTime = getCycleTime();
	if (cycleTime > 0) {
		if (getLaunchTime() < getInstallTime())
			return getInstallTime();
		else {
			double time = getLaunchTime() + cycleTime;
			if (time > getExpiryTime())
				return std::numeric_limits<double>::infinity();
			else
				return time;
		}
	}
	else
		return std::numeric_limits<double>::infinity();
	
}


double ExtractorControlUnit::getCycleEndTime() const {
	double cycleEndTime = Facility::getCycleEndTime();
	if (cycleEndTime <= getExpiryTime())
		return cycleEndTime;
	else
		return std::numeric_limits<double>::infinity();
}

void ExtractorControlUnit::finishCycle(double cycleTime) {
}

void ExtractorControlUnit::startCycle(double cycleTime) {
}

void ExtractorControlUnit::update(double time) {
	double cycleEndTime = getCycleEndTime();
	bool endCycle = !std::isinf(cycleEndTime) && fabs(cycleEndTime - time) < 0.5;
	
	if (endCycle) {
		uint32_t yield = getYieldAtTime(getLaunchTime());
		addCommodity(Commodity(getOutput(), yield));
		Facility::update(time);
		auto left = getCommodity(getOutput());
		cycles_.push_back(std::make_shared<ProductionCycle>(getLaunchTime(), getCycleTime(), Commodity(left, yield - left.getQuantity()), left));
		clear();
	}
	
	if (getLaunchTime() < 0 || endCycle) {
		if (time >= getInstallTime()) {
			if (time + getCycleTime() <= getExpiryTime())
				setLaunchTime(time);
			else
				setLaunchTime(std::numeric_limits<double>::infinity());
		}
	}
}


std::shared_ptr<const ProductionCycle> ExtractorControlUnit::getCycle(double timeStamp) const {
	return std::dynamic_pointer_cast<const ProductionCycle>(Facility::getCycle(timeStamp));
}

Commodity ExtractorControlUnit::getOutput() const {
	auto outputs = getOutputs();
	if (outputs.size() > 0)
		return outputs.front()->getCommodity();
	else
		return Commodity::InvalidCommodity();
}

bool ExtractorControlUnit::routed() const {
	return getOutputs().size() > 0;
}
