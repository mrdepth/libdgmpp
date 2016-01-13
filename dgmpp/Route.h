#pragma once
#include "types.h"

namespace dgmpp {
	struct Route {
		std::shared_ptr<Facility> source;
		std::shared_ptr<Facility> destination;
		TypeID contentTypeID;
		int64_t identifier;
	};
}