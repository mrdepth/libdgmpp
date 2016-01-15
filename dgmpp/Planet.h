#pragma once
#include "types.h"
#include "Warning.h"

namespace dgmpp {
	class Planet : public std::enable_shared_from_this<Planet> {
	public:
		Planet(std::shared_ptr<Engine> const& engine, TypeID typeID);
		std::shared_ptr<Facility> addFacility(TypeID typeID, int64_t identifier = 0);
		void removeFacility(std::shared_ptr<Facility> const& facility);
		const FacilitiesList& getFacilities() const {return facilities_;};
		std::shared_ptr<Route> addRoute(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier = 0);
		void removeRoute(std::shared_ptr<Route> const& route);
		std::shared_ptr<Engine> getEngine() const;
		std::shared_ptr<Facility> findFacility(int64_t identifier);
		void setLastUpdate(double lastUpdate);
		double getLastUpdate();
		
		double getNextCycleTime();
		void runCycle(double cycleTime);
		void reportWarning(const std::shared_ptr<const Warning>& warning);
		const std::list<std::shared_ptr<const Warning>>& getWarnings() const {return warnings_;};
		
		virtual std::string toJSONString() const;
		friend std::ostream& operator<<(std::ostream& os, const Planet& planet);

	private:
		FacilitiesList facilities_;
		RoutesList routes_;
		std::weak_ptr<Engine> engine_;
		std::list<std::shared_ptr<const Warning>> warnings_;
		double lastUpdate_;

	};
}