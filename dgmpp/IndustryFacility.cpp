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

IndustryFacility::IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier) : Facility(typeID, typeName, capacity, owner, identifier), launchTime_(0), idle_(true) {
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

void IndustryFacility::finishCycle(double cycleTime) {
	if (schematic_) {
		Commodity left = schematic_->getOutput();
		int32_t yield = left.getQuantity();
		for (auto output: getOutputs()) {
			if (left.getQuantity() > 0) {
				int32_t free = output->getDestination()->getFreeStorage(left);
				if (free > 0) {
					int32_t quantity = std::min(left.getQuantity(), free);
					output->getDestination()->addCommodity(Commodity(left, quantity));
					left.extract(quantity);
				}
			}
		}
		cycles_.push_back(std::make_shared<ProductionCycle>(getLaunchTime(), getCycleTime(), getCommodities(), Commodity(left, yield - left.getQuantity()), left));
		clear();

//		if (commodity.getQuantity() > 0)
//			getOwner()->reportWarning(std::make_shared<Warning>(shared_from_this(), Warning::CODE_WASTED, cycleTime, static_cast<double>(commodity.getQuantity()) / static_cast<double>(yield)));

	}
	setLaunchTime(0);
}

void IndustryFacility::startCycle(double cycleTime) {
	if (schematic_) {
		for (const auto& input: schematic_->getInputs()) {
			const auto& c = getCommodity(input);
			if (c.getQuantity() < input.getQuantity()) {
				if (!idle_) {
					idle_ = true;
					Commodity commodity = schematic_->getOutput();
					commodity.setQuantity(0);
					cycles_.push_back(std::make_shared<ProductionCycle>(cycleTime, getCycleTime(), getCommodities(), commodity, commodity));
				}
				else {
					bool equals = false;

					if (cycles_.size() > 0) {
						equals = true;
						auto lastCycle = std::dynamic_pointer_cast<ProductionCycle>(cycles_.back());
						const auto& lastCycleMaterials = lastCycle->getMaterials();
						const auto& materials = getCommodities();
						
						if (lastCycleMaterials.size() == materials.size() && lastCycleMaterials.size() > 0) {
							bool e = false;
							for (const auto& a: materials) {
								for (const auto& b: lastCycleMaterials) {
									if (*a == *b) {
										e = true;
										break;
									}
								}
								if (!e)
									break;
							}
							equals = e;
						}
						
						lastCycle->setCycleTime(cycleTime - lastCycle->getLaunchTime());
					}
					
					if (!equals) {
						Commodity commodity = schematic_->getOutput();
						commodity.setQuantity(0);
						cycles_.push_back(std::make_shared<ProductionCycle>(cycleTime, getCycleTime(), getCommodities(), commodity, commodity));
					}
				}
				setLaunchTime(0);
				return;
			}
		}
		if (idle_) {
			if (cycles_.size() > 0) {
				auto lastCycle = std::dynamic_pointer_cast<ProductionCycle>(cycles_.back());
				lastCycle->setCycleTime(cycleTime - lastCycle->getLaunchTime());
			}
		}
		
		idle_ = false;
		setLaunchTime(cycleTime);
	}
	else
		setLaunchTime(0);
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
