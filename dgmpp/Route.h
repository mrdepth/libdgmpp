#pragma once
#include "types.h"

namespace dgmpp {
	class Route {
	public:
		Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier = 0);
		std::shared_ptr<Facility> getSource() const;
		std::shared_ptr<Facility> getDestination() const;
		const Commodity& getCommodity() const {return *commodity_;};
	private:
		std::weak_ptr<Facility> source_;
		std::weak_ptr<Facility> destination_;
		std::shared_ptr<Commodity> commodity_;
		int64_t identifier_;
	};
}