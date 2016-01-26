#pragma once
#include "State.h"
#include "ProductionCycle.h"

namespace dgmpp {
	class ProductionState: public State {
	public:
		ProductionState(double timestamp, const std::shared_ptr<ProductionCycle>& currentCycle);
		virtual ~ProductionState() {};
		const std::shared_ptr<ProductionCycle>& getCurrentCycle() const {return currentCycle_;};
	private:
		std::shared_ptr<ProductionCycle> currentCycle_;
	};
}