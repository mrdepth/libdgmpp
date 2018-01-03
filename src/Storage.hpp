//
//  Storage.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Facility.hpp"

namespace dgmpp {
	
	class Storage: public Facility {
	public:
		
		const std::list<std::unique_ptr<State>>& states() const noexcept { return states_; }

	protected:
		std::list<std::unique_ptr<State>> states_;

		using Facility::Facility;
		
		virtual int priority_() const noexcept override { return -900; }
        virtual void update_ (std::chrono::seconds time) override;
		friend class Planet;
	};
	
}

