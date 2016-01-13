#pragma once
#include "types.h"

namespace dgmpp {
	class Route {
	public:
		Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier = 0);
		std::shared_ptr<Facility> getSource() const {return source_;};
		std::shared_ptr<Facility> getDestination() const {return destination_;};
	private:
		std::shared_ptr<Facility> source_;
		std::shared_ptr<Facility> destination_;
		TypeID contentTypeID_;
		int64_t identifier_;
	};
}