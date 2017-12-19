//
//  Factory.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Facility.hpp"

namespace dgmpp {
	
	class Factory: public Facility {
	public:
		virtual bool configured() const override;

		const MetaInfo::Schematic* schematic() const noexcept { return schematic_; }
		void schematic(SchematicID schematicID);

		std::chrono::seconds launchTime() const noexcept { return launchTime_; }
		void launchTime (std::chrono::seconds value) noexcept { launchTime_ = value; }
		std::optional<std::chrono::seconds> cycleTime() const;
		std::optional<Commodity> output() const;

		virtual Commodity free(const Commodity& key) noexcept override;
		
		const std::list<std::unique_ptr<ProductionState>>& states() const noexcept { return states_; }
		const std::list<std::unique_ptr<ProductionCycle>>& cycles() const noexcept { return cycles_; }

	protected:
		std::list<std::unique_ptr<ProductionState>> states_;
		std::list<std::unique_ptr<ProductionCycle>> cycles_;
		
		using Facility::Facility;
		virtual std::optional<std::chrono::seconds> nextUpdateTime() const noexcept override;
		virtual int priority() const noexcept override;
		virtual void update(std::chrono::seconds time) override;

	private:
		friend class Planet;
		const MetaInfo::Schematic* schematic_ = nullptr;
		
		std::chrono::seconds launchTime_ = std::chrono::seconds::zero();
		std::chrono::seconds startTime_ = std::chrono::seconds::zero();
		std::chrono::seconds productionTime_ = std::chrono::seconds::zero();
		bool updating_ = false;
		
		ProductionCycle* production_ = nullptr;
		
		void schematic(const MetaInfo::Schematic* schematic) noexcept { schematic_ = schematic; }
		void finishCycle(ProductionCycle& cycle, std::chrono::seconds time);
		ProductionCycle* startCycle(std::chrono::seconds time);
	};
	
}
