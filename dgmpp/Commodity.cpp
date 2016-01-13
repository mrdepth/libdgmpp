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

Commodity::Commodity(std::shared_ptr<Engine> const& engine, TypeID typeID) : typeID(typeID), quantity(0), volume(0) {
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT volume FROM invTypes WHERE typeID = ? LIMIT 1");
	stmt->bindInt(1, typeID);
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	if (result->next()) {
		volume = result->getDouble(0);
	}
	else {
		throw Item::UnknownTypeIDException(std::to_string(typeID));
	}
}

Commodity::Commodity(const Commodity& other, int32_t quantity) {
	volume = other.volume;
	typeID = other.typeID;
	this->quantity = quantity;
}

void Commodity::add(int32_t quantity) {
	this->quantity += quantity;
}

std::shared_ptr<Commodity> Commodity::extract(int32_t quantity) {
	if (quantity > this->quantity)
		throw  NotEnoughCommodities(std::to_string(this->quantity - quantity));
	else {
		this->quantity -= quantity;
		return std::make_shared<Commodity>(*this, quantity);
	}
}
