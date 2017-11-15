//
//  SDE.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 01.11.2017.
//

#pragma once
#include "Attribute.h"
#include "Type.hpp"
#include <stdexcept>
#include "MetaInfo.hpp"

namespace dgmpp2 {
	namespace SDE {
		extern const std::initializer_list<ref<const MetaInfo::Type>> skills;
		
		template<typename T>
		class NotFound : public std::runtime_error {
		public:
			NotFound (T identifier) : std::runtime_error("id = " + std::to_string(static_cast<int>(identifier))) {};
		};
		
		const MetaInfo::Attribute& get (AttributeID attributeID);
		const MetaInfo::Type& get (TypeID typeID);
	}
}
