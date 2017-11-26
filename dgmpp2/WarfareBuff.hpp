//
//  WarfareBuff.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 26.11.2017.
//

#pragma once
#include "MetaInfo.hpp"

namespace dgmpp2 {
	class Type;
	class Attribute;
	class Effect;
	
	class WarfareBuff {
	public:
		Modifier (const MetaInfo::Modifier& metaInfo, Type& owner, const Effect& effect);
		Modifier (const Modifier& other) = delete;
		Modifier (Modifier&& other) = delete;
		Modifier& operator= (const Modifier& other) = delete;
		Modifier& operator= (Modifier&& other) = delete;
		virtual ~Modifier() = default;
		
		const MetaInfo::Modifier& metaInfo() const { return metaInfo_; }
		Type& owner() const { return owner_; }
		Type* domain() const;
		const Effect& effect() const { return effect_; }
		
		bool match(const Type* type) const;
		Float value() const;
		operator Float() const { return value(); }
		bool needsStackingCheck() const { return needsStackingCheck_; }
		
	private:
		friend class Effect;
		
		const MetaInfo::WarfareBuff&	metaInfo_;
		Type&				owner_;
		const Effect&		effect_;
		Attribute&			modifyingAttribute_;
		bool				needsStackingCheck_;
		
	};
}


