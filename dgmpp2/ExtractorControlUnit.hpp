//
//  ExtractorControlUnit.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Facility.hpp"

namespace dgmpp2 {
	
	class ExtractorControlUnit: public Facility {
	public:
		
		
	protected:
		using Facility::Facility;
		virtual int priority() const override { return -1000; }

	public:
		friend class Planet;
	};
	
}


