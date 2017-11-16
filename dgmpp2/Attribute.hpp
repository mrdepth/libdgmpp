//
//  Attribute.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once

#include <unordered_map>
#include "MetaInfo.hpp"

namespace dgmpp2 {
	class Type;
	
	class Attribute {
	public:
		class Proxy;
		
		Attribute(const Attribute& other) = delete;
		Attribute(Attribute&& other) = delete;
		Attribute& operator=(const Attribute& other) = delete;
		Attribute& operator=(Attribute&& other) = delete;
		~Attribute() = default;
		
		const MetaInfo::Attribute& metaInfo() const {return metaInfo_;}
		Type& owner() const {return owner_;}
		
		Float value();
		//		operator Float() const {return get();}
		
		Attribute& operator= (optional<Float>&& value);
		
	private:
		friend class Type;
		friend class AttributeProxy;
		const MetaInfo::Attribute& metaInfo_;
		Type& owner_;
		Float initialValue_;
		optional<Float> forcedValue_ = nullopt;
		mutable optional<Float> value_ = nullopt;
		optional<Proxy> maxAttribute_ = nullopt;
		
		Attribute(const MetaInfo::Attribute& metaInfo, Float initialValue, Type& owner);
		
		void reset() {value_ = nullopt;}
		
#if DEBUG
		mutable bool recursionFlag_ = false;
#endif
		
	};
	
	using AttributesMap = std::unordered_map<AttributeID, std::unique_ptr<Attribute>>;
	
	class Attribute::Proxy {
	public:
		Proxy(Proxy&& other) = default;
		Proxy(const Proxy& other) = default;
		Proxy& operator=(Proxy&& other) = delete;
		Proxy& operator=(const Proxy& other) = delete;
		
		explicit operator bool() const {
			return attribute_->second != nullptr;
		}
		//		operator Float() const;
		Attribute& operator*() const;
		Attribute* operator->() const {
			return &(**this);
		}
		
		//		Proxy& operator=(Float value) {
		//			this->operator*() = value;
		//			return *this;
		//		}
		
	private:
		Type& owner_;
		AttributesMap::iterator attribute_;
		mutable const MetaInfo::Attribute* metaInfo_ = nullptr;
		friend class Type;
		
		Proxy(Type& owner, AttributesMap::iterator attribute)
		: owner_(owner), attribute_(attribute) {}
		
		const MetaInfo::Attribute& metaInfo() const;
	};
	
}
