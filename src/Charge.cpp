//
//  Charge.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Charge.hpp"
#include "SDE.hpp"

namespace dgmpp {
	
	Charge::Charge (TypeID typeID): Type(typeID) {
		const auto& effects = this->effects();
		flags_.requireTarget = std::any_of(effects.begin(), effects.end(), [](const auto& i) {return i->metaInfo().category == MetaInfo::Effect::Category::target;});
		
		flags_.canBeActive = flags_.requireTarget || std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			switch (i->metaInfo().category) {
				case MetaInfo::Effect::Category::active:
				case MetaInfo::Effect::Category::overloaded:
					return true;
				default:
					return false;
			}
		});
		
		flags_.isAssistance = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isAssistance;
		});
		flags_.isOffensive = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isOffensive;
		});

		flags_.dealsDamage = std::any_of(SDE::chargeDamageAttributes.begin(), SDE::chargeDamageAttributes.end(), [&](auto i) {
			return static_cast<bool>(this->attribute(i));
		});
	}
	
	Charge::Charge (const Charge& other): Type(other) {
		flags_ = other.flags_;
	}

	Type* Charge::domain (MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::other:
				return parent_();
			default:
				return Type::domain(domain);
		}
	}
	
	Charge::Size Charge::size() {
		if (auto attribute = this->attribute(AttributeID::chargeSize))
			return static_cast<Size>(static_cast<int>(attribute->value_()));
		else
			return Size::none;
	}
	
}
