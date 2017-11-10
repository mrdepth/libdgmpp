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

namespace dgmpp2 {
	namespace SDE {
		template<typename T>
		class NotFound : public std::runtime_error {
		public:
			NotFound (T identifier) : std::runtime_error("id = " + std::to_string(static_cast<int>(identifier))) {};
		};
		
		const MetaInfo::Attribute& get (AttributeID attributeID);
		const MetaInfo::Type& get (TypeID typeID);
	}
}
