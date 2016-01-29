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

Commodity Commodity::InvalidCommodity() {
	return Commodity(nullptr, 0);
}

Commodity::Commodity(std::shared_ptr<Engine> const& engine, TypeID typeID, uint32_t quantity) : typeID_(typeID), quantity_(quantity), volume_(0), tier_(TIER_UNKNOWN) {
	if (engine) {
		auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT volume, typeName FROM invTypes WHERE typeID = ? LIMIT 1");
		stmt->bindInt(1, typeID);
		std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
		if (result->next()) {
			volume_ = result->getDouble(0);
			typeName_ = std::make_shared<std::string>(result->getText(1));
			auto tier = engine->getCommodityTiers().find(typeID);
			tier_ = tier != engine->getCommodityTiers().end() ? tier->second : TIER_UNKNOWN;
		}
		else {
			throw Item::UnknownTypeIDException(std::to_string(typeID));
		}
	}
}

Commodity::Commodity(const Commodity& other, uint32_t quantity) {
	volume_ = other.volume_;
	typeID_ = other.typeID_;
	typeName_ = other.typeName_;
	quantity_ = quantity;
	tier_ = other.tier_;
}

Commodity::Commodity(const Commodity& other) : Commodity(other, other.getQuantity()) {
}

void Commodity::add(uint32_t quantity) {
	quantity_ += quantity;
}

void Commodity::extract(uint32_t quantity) {
	if (quantity > quantity_)
		throw  NotEnoughCommodities(std::to_string(quantity_ - quantity));
	else
		quantity_ -= quantity;
}

bool Commodity::operator==(const Commodity& other) const {
	return typeID_ == other.typeID_ && quantity_ == other.quantity_;
}

bool Commodity::operator!=(const Commodity& other) const {
	return !operator==(other);
}

std::ostream& dgmpp::operator<<(std::ostream& os, const Commodity& commodity) {
	return os << "{\"typeName\":\"" << commodity.getTypeName() << "\", \"quantity\":" << commodity.getQuantity() << "}";
}

Commodity Commodity::operator+(const Commodity& other) {
	if (typeID_ != getTypeID())
		throw DifferentCommoditiesTypeIDs(std::to_string(other.getTypeID()));
	return Commodity(other, quantity_ + other.getQuantity());
}

Commodity Commodity::operator-(const Commodity& other) {
	if (typeID_ != getTypeID())
		throw DifferentCommoditiesTypeIDs(std::to_string(other.getTypeID()));
	else if (getQuantity() < quantity_)
		throw  NotEnoughCommodities(std::to_string(quantity_ - other.getQuantity()));
	return Commodity(other, quantity_ - other.getQuantity());
}
