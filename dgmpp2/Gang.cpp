//
//  Gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Gang.hpp"

namespace dgmpp2 {
	Character* Gang::add(std::unique_ptr<Character> pilot) {
		assert(pilot != nullptr);
		auto ptr = pilot.get();
		pilots_.push_back(std::move(pilot));
		ptr->parent(this);
		return ptr;
	}
	
	void Gang::remove(Character* pilot) {
		assert(pilot != nullptr);
		if (pilot->isEnabled())
			pilot->setEnabled(false);
		
		pilots_.remove_if([=](const auto& i) { return i.get() == pilot; });
	}
	
	
	Type* Gang::domain(MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::gang:
				return this;
			default:
				return Type::domain(domain);
		}
	}
	
	void Gang::setEnabled (bool enabled) {
		Type::setEnabled(enabled);
		for (auto& pilot: pilots_) {
			if (pilot->isEnabled() != enabled)
				pilot->setEnabled(enabled);
		}
	}

}


