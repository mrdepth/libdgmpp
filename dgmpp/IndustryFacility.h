#pragma once
#include "Facility.h"
#include "Storage.h"
#include "Schematic.h"

namespace dgmpp {
	class IndustryFacility: public Facility, public Storage {
	public:
		enum {
			GROUP_ID = 1028
		};
		IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() {return GROUP_ID;};
		
		std::shared_ptr<Schematic> setSchematic(TypeID schematicID);
		std::shared_ptr<Schematic> getSchematic() const {return schematic_;};
		
		void setLastLaunchTime(double lastLaunchTime) {lastLaunchTime_ = lastLaunchTime;};
		double getLastLaunchTime() const {return lastLaunchTime_;};
		double getCycleTime() const;
		double getQuantityPerCycle() const;
	private:
		double lastLaunchTime_;
		std::shared_ptr<Schematic> schematic_;
	};
}