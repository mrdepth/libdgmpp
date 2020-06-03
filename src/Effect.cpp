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
	
	
	void WarfareBuffEffect::setActive_(bool active) {
		Effect::setActive_(active);
		if (active) {
			warfareBuffs_.clear();
			auto& owner = this->owner();
			for (auto attributeID: SDE::warfareBuffIDAttributes) {
				auto attribute = owner.attribute_(attributeID);
				if (auto value = attribute->value_(); value > 0) {
					auto buffID = static_cast<WarfareBuffID>(static_cast<int>(value));
                    AttributeID modifyingAttributeID = AttributeID::none;
                    switch (attributeID) {
                        case AttributeID::warfareBuff1ID:
                            modifyingAttributeID = AttributeID::warfareBuff1Value;
                            break;
                        case AttributeID::warfareBuff2ID:
                            modifyingAttributeID = AttributeID::warfareBuff2Value;
                            break;
                        case AttributeID::warfareBuff3ID:
                            modifyingAttributeID = AttributeID::warfareBuff3Value;
                            break;
                        case AttributeID::warfareBuff4ID:
                            modifyingAttributeID = AttributeID::warfareBuff4Value;
                            break;
                        default:
                            continue;
                    }
					warfareBuffs_.emplace_back(SDE::get(buffID), owner, modifyingAttributeID, *this);
				}
			}
		}
		else {
			warfareBuffs_.clear();
		}
	}
}
