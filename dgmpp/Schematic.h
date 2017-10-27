#pragma once
#include "types.h"

namespace dgmpp {
	
	class Schematic {
	public:
		Schematic(std::shared_ptr<Engine> const& engine, SchematicID schematicID);
		double getCycleTime() const {return cycleTime_;};
		const Commodity& getOutput() const {return *output_;};
		const std::list<const Commodity>& getInputs() const {return inputs_;};
		SchematicID getSchematicID() const {return schematicID_;};
	private:
		SchematicID schematicID_;
		double cycleTime_;
		std::string schematicName_;
		std::list<const Commodity> inputs_;
		std::shared_ptr<const Commodity> output_;
	};
}
