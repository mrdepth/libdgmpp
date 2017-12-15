#pragma once
#include "types.h"

namespace dgmpp {
	
	class AttributePrototype
	{
	public:
		static std::shared_ptr<AttributePrototype> getAttributePrototype(std::shared_ptr<Engine> const& engine, AttributeID attributeID);

		AttributePrototype(std::shared_ptr<Engine> const& engine, AttributeID attributeID);

		AttributeID getAttributeID() const {return attributeID_;};
		AttributeID getMaxAttributeID() const {return maxAttributeID_;};
		Float getDefaultValue() const {return defaultValue_;};
		bool isStackable() const {return isStackable_;};
		bool highIsGood() const {return highIsGood_;};
		const char* getAttributeName() const {return attributeName_.c_str();};
	protected:
	private:
		std::weak_ptr<Engine> engine_;
		AttributeID attributeID_;
		AttributeID maxAttributeID_;
		Float defaultValue_;
		bool isStackable_;
		bool highIsGood_;
		std::string attributeName_;
	};
	
}
