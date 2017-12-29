//
//  Effect.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Effect.hpp"
#include "SDE.hpp"

namespace dgmpp {
	Effect::Effect(const MetaInfo::Effect& metaInfo, Type& owner) : metaInfo_(metaInfo), owner_(owner) {
		for (const auto info: metaInfo_.modifiers()) {
			modifiers_.emplace_back(*info, owner, *this);
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
	
	
	void WarfareBuffEffect::setActive(bool active) {
		Effect::setActive(active);
		if (active) {
			warfareBuffs_.clear();
			auto& owner = this->owner();
			for (auto attributeID: SDE::warfareBuffIDAttributes) {
				auto attribute = owner.attribute(attributeID);
				if (auto value = attribute->value_(); value > 0) {
					auto buffID = static_cast<WarfareBuffID>(static_cast<int>(value));
					warfareBuffs_.emplace_back(SDE::get(buffID), owner, *this);
				}
			}
		}
		else {
			warfareBuffs_.clear();
		}
	}
}
