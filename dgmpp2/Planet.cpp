//
//  Planet.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Planet.hpp"
#include "SDE.hpp"
#include "CommandCenter.hpp"
#include "Factory.hpp"
#include "Spaceport.hpp"
#include "ExtractorControlUnit.hpp"

#include <algorithm>

namespace dgmpp2 {
	Facility* Planet::add(TypeID typeID, int64_t identifier) {
		const auto& metaInfo = SDE::facility(typeID);
		Facility* facility = nullptr;
		
		switch (metaInfo.groupID) {
			case GroupID::commandCenters:
				facility = new CommandCenter(metaInfo, *this, identifier);
				break;
			case GroupID::processors:
				facility = new Factory(metaInfo, *this, identifier);
				break;
			case GroupID::storageFacilities:
				facility = new Storage(metaInfo, *this, identifier);
				break;
			case GroupID::spaceports:
				facility = new Spaceport(metaInfo, *this, identifier);
				break;
			case GroupID::extractorControlUnits:
				facility = new ExtractorControlUnit(metaInfo, *this, identifier);
				break;
			default:
				break;
		}
		assert(facility);
		
		facilities_.emplace(facility);
		return facility;
	}
	
	void Planet::remove(Facility* facility) {
		for (auto& route: facility->inputs_)
			route.from_->outputs_.erase(route);
		for (auto& route: facility->outputs_)
			route.to_->inputs_.erase(route);
		
		auto i = facilities_.find(facility);
		assert(i != facilities_.end());
		facilities_.erase(i);
	}
	
	std::vector<Facility*> Planet::facilities() const {
		std::vector<Facility*> result;
		result.reserve(facilities_.size());
		std::transform(facilities_.begin(), facilities_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}
	
	void Planet::add(const Route& route) {
		route.from_->outputs_.insert(route);
		route.to_->inputs_.insert(route);
	}
	
	void Planet::remove(const Route& route) {
		route.from_->outputs_.erase(route);
		route.to_->inputs_.erase(route);
	}
	
	std::optional<std::chrono::seconds> Planet::nextCycleTime() {
		std::optional<std::chrono::seconds> next = std::nullopt;
		for (auto& facility: facilities_) {
			if (auto time = facility->nextUpdateTime(); time && *time >= timestamp_)
				next = next ? std::min(*next, *time) : time;
		}
		return next;
	}
	
	std::chrono::seconds Planet::run() {
		auto endTime = std::chrono::seconds::zero();
		timestamp_ = endTime;
		while(true) {
			if (auto next = nextCycleTime(); next->count() >= 0) {
				timestamp_ = *next;
				for (auto& i: facilities_)
					i->update(timestamp_);
				endTime = *next;
			}
			else
				break;
		}
		
		return endTime;
	}

}
