#pragma once
#include "types.h"

namespace dgmpp {
	class State {
	public:
		State(double timestamp);
		virtual ~State() {};
		virtual double getTimestamp() const {return timestamp_;};
		virtual void setTimestamp(double timestamp) {timestamp_ = timestamp;};
		
		const std::list<std::shared_ptr<const Commodity>>& getCommodities() const {return commodities_;};
		void setCommodities(const std::list<std::shared_ptr<const Commodity>>& commodities);
		
	private:
		double timestamp_;
		std::list<std::shared_ptr<const Commodity>> commodities_;
	};
}