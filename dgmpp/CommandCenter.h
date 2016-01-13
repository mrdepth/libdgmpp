#pragma once
#include "Facility.h"
#include "Route.h"

namespace dgmpp {
	class CommandCenter: public Facility {
	public:
		CommandCenter(std::shared_ptr<Engine> const& engine, TypeID typeID);
		std::shared_ptr<Facility> addFacility(TypeID typeID);
		void removeFacility(std::shared_ptr<Facility> const& facility);
		std::shared_ptr<Route> addRoute(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID);
		void removeRoute(std::shared_ptr<Route> const& route);
		
	private:
		FacilitiesList facilities_;
		RoutesList routes_;
	};
}