#pragma once
#include "types.h"

namespace dgmpp {
	
	class AttributePrototype
	{
	public:
		static std::shared_ptr<AttributePrototype> getAttributePrototype(std::shared_ptr<Engine> const& engine, TypeID effectID);

		AttributePrototype(std::shared_ptr<Engine> const& engine, TypeID attributeID);

		TypeID getAttributeID() const {return attributeID_;};
		TypeID getMaxAttributeID() const {return maxAttributeID_;};
		float getDefaultValue() const {return defaultValue_;};
		bool isStackable() const {return isStackable_;};
		bool highIsGood() const {return highIsGood_;};
		const char* getAttributeName() const {return attributeName_.c_str();};
	protected:
	private:
		std::weak_ptr<Engine> engine_;
		TypeID attributeID_;
		TypeID maxAttributeID_;
		float defaultValue_;
		bool isStackable_;
		bool highIsGood_;
		std::string attributeName_;
	};
	
}