//
//  WarfareBuff.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 26.11.2017.
//

#include "WarfareBuff.hpp"
#include "Type.hpp"

namespace dgmpp {
	WarfareBuff::WarfareBuff (const MetaInfo::WarfareBuff& metaInfo, Type& owner, AttributeID modifyingAttributeID, Effect& effect)
	: metaInfo_(metaInfo), owner_(owner), modifyingAttributeID_(modifyingAttributeID) {
		for (const auto prototype: metaInfo_.modifiers()) {
            auto info = *prototype;
            info.modifyingAttributeID = modifyingAttributeID_;
            modifiersMetaInfo_.push_back(info);
			modifiers_.emplace_back(modifiersMetaInfo_.back(), owner, effect);
		}
	}
	
	Float WarfareBuff::value() const {
		return owner_.attribute_(modifyingAttributeID_)->value_();
	}
	
}
