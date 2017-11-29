//
//  Storage.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Facility.hpp"

namespace dgmpp2 {
	
	class Storage: public Facility {
	protected:
		using Facility::Facility;
		
		virtual int priority() const override { return -900; }
        virtual void update(std::chrono::seconds time) override;
	public:
		friend class Planet;
	};
	
}

