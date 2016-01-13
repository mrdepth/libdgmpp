//
//  Storage.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Storage.h"

using namespace dgmpp;

void Storage::addCommodity(std::shared_ptr<Commodity> const& commodity) {
}

void Storage::extractCommodity(std::shared_ptr<Commodity> const& commodity) {
	
}

std::shared_ptr<Commodity> Storage::getCommodity(TypeID typeID) {
	auto i = commodities_.find(typeID);
	if (i != commodities_.end())
		return i->second;
	else
		return nullptr;
}
