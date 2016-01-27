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

void ExtractorControlUnit::setQuantityPerCycle(uint32_t quantityPerCycle) {
	quantityPerCycle_ = quantityPerCycle;
	phaseShift_ = std::pow(quantityPerCycle_, 0.7);
}

uint32_t ExtractorControlUnit::getYieldAtTime(double time) const {
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
	if (extractionCycle_)
		return extractionCycle_->getLaunchTime() + extractionCycle_->getCycleTime();
	else {
		double cycleTime = getCycleTime();
		if (cycleTime > 0) {
			if (getLaunchTime() < getInstallTime())
				return getInstallTime();
			else
				return getLaunchTime();
		}
		else
			return std::numeric_limits<double>::infinity();
	}
}

void ExtractorControlUnit::update(double time) {
	if (extractionCycle_) {
		double cycleEndTime = extractionCycle_->getLaunchTime() + extractionCycle_->getCycleTime();
		bool endCycle = cycleEndTime == time;
		
		if (endCycle) {
			uint32_t yield = getYieldAtTime(extractionCycle_->getLaunchTime());
			Commodity product = Commodity(getOutput(), yield);
			addCommodity(product);
			Facility::update(time);
			auto left = getCommodity(getOutput());
			extractionCycle_->setYield(product - left);
			extractionCycle_->setWaste(left);
			
			clear();
			extractionCycle_ = nullptr;
			states_.push_back(std::make_shared<ProductionState>(time, nullptr));
		}
	}
	
	if (!extractionCycle_) {
		bool newCycle = false;
		if (!std::isinf(getLaunchTime())) {
			if (getLaunchTime() < getInstallTime()) {
				if (time == getInstallTime())
					newCycle = true;
			}
			else if (time == getLaunchTime())
				newCycle = true;
		}
		else if (time <= getExpiryTime() - getCycleTime())
			newCycle = true;
		if (newCycle) {
			setLaunchTime(std::numeric_limits<double>::infinity());
			extractionCycle_ = std::make_shared<ProductionCycle>(time, getCycleTime(), getOutput(), getOutput());
			if (states_.size() == 0)
				states_.push_back(std::make_shared<ProductionState>(time, extractionCycle_));
			else
				std::dynamic_pointer_cast<ProductionState>(states_.back())->setCurrentCycle(extractionCycle_);
		}
	}
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
