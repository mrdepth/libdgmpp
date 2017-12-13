//
//  Gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Gang.hpp"

namespace dgmpp {
	Character* Gang::add(std::unique_ptr<Character>&& pilot) {
		assert(pilot != nullptr);
		auto ptr = pilot.get();
		pilots_.push_back(std::move(pilot));
		ptr->parent(this);
		return ptr;
	}
	
	void Gang::remove(Character* pilot) {
		assert(pilot != nullptr);
		pilot->parent(nullptr);
//		if (pilot->isEnabled())
//			pilot->setEnabled(false);
		pilots_.remove_if([=](const auto& i) { return i.get() == pilot; });
	}
	
	std::vector<Character*> Gang::pilots() const {
		std::vector<Character*> result;
		result.reserve(pilots_.size());
		std::transform(pilots_.begin(), pilots_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}
	
	Type* Gang::domain(MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::gang:
				return this;
			default:
				return Type::domain(domain);
		}
	}
	
	void Gang::setEnabled (bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
		
		std::for_each(pilots_.begin(), pilots_.end(), [enabled](auto& i) {
			i->setEnabled(enabled);
		});
	}

}


