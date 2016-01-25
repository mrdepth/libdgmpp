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



IndustryFacility::IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), launchTime_(0), idle_(true), nextUpdateTime_(-1) {
}

std::shared_ptr<Schematic> IndustryFacility::setSchematic(TypeID schematicID) {
	schematic_ = schematicID > 0 ? std::make_shared<Schematic>(getOwner()->getEngine(), schematicID) : nullptr;
	return schematic_;
}

void IndustryFacility::setLaunchTime(double launchTime) {
	launchTime_ = std::max(launchTime, 0.0);
	if (launchTime > 0)
		idle_ = false;
};


double IndustryFacility::getCycleTime() const {
	return schematic_ ? schematic_->getCycleTime() : 0;
}

int32_t IndustryFacility::getQuantityPerCycle() const {
	return schematic_ ? schematic_->getOutput().getQuantity() : 0;
}

double IndustryFacility::getCycleEndTime() const {
	double launchTime = getLaunchTime();
	if (launchTime > 0)
		return Facility::getCycleEndTime();
	else
		return 0;
}

double IndustryFacility::getNextUpdateTime() const {
	double launchTime = getLaunchTime();
	if (launchTime >= 0) {
		if (nextUpdateTime_ <= 0)
			return launchTime;
		else if (idle_)
			return std::numeric_limits<double>::infinity();
		else
			return Facility::getCycleEndTime();
	}
	else
		return std::numeric_limits<double>::infinity();
}

void IndustryFacility::finishCycle(double time) {
	if (schematic_) {
		Commodity product = schematic_->getOutput();
		addCommodity(product);
		Facility::update(time);
		auto left = getCommodity(getOutput());
		cycles_.push_back(std::make_shared<ProductionCycle>(getLaunchTime(), getCycleTime(), Commodity(left, product.getQuantity() - left.getQuantity()), left));
		if (left.getQuantity() > 0)
			extractCommodity(left);
	}
	idle_ = true;
}

void IndustryFacility::startCycle(double time) {
	if (schematic_) {
		for (const auto& input: schematic_->getInputs()) {
			const auto& c = getCommodity(input);
			if (c.getQuantity() < input.getQuantity()) {
				if (!idle_) {
					idle_ = true;
					Commodity commodity = schematic_->getOutput();
					commodity.setQuantity(0);
					cycles_.push_back(std::make_shared<ProductionCycle>(time, std::numeric_limits<double>::infinity(), commodity, commodity));
				}
				else {
					bool equals = false;

					if (cycles_.size() > 0) {
						auto lastCycle = std::dynamic_pointer_cast<ProductionCycle>(cycles_.back());
						if (lastCycle->getLaunchTime() == time)
							equals = true;
						else
							equals = lastCycle->getMaterials() == getCommodities();
						
						if (!equals)
							lastCycle->setCycleTime(time - lastCycle->getLaunchTime());
					}
					
					if (!equals) {
						Commodity commodity = schematic_->getOutput();
						commodity.setQuantity(0);
						cycles_.push_back(std::make_shared<ProductionCycle>(time, std::numeric_limits<double>::infinity(), commodity, commodity));
					}
				}
				setLaunchTime(0);
				nextUpdateTime_ = std::numeric_limits<double>::infinity();
				return;
			}
		}
		
		if (idle_) {
			if (cycles_.size() > 0) {
				auto lastCycle = std::dynamic_pointer_cast<ProductionCycle>(cycles_.back());
				lastCycle->setCycleTime(time - lastCycle->getLaunchTime());
			}
		}
		
		idle_ = false;
		setLaunchTime(time);
		nextUpdateTime_ = time + getCycleTime();
		clear();
		for (const auto& input: getInputs()) {
			input->update(time);
		}
	}
	else
		nextUpdateTime_ = std::numeric_limits<double>::infinity();
}

void IndustryFacility::update(double time) {
	double cycleEndTime = getCycleEndTime();
	bool endCycle = !std::isinf(cycleEndTime) && fabs(cycleEndTime - time) < 0.5 && !idle_;

	if (endCycle) {
		finishCycle(time);
	}
	
	if (idle_)
		startCycle(time);
	
	if (cycles_.size() > 0) {
		auto lastCycle = std::dynamic_pointer_cast<ProductionCycle>(cycles_.back());
		if (lastCycle->getLaunchTime() == time)
			lastCycle->setMaterials(getCommodities());
	}
	
	if (idle_)
		nextUpdateTime_ = std::numeric_limits<double>::infinity();
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

std::shared_ptr<const ProductionCycle> IndustryFacility::getCycle(double timeStamp) const {
	return std::dynamic_pointer_cast<const ProductionCycle>(Facility::getCycle(timeStamp));
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
