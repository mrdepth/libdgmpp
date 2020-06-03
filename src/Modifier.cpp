//
//  Modifier.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Modifier.hpp"
#include "Type.hpp"

namespace dgmpp {
	
	Modifier::Modifier(const MetaInfo::Modifier& metaInfo, Type& owner, const Effect& effect)
	: metaInfo_(metaInfo), owner_(owner), effect_(effect), modifyingAttribute_(*owner.attribute_(metaInfo.modifyingAttributeID)) {
		switch (owner.metaInfo().categoryID) {
			case CategoryID::module:
			case CategoryID::drone:
			case CategoryID::charge:
			case CategoryID::fighter:
			case CategoryID::starbase:
			case CategoryID::structure:
			case CategoryID::structureModule:
				needsStackingCheck_ = true;
				break;
			default:
				needsStackingCheck_ = false;
		}
	}
	
	Type* Modifier::domain() const noexcept {
		return owner().domain_(metaInfo().domain);
	}
	
	bool Modifier::match(Type* type) const {
		switch (metaInfo_.type) {
			case MetaInfo::Modifier::ModifierType::item:
			case MetaInfo::Modifier::ModifierType::location:
				return true;
			case MetaInfo::Modifier::ModifierType::locationGroup:
				return type->metaInfo().groupID == metaInfo_.require.groupID;
			case MetaInfo::Modifier::ModifierType::locationRequiredSkill: {
				auto owner = type->owner_();
				auto domain = owner_.domain_(metaInfo().domain);
				if (!owner || !domain || !owner->isDescendant_(*domain))
					return false;
				return type->metaInfo().requireSkill(metaInfo_.require.typeID);
			}
			case MetaInfo::Modifier::ModifierType::ownerRequiredSkill:
				return type->metaInfo().requireSkill(metaInfo_.require.typeID);
			case MetaInfo::Modifier::ModifierType::locationRequiredDomainSkill:
				if (auto type = owner_.domain_(metaInfo_.domain))
					return type->metaInfo().requireSkill(type->metaInfo().typeID);
				else
					return false;
			default:
				assert(!"Invalid MetaInfo::Modifier::ModifierType value");
				return false;
		}
	}
	
	Float Modifier::value() const {
		switch (metaInfo_.association) {
				using namespace std::chrono_literals;
				
			case MetaInfo::Modifier::Association::postDiv:
				return 1.0 / modifyingAttribute_.value_();
			case MetaInfo::Modifier::Association::postPercent:
				return 1.0 + modifyingAttribute_.value_() / 100.0;
			case MetaInfo::Modifier::Association::addRate:
			case MetaInfo::Modifier::Association::subRate:
				std::chrono::duration<Float> duration;
				if (auto attr = owner_.attribute_(AttributeID::duration))
					duration = std::chrono::duration<Float, std::milli>(attr->value_());
				else if (auto attr = owner_.attribute_(AttributeID::speed)) {
					duration = std::chrono::duration<Float, std::milli>(attr->value_());
				}
				else {
					duration = 1s;
				}
				return duration > 0.0s ? modifyingAttribute_.value_() / duration.count() : 0.0;
			default:
				return modifyingAttribute_.value_();
		}
		return 0;
	}
}

