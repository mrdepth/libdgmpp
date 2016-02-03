//
//  ProductionState.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 26.01.16.
//
//

#include "ProductionState.h"
#include "Facility.h"

using namespace dgmpp;

ProductionState::ProductionState(double timestamp, const std::shared_ptr<ProductionCycle>& currentCycle, double efficiency) : State(timestamp), currentCycle_(currentCycle), efficiency_(efficiency) {
}

bool ProductionState::operator == (const ProductionState& other) {
	return currentCycle_ == other.currentCycle_ && getCommodities() == other.getCommodities();
}

bool ProductionState::operator != (const ProductionState& other) {
	return !(*this == other);
}
