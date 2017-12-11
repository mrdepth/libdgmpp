#include "AttributePrototype.h"
#include "Engine.h"

using namespace dgmpp;

std::shared_ptr<AttributePrototype> AttributePrototype::getAttributePrototype(std::shared_ptr<Engine> const& engine, AttributeID attributeID) {
	auto& reusableAttributePrototypes = engine->getReusableAttributePrototypes();
	auto i = reusableAttributePrototypes.find(attributeID);
	if (i == reusableAttributePrototypes.end()) {
		auto attributePrototype = std::make_shared<AttributePrototype>(engine, attributeID);
		reusableAttributePrototypes[attributeID] = attributePrototype;
		return attributePrototype;
	}
	else
		return i->second;
}


AttributePrototype::AttributePrototype(std::shared_ptr<Engine> const& engine, AttributeID attributeID) : engine_(engine), attributeID_(attributeID), defaultValue_(0), isStackable_(false)
{
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT stackable, maxAttributeID, defaultValue, highIsGood, attributeName FROM dgmAttributeTypes WHERE attributeID = ?");
	stmt->bindInt(1, static_cast<int>(attributeID_));
	
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	if (result->next()) {
		isStackable_ = result->getInt(0) != 0;
		maxAttributeID_ = static_cast<AttributeID>(result->getInt(1));
		defaultValue_ = static_cast<Float>(result->getDouble(2));
		highIsGood_ = result->getInt(3) != 0;
		attributeName_ = result->getText(4);
	}
}
