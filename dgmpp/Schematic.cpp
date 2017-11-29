//
//  Schematic.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Schematic.h"
#include "Engine.h"
#include "Item.h"
#include "Commodity.h"

using namespace dgmpp;

Schematic::Schematic(std::shared_ptr<Engine> const& engine, SchematicID schematicID) : schematicID_(schematicID), cycleTime_(0) {
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT schematicName, cycleTime FROM planetSchematics WHERE schematicID = ? LIMIT 1");
	stmt->bindInt(1, static_cast<int>(schematicID));
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	if (result->next()) {
		schematicName_ = result->getText(0);
		cycleTime_ = result->getDouble(1);
	}
	else {
		throw Item::UnknownTypeIDException(std::to_string(static_cast<int>(schematicID)));
	}
	
	stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT typeID, quantity, isInput FROM planetSchematicsTypeMap WHERE schematicID = ?");
	stmt->bindInt(1, static_cast<int>(schematicID));
	result = engine->getSqlConnector()->exec(stmt);
	while (result->next()) {
		TypeID typeID = static_cast<TypeID>(result->getInt(0));
		double quantity = result->getDouble(1);
		bool isInput = result->getInt(2);
		Commodity commodity (engine, typeID, quantity);
		if (isInput)
			inputs_.push_back(commodity);
		else
			output_ = std::make_shared<Commodity>(commodity);
	}
}
