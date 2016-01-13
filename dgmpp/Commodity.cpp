//
//  Commodity.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Commodity.h"
#include "Engine.h"
#include "Item.h"

using namespace dgmpp;

Commodity::Commodity(std::shared_ptr<Engine> const& engine, TypeID typeID) : typeID_(typeID), quantity_(0), volume_(0) {
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT volume, typeName FROM invTypes WHERE typeID = ? LIMIT 1");
	stmt->bindInt(1, typeID);
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	if (result->next()) {
		volume_ = result->getDouble(0);
		typeName_ = std::make_shared<std::string>(result->getText(1));
	}
	else {
		throw Item::UnknownTypeIDException(std::to_string(typeID));
	}
}

Commodity::Commodity(const Commodity& other, int32_t quantity) {
	volume_ = other.volume_;
	typeID_ = other.typeID_;
	typeName_ = other.typeName_;
	quantity_ = quantity;
}

void Commodity::add(int32_t quantity) {
	quantity_ += quantity;
}

std::shared_ptr<Commodity> Commodity::extract(int32_t quantity) {
	if (quantity > quantity_)
		throw  NotEnoughCommodities(std::to_string(quantity_ - quantity));
	else {
		quantity_ -= quantity;
		return std::make_shared<Commodity>(*this, quantity);
	}
}
