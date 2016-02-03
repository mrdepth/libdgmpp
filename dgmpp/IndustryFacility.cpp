//
//  IndustryFacility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "IndustryFacility.h"
#include "Planet.h"
#include "Engine.h"
#include "Route.h"
#include "Commodity.h"
#include <cmath>

using namespace dgmpp;



IndustryFacility::IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), launchTime_(0), startTime_(-1), productionTime_(0) {
}

std::shared_ptr<Schematic> IndustryFacility::setSchematic(TypeID schematicID) {
	schematic_ = schematicID > 0 ? std::make_shared<Schematic>(getOwner()->getEngine(), schematicID) : nullptr;
	return schematic_;
}

void IndustryFacility::setLaunchTime(double launchTime) {
	launchTime_ = launchTime;
};


double IndustryFacility::getCycleTime() const {
	return schematic_ ? schematic_->getCycleTime() : 0;
}

uint32_t IndustryFacility::getQuantityPerCycle() const {
	return schematic_ ? schematic_->getOutput().getQuantity() : 0;
}

double IndustryFacility::getNextUpdateTime() const {
	if (!schematic_)
		return std::numeric_limits<double>::infinity();
	
	if (productionCycle_)
		return productionCycle_->getLaunchTime() + productionCycle_->getCycleTime();
	else if (!std::isinf(getLaunchTime()) && getLaunchTime() + getCycleTime() < getOwner()->getLastUpdate())
		return getOwner()->getLastUpdate();
	else
		return getLaunchTime();
}

void IndustryFacility::finishCycle(double time) {
	Commodity product = schematic_->getOutput();
	addCommodity(product);
	Facility::update(time);
	auto left = getCommodity(getOutput());
	if (left.getQuantity() > 0)
		extractCommodity(left);
	productionCycle_->setYield(product - left);
	productionCycle_->setWaste(left);
	productionTime_ += productionCycle_->getCycleTime();
	productionCycle_ = nullptr;
	setLaunchTime(std::numeric_limits<double>::infinity());
	
	states_.push_back(std::make_shared<ProductionState>(time, nullptr, productionTime_ / (time - startTime_)));
}

bool IndustryFacility::startCycle(double time) {
	if (!std::isinf(getLaunchTime())) {
		if (getLaunchTime() + getCycleTime() < getOwner()->getLastUpdate()) {
			if (time != getOwner()->getLastUpdate())
				return false;
		}
		else if (time != getLaunchTime())
			return false;
	}
	if (startTime_ < 0)
		startTime_ = time;
	
	if (getLaunchTime() < 0) {
		setLaunchTime(std::numeric_limits<double>::infinity());
		productionCycle_ = std::make_shared<ProductionCycle>(time, getCycleTime(), getOutput(), getOutput());
		return true;
	}
	else {
		setLaunchTime(std::numeric_limits<double>::infinity());
		if (schematic_->getInputs() == getCommodities()) {
			productionCycle_ = std::make_shared<ProductionCycle>(time, getCycleTime(), getOutput(), getOutput());
			clear();
			for (const auto& input: getInputs())
				input->getSource()->update(time);
			return true;
		}
	}
	return false;
}

void IndustryFacility::update(double time) {
	if (!schematic_)
		return;
	
	if (productionCycle_) {
		double cycleEndTime = productionCycle_->getLaunchTime() + productionCycle_->getCycleTime();
		bool endCycle = cycleEndTime == time;
		if (endCycle)
			finishCycle(time);
	}
	
	if (!productionCycle_)
		if (startCycle(time))
			return;
	
	auto materials = getCommodities();
	std::shared_ptr<ProductionState> currentState;
	if (states_.size() > 0) {
		currentState = std::dynamic_pointer_cast<ProductionState>(states_.back());
		if (currentState->getTimestamp() < time && (currentState->getCurrentCycle() != productionCycle_ || currentState->getCommodities() != materials))
			currentState = nullptr;
	}
	
	if (!currentState) {
		currentState = std::make_shared<ProductionState>(time, nullptr);
		states_.push_back(currentState);
	}
	currentState->setCommodities(materials);
	currentState->setCurrentCycle(productionCycle_);
	if (startTime_ > 0) {
		double duration = time - startTime_;
		if (duration > 0)
			currentState->setEfficiency(productionTime_ / duration);
	}
}


uint32_t IndustryFacility::getFreeStorage(const Commodity& commodity) const {
	if (schematic_) {
		for (const auto& input: schematic_->getInputs()) {
			if (input.getTypeID() == commodity.getTypeID()) {
				const auto& c = getCommodity(input);
				return std::max(static_cast<int32_t>(input.getQuantity()) - static_cast<int32_t>(c.getQuantity()), 0);
			}
		}
		return 0;
	}
	else
		return 0;
}

Commodity IndustryFacility::getOutput() const {
	if (schematic_)
		return schematic_->getOutput();
	else
		return Commodity::InvalidCommodity();
}

bool IndustryFacility::routed() const {
	if (schematic_) {
		for (const auto& require: schematic_->getInputs()) {
			bool routed = false;
			for (const auto& input: getInputs()) {
				if (input->getCommodity().getTypeID() == require.getTypeID()) {
					routed = true;
					break;
				}
			}
			if (!routed)
				return false;
		}
		const auto& product = schematic_->getOutput();
		for (const auto& output: getOutputs()) {
			if (output->getCommodity().getTypeID() == product.getTypeID())
				return true;
		}
		return false;
	}
	else
		return false;
}
