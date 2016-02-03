#pragma once
#include "State.h"
#include "ProductionCycle.h"

namespace dgmpp {
	class ProductionState: public State {
	public:
		ProductionState(double timestamp, const std::shared_ptr<ProductionCycle>& currentCycle = nullptr, double efficiency = 0.0);
		virtual ~ProductionState() {};
		const std::shared_ptr<ProductionCycle>& getCurrentCycle() const {return currentCycle_;};
		void setCurrentCycle(const std::shared_ptr<ProductionCycle>& cycle) {currentCycle_ = cycle;};
		bool operator == (const ProductionState& other);
		bool operator != (const ProductionState& other);
		double getEfficiency() const {return efficiency_;};
		void setEfficiency(double efficiency) {efficiency_ = efficiency;};
	private:
		std::shared_ptr<ProductionCycle> currentCycle_;
		double efficiency_;
	};
}