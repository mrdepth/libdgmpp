//
//  Charge.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Charge.hpp"
#include "SDE.hpp"

namespace dgmpp2 {
	
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
			return static_cast<bool>((*this)[i]);
		});
	}
	
	Type* Charge::domain (MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::other:
				return parent();
			default:
				return Type::domain(domain);
		}
	}
	
	Charge::Size Charge::chargeSize() {
		if (auto attribute = (*this)[AttributeID::chargeSize])
			return static_cast<Size>(static_cast<int>(attribute->value()));
		else
			return Size::none;
	}
}
