//
//  WarfareBuff.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 26.11.2017.
//

#include "WarfareBuff.hpp"
#include "Type.hpp"

namespace dgmpp {
	WarfareBuff::WarfareBuff (const MetaInfo::WarfareBuff& metaInfo, Type& owner, Effect& effect)
	: metaInfo_(metaInfo), owner_(owner) {
		for (const auto info: metaInfo_.modifiers()) {
			modifiers_.emplace_back(*info, owner, effect);
		}
	}
	
	Float WarfareBuff::value() const {
		return owner_.attribute_(metaInfo_.modifyingAttributeID)->value_();
	}
	
}
