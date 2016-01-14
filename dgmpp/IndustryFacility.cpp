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

IndustryFacility::IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), lastLaunchTime_(0) {
}

std::shared_ptr<Schematic> IndustryFacility::setSchematic(TypeID schematicID) {
	schematic_ = schematicID > 0 ? std::make_shared<Schematic>(getOwner()->getEngine(), schematicID) : nullptr;
	return schematic_;
}

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

void IndustryFacility::finishCycle() {
	if (schematic_) {
		Commodity commodity = schematic_->getOutput();
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

void IndustryFacility::startCycle(double cycleTime) {
	if (schematic_) {
		for (const auto& input: schematic_->getInputs()) {
			const auto& c = getCommodity(input);
			if (c.getQuantity() < input.getQuantity()) {
				setLastLaunchTime(0);
				return;
			}
		}
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
