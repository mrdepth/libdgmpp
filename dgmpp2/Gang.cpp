//
//  Gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Gang.hpp"

namespace dgmpp2 {
	Character* Gang::add(std::unique_ptr<Character> pilot) {
		return Type::add(std::move(pilot));
	}
	
	void Gang::remove(Character* pilot) {
		Type::remove(pilot);
	}
	
	std::vector<Character*> Gang::pilots() const {
		const auto& pilots = children();
		std::vector<Character*> v;
		v.reserve(pilots.size());
		for (const auto& i: pilots) {
			if (auto pilot = dynamic_cast<Character*>(i.get())) {
				v.push_back(pilot);
			}
		}
		return v;
	}
	
	
	Type* Gang::domain(MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::gang:
				return this;
			default:
				return Type::domain(domain);
		}
	}
	
}
