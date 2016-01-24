#pragma once
#include "Cycle.h"

namespace dgmpp {
	class ProductionCycle: public Cycle {
	public:
		ProductionCycle(double launchTime, double cycleTime, const std::list<std::shared_ptr<const Commodity>>& materials, const Commodity& yield, const Commodity& waste);
		ProductionCycle(double launchTime, double cycleTime, const Commodity& yield, const Commodity& waste);
		const Commodity& getYield() const {return *yield_;};
		const Commodity& getWaste() const {return *waste_;};
		const std::list<std::shared_ptr<const Commodity>>& getMaterials() const {return materials_;};
		void setMaterials(const std::list<std::shared_ptr<const Commodity>>& materials);
		bool isIdle() const;
	private:
		std::list<std::shared_ptr<const Commodity>> materials_;
		std::shared_ptr<const Commodity> yield_;
		std::shared_ptr<const Commodity> waste_;
	};
}