//
//  SDE.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 01.11.2017.
//

#pragma once
#include <stdexcept>
#include "Type.hpp"
#include "Attribute.hpp"

namespace dgmpp2 {
	namespace SDE {
		extern const std::initializer_list<ref<const MetaInfo::Type>> skills;
		
		template<typename T>
		class NotFound : public std::runtime_error {
		public:
			NotFound (T identifier) : std::runtime_error("id = " + std::to_string(static_cast<int>(identifier))) {};
		};
		
		extern const MetaInfo::Attribute& get (AttributeID attributeID);
		extern const MetaInfo::Type& get (TypeID typeID);
	}
}
