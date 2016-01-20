//
//  Facility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Facility.h"
#include <cmath>
#include "Planet.h"
#include <sstream>

using namespace dgmpp;

Facility::Facility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier): typeID_(typeID), typeName_(typeName), capacity_(capacity), owner_(owner), identifier_(identifier) {
}

void Facility::addInput(const std::shared_ptr<const Route>& route) {
	inputs_.push_back(route);
}

void Facility::addOutput(const std::shared_ptr<const Route>& route) {
	outputs_.push_back(route);
}

void Facility::removeInput(const std::shared_ptr<const Route>& route) {
	inputs_.remove(route);
}

void Facility::removeOutput(const std::shared_ptr<const Route>& route) {
	outputs_.remove(route);
}

double Facility::getCycleEndTime() const {
	double launchTime = getLaunchTime();
	return launchTime > 0 ? launchTime + getCycleTime() : 0;
}

void Facility::addCommodity(const Commodity& commodity) {
	auto i = commodities_.find(commodity.getTypeID());
	if (i != commodities_.end())
		i->second->add(commodity.getQuantity());
	else
		commodities_[commodity.getTypeID()] = std::make_shared<Commodity>(commodity);
}

void Facility::addCommodity(TypeID typeID, uint32_t quantity) {
	addCommodity(Commodity(getOwner()->getEngine(), typeID, quantity));
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
			list.push_back(std::make_shared<const Commodity>(*commodity.second));
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
	return getCapacity() - getVolume();
}

double Facility::getVolume() const {
	double volume = 0;
	for (auto commodity: commodities_)
		volume += commodity.second->getVolume();
	return volume;
}


std::shared_ptr<const Cycle> Facility::getCycle(double timeStamp) const {
	std::shared_ptr<Cycle> last;
	for (const auto& cycle: cycles_) {
		double from = cycle->getLaunchTime();
		if (timeStamp >= from) {
			double to = cycle->getCycleTime();
			if (timeStamp < to)
				return cycle;
		}
		else
			return last;
		last = cycle;
	}
	return last;
}

std::string Facility::toJSONString() const {
	std::stringstream os;
	os << "\"typeName\":\"" << getTypeName() << "\",";
	if (getCapacity() > 0)
		os << "\"free\":" << getFreeVolume() << ",";
	os << "\"commodities\":[";
	bool isFirst = true;
	for (const auto& commodity: commodities_) {
		if (commodity.second->getQuantity() > 0) {
			if (isFirst)
				isFirst = false;
			else
				os << "," << std::endl;;
			os << *commodity.second;
		}
	}
	os << "]" << std::endl;
	return os.str();
}

std::ostream& dgmpp::operator<<(std::ostream& os, const Facility& facility) {
	return os << "{" << facility.toJSONString() << "}" << std::endl;
}
