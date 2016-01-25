#pragma once
#include "types.h"
#include "Commodity.h"

namespace dgmpp {
	class Route {
	public:
		Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, const Commodity& commodity, int64_t identifier = 0);
		std::shared_ptr<Facility> getSource() const;
		std::shared_ptr<Facility> getDestination() const;
		const Commodity& getCommodity() const {return commodity_;};
		void update(double time) const;
	private:
		std::weak_ptr<Facility> source_;
		std::weak_ptr<Facility> destination_;
		Commodity commodity_;
		int64_t identifier_;
	};
}