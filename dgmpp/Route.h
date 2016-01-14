#pragma once
#include "types.h"

namespace dgmpp {
	class Route {
	public:
		Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier = 0);
		std::shared_ptr<Facility> getSource() const;
		std::shared_ptr<Facility> getDestination() const;
	private:
		Facility* source_;
		Facility* destination_;
		TypeID contentTypeID_;
		int64_t identifier_;
	};
}