#pragma once
#include "Facility.h"
#include "Schematic.h"

namespace dgmpp {
	class IndustryFacility: public Facility {
	public:
		enum {
			GROUP_ID = 1028
		};
		IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual TypeID getGroupID() const {return GROUP_ID;};
		
		std::shared_ptr<Schematic> setSchematic(TypeID schematicID);
		std::shared_ptr<Schematic> getSchematic() const {return schematic_;};
		
		virtual double getLastLaunchTime() const {return lastLaunchTime_;};
		virtual double getCycleTime() const;
		int32_t getQuantityPerCycle() const;
		void setLastLaunchTime(double lastLaunchTime);
		
		virtual double getCycleEndTime() const;
		virtual void finishCycle(double cycleTime);
		virtual void startCycle(double cycleTime);
		virtual int32_t getFreeStorage(const Commodity& commodity) const;
		virtual int priority() const {return 1;};
	private:
		double lastLaunchTime_;
		std::shared_ptr<Schematic> schematic_;
		bool idle_;
	};
}