#pragma once
#include "types.h"

namespace dgmpp {
	class Planet : public std::enable_shared_from_this<Planet> {
	public:
		Planet(std::shared_ptr<Engine> const& engine, TypeID typeID);
		TypeID getTypeID() const {return typeID_;};
		
		std::shared_ptr<Facility> addFacility(TypeID typeID, int64_t identifier = 0);
		void removeFacility(std::shared_ptr<Facility> const& facility);
		const FacilitiesList& getFacilities() const {return facilities_;};
		std::shared_ptr<Facility> findFacility(int64_t identifier);
		
		std::shared_ptr<Route> addRoute(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, const Commodity& commodity, int64_t identifier = 0);
		void removeRoute(std::shared_ptr<const Route> const& route);
		
		std::shared_ptr<Engine> getEngine() const;
		
		void setLastUpdate(double lastUpdate);
		double getLastUpdate();
		
		double simulate();
		
		virtual std::string toJSONString() const;
		friend std::ostream& operator<<(std::ostream& os, const Planet& planet);

	private:
		FacilitiesList facilities_;
		RoutesList routes_;
		std::weak_ptr<Engine> engine_;
		double lastUpdate_ = 0;
		double timestamp_;
		TypeID typeID_;
		
		double getNextCycleTime();
		void runCycle(double cycleTime);

	};
}
