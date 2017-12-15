#pragma once
#include "Facility.h"
#include "Schematic.h"
#include "ProductionState.h"

namespace dgmpp {
	class IndustryFacility: public Facility {
	public:

		static const GroupID groupID = GroupID::processors;
		
		IndustryFacility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		virtual GroupID getGroupID() const {return groupID;};
		
		std::shared_ptr<Schematic> setSchematic(SchematicID schematicID);
		std::shared_ptr<Schematic> getSchematic() const {return schematic_;};
		
		virtual double getLaunchTime() const {return launchTime_;};
		virtual double getCycleTime() const;
		uint32_t getQuantityPerCycle() const;
		void setLaunchTime(double launchTime);
		
		virtual uint32_t getFreeStorage(const Commodity& commodity) const;
		
		Commodity getOutput() const;
		virtual bool routed() const;

		virtual void update(double time);

	protected:
		virtual double getNextUpdateTime() const;
		void finishCycle(double cycleTime);
		bool startCycle(double cycleTime);
		virtual int priority() const {return -getOutput().getTier();};
	private:
		double launchTime_;
		double startTime_;
		double productionTime_;
		bool updating_;

		std::shared_ptr<Schematic> schematic_;
		
		std::shared_ptr<ProductionCycle> productionCycle_;

	};
}
