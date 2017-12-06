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
	public:
		
		const std::list<std::unique_ptr<State>>& states() const noexcept { return states_; }

	protected:
		std::list<std::unique_ptr<State>> states_;

		using Facility::Facility;
		
		virtual int priority() const override { return -900; }
        virtual void update(std::chrono::seconds time) override;
	public:
		friend class Planet;
	};
	
}

