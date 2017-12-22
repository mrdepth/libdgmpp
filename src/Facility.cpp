//
//  Facility.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Facility.hpp"
#include <numeric>

namespace dgmpp {
	
//	Facility::Facility(const MetaInfo::Facility& metaInfo, Planet& planet, Identifier identifier)
//	: metaInfo_(metaInfo), planet_(planet), identifier_(identifier) {
//		if (identifier_ <= 0)
//			identifier_ = reinterpret_cast<intptr_t>(this);
//	}

	Facility::Facility(const MetaInfo::Facility& metaInfo, Planet& planet, Identifier identifier)
	: metaInfo_(metaInfo), planet_(planet), identifier_(identifier) {
	
		if (identifier > 0) {
			std::string baseStr = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			int len = static_cast<int>(baseStr.length()) - 1;
			std::string pinName;
			
			for (int i = 0; i < 5; i++) {
				int at = static_cast<int64_t>((identifier_ / pow(len, i))) % len;
				if (i == 2)
					pinName += '-';
				pinName += baseStr.at(at);
			}
			name_ = pinName;
		}
	}

	
	CubicMeter Facility::usedVolume() const noexcept {
		return std::accumulate(commodities_.begin(), commodities_.end(), CubicMeter(0), [](auto sum, const auto& i) {
			return sum + i.second.volume();
		});
	}
	
	Commodity Facility::free(const Commodity& key) noexcept {
		auto output = key;
		output = key.metaInfo().volume > 0 ? std::trunc(freeVolume() / key.metaInfo().volume) : std::numeric_limits<std::size_t>::max();
		return output;
	}
	
    void Facility::add(const dgmpp::Commodity &commodity) {
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
    
    void Facility::extract(const dgmpp::Commodity &commodity) {
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
	
	Commodity Facility::income (TypeID typeID) const {
		auto i = income_.find(typeID);
		if (i != income_.end())
			return i->second;
		else
			return Commodity(typeID);
//			return std::nullopt;
	}

	void Facility::update(std::chrono::seconds time) {
		for (const auto& output: outputs_)
			output.update(time);
	}

}
