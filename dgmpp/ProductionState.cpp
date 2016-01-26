//
//  ProductionState.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 26.01.16.
//
//

#include "ProductionState.h"

using namespace dgmpp;

ProductionState::ProductionState(double timestamp, const std::shared_ptr<ProductionCycle>& currentCycle) : State(timestamp), currentCycle_(currentCycle) {
}
