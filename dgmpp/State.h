#pragma once
#include "types.h"
#include "Commodity.h"

namespace dgmpp {
	class State {
	public:
		State(double timestamp);
		virtual ~State() {};
		virtual double getTimestamp() const {return timestamp_;};
		virtual void setTimestamp(double timestamp) {timestamp_ = timestamp;};
		double getVolume() const;

		const std::list<const Commodity>& getCommodities() const {return commodities_;};
		void setCommodities(const std::list<const Commodity>& commodities);
		virtual std::string toJSONString() const;
		
		friend std::ostream& operator<<(std::ostream& os, const State& state);

	private:
		double timestamp_;
		std::list<const Commodity> commodities_;
	};
}