//
//  Effect.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Effect.hpp"

namespace dgmpp2 {
	Effect::Effect(const MetaInfo::Effect& metaInfo, Type& owner) : metaInfo_(metaInfo) {
		for (const auto& info: metaInfo_.modifiers) {
			modifiers_.emplace(modifiers_.end(), info, owner, *this);
		}
	}
	
	//	void Effect::activate() {
	//		assert(isActive_ == false);
	//		for (const auto& modifier: modifiers()) {
	//			if (auto type = modifier.domain()) {
	//				type->addModifier(&modifier);
	//			}
	//		}
	//		isActive_ = true;
	//	}
	
	//	void Effect::deactivate() {
	//		assert(isActive_ == true);
	//		for (const auto& modifier: modifiers()) {
	//			if (auto type = modifier.domain()) {
	//				type->removeModifier(&modifier);
	//			}
	//		}
	//		isActive_ = false;
	//	}
	
}
