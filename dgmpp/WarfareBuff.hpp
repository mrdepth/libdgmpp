//
//  WarfareBuff.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 26.11.2017.
//

#pragma once
#include "MetaInfo.hpp"
#include "Modifier.hpp"

namespace dgmpp {
	class Type;
	class Attribute;
	class Effect;
	
	class WarfareBuff {
	public:
		WarfareBuff (const MetaInfo::WarfareBuff& metaInfo, Type& owner, Effect& effect);
		WarfareBuff (const WarfareBuff& other) = delete;
		WarfareBuff (WarfareBuff&& other) = delete;
		WarfareBuff& operator= (const WarfareBuff& other) = delete;
		WarfareBuff& operator= (WarfareBuff&& other) = delete;
		virtual ~WarfareBuff() = default;
		
		const MetaInfo::WarfareBuff& metaInfo() const noexcept { return metaInfo_; }
		
		const std::list<Modifier>& modifiers() const noexcept { return modifiers_; };
		Float value() const;
	private:
		friend class Type;
		Type& owner_;
		
		const MetaInfo::WarfareBuff& metaInfo_;
		std::list<Modifier>	modifiers_;


	};
}


