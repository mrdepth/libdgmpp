//
//  Facility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Facility.h"
#include <cmath>

using namespace dgmpp;

Facility::Facility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier): typeID_(typeID), typeName_(typeName), capacity_(capacity), owner_(owner), identifier_(identifier) {
}

void Facility::addInput(const Route* route) {
	inputs_.push_back(route);
}

void Facility::addOutput(const Route* route) {
	outputs_.push_back(route);
}

void Facility::removeInput(const Route* route) {
	inputs_.remove(route);
}

void Facility::removeOutput(const Route* route) {
	outputs_.remove(route);
}

double Facility::getCycleEndTime() const {
	return getLastLaunchTime() + getCycleTime();
}

void Facility::addCommodity(const Commodity& commodity) {
	auto i = commodities_.find(commodity.getTypeID());
	if (i != commodities_.end())
		i->second->add(commodity.getQuantity());
	else
		commodities_[commodity.getTypeID()] = std::make_shared<Commodity>(commodity);
}

void Facility::extractCommodity(const Commodity& commodity) {
	auto i = commodities_.find(commodity.getTypeID());
	if (i != commodities_.end())
		i->second->extract(commodity.getQuantity());
	else
		throw Commodity::NotEnoughCommodities(std::to_string(-commodity.getQuantity()));
}

const Commodity& Facility::getCommodity(const Commodity& commodity) const {
	auto i = commodities_.find(commodity.getTypeID());
	if (i != commodities_.end())
		return *i->second;
	else {
		auto c = std::make_shared<Commodity>(commodity, 0);
		commodities_[commodity.getTypeID()] = c;
		return *c;
	}
}

void Facility::clear() {
	commodities_.clear();
}

std::list<std::shared_ptr<const Commodity>> Facility::getCommodities() const {
	std::list<std::shared_ptr<const Commodity>> list;
	for (const auto& commodity: commodities_) {
		if (commodity.second->getQuantity() > 0)
			list.push_back(commodity.second);
	}
	return list;
}

int32_t Facility::getFreeStorage(const Commodity& commodity) const {
	double itemVolume = commodity.getItemVolume();
	if (itemVolume > 0) {
		double free = getFreeVolume();
		return std::trunc(free / itemVolume);
	}
	else
		return std::numeric_limits<int32_t>::max();
}

double Facility::getFreeVolume() const {
	double capacity = getCapacity();
	for (auto commodity: commodities_)
		capacity -= commodity.second->getVolume();
	return capacity;
}
