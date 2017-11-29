//
//  Factory.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Facility.hpp"

namespace dgmpp2 {
	
	class Factory: public Facility {
	public:
		std::optional<Commodity> output() const;
		
		const MetaInfo::Schematic* schematic() const { return schematic_; }
		void schematic(const MetaInfo::Schematic* schematic) { schematic_ = schematic; }
		void schematic(SchematicID schematicID);
		
	protected:
		using Facility::Facility;
		virtual int priority() const override;
	private:
		friend class Planet;
		const MetaInfo::Schematic* schematic_ = nullptr;
	};
	
}
