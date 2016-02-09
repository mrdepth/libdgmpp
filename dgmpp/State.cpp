//
//  State.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 26.01.16.
//
//

#include "State.h"
#include <sstream>
#include "Commodity.h"

using namespace dgmpp;

State::State(double timestamp) : timestamp_(timestamp) {
	
}

void State::setCommodities(const std::list<const Commodity>& commodities) {
	commodities_.clear();
	std::copy(commodities.begin(), commodities.end(), std::inserter(commodities_, commodities_.begin()));
}

double State::getVolume() const {
	double volume = 0;
	for (auto commodity: commodities_)
		volume += commodity.getVolume();
	return volume;
}

std::string State::toJSONString() const {
	std::stringstream os;
	os << "\"timestamp\":" << static_cast<int64_t> (timestamp_) << ",";
	os << "\"commodities\":[";
	bool isFirst = true;
	for (const auto& commodity: commodities_) {
		if (commodity.getQuantity() > 0) {
			if (isFirst)
				isFirst = false;
			else
				os << "," << std::endl;;
			os << commodity;
		}
	}
	os << "]" << std::endl;
	return os.str();
}

std::ostream& dgmpp::operator<<(std::ostream& os, const State& state) {
	return os << "{" << state.toJSONString() << "}" << std::endl;
}
