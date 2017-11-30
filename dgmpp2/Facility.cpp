//
//  Facility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Facility.hpp"
#include <numeric>

namespace dgmpp2 {
	
	CubicMeter Facility::usedVolume() const {
		return std::accumulate(commodities_.begin(), commodities_.end(), CubicMeter(0), [](auto sum, const auto& i) {
			return sum + i.second.volume();
		});
	}
    
    void Facility::add(const dgmpp2::Commodity &commodity) {
        try {
            commodities_.at(commodity.metaInfo().typeID) += commodity;
        }
        catch (std::out_of_range) {
            commodities_.emplace(commodity.metaInfo().typeID, commodity);
        }
        try {
            income_.at(commodity.metaInfo().typeID) += commodity;
        }
        catch (std::out_of_range) {
            income_.emplace(commodity.metaInfo().typeID, commodity);
        }
    }
    
    void Facility::extract(const dgmpp2::Commodity &commodity) {
        if (commodity.empty())
            return;
        
        try {
            commodities_.at(commodity.metaInfo().typeID) -= commodity;
        }
        catch (std::out_of_range) {
            throw NotEnoughCommodities(commodity.quantity());
        }
    }
    
    std::vector<Commodity> Facility::commodities() {
        std::vector<Commodity> result;
        result.reserve(commodities_.size());
        for (const auto& i: commodities_) {
            if (!i.second.empty())
                result.push_back(i.second);
        }
        return result;
    }
	
	Commodity& Facility::operator[] (TypeID typeID) {
		auto i = commodities_.find(typeID);
		if (i != commodities_.end())
			return i->second;
		else {
			auto i = commodities_.emplace(typeID, Commodity(typeID));
			return i.first->second;
		}
	}
	
	Commodity& Facility::operator[] (const Commodity& key) {
		return (*this)[key.metaInfo().typeID];
	}
	
//	std::optional<Commodity> Facility::commodity (TypeID typeID) const {
//		auto i = commodities_.find(typeID);
//		if (i != commodities_.end())
//			return i->second;
//		else
//			return std::nullopt;
//	}
	
	std::optional<Commodity> Facility::income (TypeID typeID) const {
		auto i = income_.find(typeID);
		if (i != income_.end())
			return i->second;
		else
			return std::nullopt;
	}

}
