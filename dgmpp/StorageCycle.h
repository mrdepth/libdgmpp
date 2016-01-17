#pragma once
#include "Cycle.h"

namespace dgmpp {
	class StorageCycle: public Cycle {
	public:
		StorageCycle(double launchTime, double cycleTime, const std::list<std::shared_ptr<const Commodity>>& commodities);
		const std::list<std::shared_ptr<const Commodity>>& getCommodities() const {return commodities_;};

	private:
		std::list<std::shared_ptr<const Commodity>> commodities_;
	};
}