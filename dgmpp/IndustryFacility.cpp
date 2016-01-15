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

using namespace dgmpp;

IndustryFacility::IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), lastLaunchTime_(0), idle_(true) {
}

std::shared_ptr<Schematic> IndustryFacility::setSchematic(TypeID schematicID) {
	schematic_ = schematicID > 0 ? std::make_shared<Schematic>(getOwner()->getEngine(), schematicID) : nullptr;
	return schematic_;
}

void IndustryFacility::setLastLaunchTime(double lastLaunchTime) {
	lastLaunchTime_ = std::max(lastLaunchTime, 0.0);
	if (lastLaunchTime > 0)
		idle_ = false;
};


double IndustryFacility::getCycleTime() const {
	return schematic_ ? schematic_->getCycleTime() : 0;
}

int32_t IndustryFacility::getQuantityPerCycle() const {
	return schematic_ ? schematic_->getOutput().getQuantity() : 0;
}

double IndustryFacility::getCycleEndTime() const {
	double lastLaunchTime = getLastLaunchTime();
	if (lastLaunchTime > 0)
		return Facility::getCycleEndTime();
	else
		return 0;
}

void IndustryFacility::finishCycle(double cycleTime) {
	if (schematic_) {
		Commodity commodity = schematic_->getOutput();
		int32_t yield = commodity.getQuantity();
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
		if (commodity.getQuantity() > 0)
			getOwner()->reportWarning(std::make_shared<Warning>(shared_from_this(), Warning::CODE_WASTED, cycleTime, static_cast<double>(commodity.getQuantity()) / static_cast<double>(yield)));

	}
	setLastLaunchTime(0);
}

void IndustryFacility::startCycle(double cycleTime) {
	if (schematic_) {
		for (const auto& input: schematic_->getInputs()) {
			const auto& c = getCommodity(input);
			if (c.getQuantity() < input.getQuantity()) {
				if (!idle_) {
					getOwner()->reportWarning(std::make_shared<Warning>(shared_from_this(), Warning::CODE_PRODUCTION_STOPPED, cycleTime, 0));
					idle_ = true;
				}
				setLastLaunchTime(0);
				return;
			}
		}
		idle_ = false;
		setLastLaunchTime(cycleTime);
		clear();
	}
	else
		setLastLaunchTime(0);
}

int32_t IndustryFacility::getFreeStorage(const Commodity& commodity) const {
	if (schematic_) {
		for (const auto& input: schematic_->getInputs()) {
			if (input.getTypeID() == commodity.getTypeID()) {
				const auto& c = getCommodity(input);
				return std::max(input.getQuantity() - c.getQuantity(), 0);
			}
		}
		return 0;
	}
	else
		return 0;
}
