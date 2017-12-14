//
//  Attribute.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once

#include <unordered_map>
#include "MetaInfo.hpp"

namespace dgmpp {
	class Type;
	
	using AttributesMap = std::unordered_map<AttributeID, std::unique_ptr<class Attribute>>;

	class Attribute {
	public:
		class Proxy {
		public:
			Proxy(Proxy&& other) = default;
			Proxy(const Proxy& other) = default;
			Proxy& operator=(Proxy&& other) = default;
			Proxy& operator=(const Proxy& other) = default;
			
			explicit operator bool() const {
				return attribute_->second != nullptr;
			}

			Attribute& operator*() const;
			Attribute* operator->() const { return get(); }
			Attribute* get() const { return &(**this); }
			
		private:
			Type* owner_;
			AttributesMap::iterator attribute_;
			mutable const MetaInfo::Attribute* metaInfo_ = nullptr;
			friend class Type;
			
			Proxy(Type& owner, AttributesMap::iterator attribute)
			: owner_(&owner), attribute_(attribute) {}
			
			const MetaInfo::Attribute& metaInfo() const;
		};
		
		Attribute (const Attribute& other) = delete;
		Attribute (Attribute&& other) = delete;
		Attribute& operator= (const Attribute& other) = delete;
		Attribute& operator= (Attribute&& other) = delete;
		~Attribute() = default;
		
		const MetaInfo::Attribute& metaInfo() const noexcept {return metaInfo_;}
		Type& owner() const noexcept {return owner_;}
		
		Float value();
		Float initialValue() const { return initialValue_; }
		
		Attribute& operator= (std::optional<Float>&& value) noexcept;
		
	private:
		friend class Type;
		friend class AttributeProxy;
		const MetaInfo::Attribute& metaInfo_;
		Type& owner_;
		Float initialValue_;
		std::optional<Float> forcedValue_ = std::nullopt;
		mutable std::optional<Float> value_ = std::nullopt;
		std::optional<Proxy> maxAttribute_ = std::nullopt;
		
		Attribute(const MetaInfo::Attribute& metaInfo, Float initialValue, Type& owner);
		
		void reset() noexcept {value_ = std::nullopt;}
		
#if DEBUG
		mutable bool recursionFlag_ = false;
#endif
		
	};
}
