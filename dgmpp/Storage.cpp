//
//  Storage.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Storage.h"
#include "Commodity.h"

using namespace dgmpp;

void Storage::addCommodity(std::shared_ptr<Commodity> const& commodity) {
	auto i = commodities_.find(commodity->getTypeID());
	if (i != commodities_.end())
		i->second->add(commodity->getQuantity());
	else
		commodities_[commodity->getTypeID()] = std::make_shared<Commodity>(*commodity);
}

void Storage::extractCommodity(std::shared_ptr<Commodity> const& commodity) {
	auto c = getCommodity(commodity->getTypeID());
	if (c)
		c->extract(commodity->getQuantity());
	else
		throw Commodity::NotEnoughCommodities(std::to_string(-commodity->getQuantity()));
}

std::shared_ptr<Commodity> Storage::getCommodity(TypeID typeID) {
	auto i = commodities_.find(typeID);
	if (i != commodities_.end())
		return i->second;
	else
		return nullptr;
}
