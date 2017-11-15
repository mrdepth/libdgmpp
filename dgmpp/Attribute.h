#pragma once
#include "types.h"
#include "AttributePrototype.h"
#include <limits>

#include <iostream>
#include <unordered_map>
#include "MetaInfo.hpp"

namespace dgmpp {

	class Attribute : public std::enable_shared_from_this<Attribute>
	{
	public:
		
		static std::shared_ptr<Attribute> getAttribute(std::shared_ptr<Engine> const& engine, AttributeID attributeID, std::shared_ptr<Item> const& owner, bool isFakeAttribute = false, Float value = std::numeric_limits<Float>::quiet_NaN());

		Attribute(std::shared_ptr<Engine> const& engine, std::shared_ptr<AttributePrototype> const& prototype, std::shared_ptr<Item> const& owner, bool isFakeAttribute, Float value);
		
//		Attribute(std::shared_ptr<Engine> const& engine, TypeID attributeID, TypeID maxAttributeID, Float value, bool isStackable, bool highIsGood, std::shared_ptr<Item> const& owner = nullptr, const char* attributeName = "", bool isFakeAttribute = false);
//		Attribute(std::shared_ptr<Engine> const& engine, TypeID attributeID, std::shared_ptr<Item> const& owner = nullptr, bool isFakeAttribute = false);
		virtual ~Attribute(void);
		std::shared_ptr<Item> getOwner() const;
		AttributeID getAttributeID() const;
		bool isFakeAttribute() const;

		virtual Float getValue();
		virtual Float getInitialValue() const;
		bool isStackable() const;
		bool highIsGood() const;

		virtual void setValue(Float value);
//		virtual Float dec(Float value);
//		virtual Float inc(Float value);
		
		void reset();
		
		const char* getAttributeName() const;
		friend std::ostream& operator<<(std::ostream& os, Attribute& attribute);
	protected:
	private:
		std::weak_ptr<Engine> engine_;
		Float value_;
		Float initialValue_;
		Float forcedValue_;
		bool calculated_;
		bool isFakeAttribute_;
		
		std::weak_ptr<Item> owner_;
		std::shared_ptr<AttributePrototype> prototype_;

		void calculate();

		bool sync;
		uint32_t generation_;
	};

}

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
