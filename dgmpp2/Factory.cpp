//
//  Factory.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Factory.hpp"
#include "SDE.hpp"

namespace dgmpp2 {
	
	std::optional<Commodity> Factory::output() const {
		if (schematic_)
			return {Commodity(*schematic_->output.first, schematic_->output.second)};
		else
			return std::nullopt;
	}
	
	void Factory::schematic(SchematicID schematicID) {
		schematic_ = &SDE::get(schematicID);
	}
	
	int Factory::priority() const {
		return schematic_ ? static_cast<int>(schematic_->output.first->tier) : 0;
	}
}
