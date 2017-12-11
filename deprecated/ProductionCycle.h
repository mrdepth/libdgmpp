#pragma once
#include "Cycle.h"
#include "Commodity.h"

namespace dgmpp {
	class ProductionCycle: public Cycle {
	public:
		ProductionCycle(double launchTime, double cycleTime, const Commodity& yield, const Commodity& waste);
		const Commodity& getYield() const {return *yield_;};
		const Commodity& getWaste() const {return *waste_;};
		void setYield(const Commodity& yield) {yield_ = std::make_shared<const Commodity>(yield);};
		void setWaste(const Commodity& waste) {waste_ = std::make_shared<const Commodity>(waste);};
		friend std::ostream& operator<<(std::ostream& os, const ProductionCycle& productionCycle);
	private:
		std::shared_ptr<const Commodity> yield_;
		std::shared_ptr<const Commodity> waste_;
	};
}
