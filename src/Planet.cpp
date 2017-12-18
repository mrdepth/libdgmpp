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

namespace dgmpp {
	Facility* Planet::add(TypeID typeID, Facility::Identifier identifier) {
		const auto& metaInfo = SDE::facility(typeID);
		Facility* facility = nullptr;
		
		if (identifier <= 0)
			identifier = facilities_.size() + 1;
		
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
		
		facilities_.emplace_back(facility);
		return facility;
	}
	
	void Planet::remove(Facility* facility) {
		for (auto& route: facility->inputs_)
			route.from->outputs_.erase(route);
		for (auto& route: facility->outputs_)
			route.to->inputs_.erase(route);
		
		auto i = std::find_if(facilities_.begin(), facilities_.end(), [&](const auto& i) { return i.get() == facility; });
//		auto i = facilities_.find(facility);
		assert(i != facilities_.end());
		facilities_.erase(i);
	}
	
	std::vector<Facility*> Planet::facilities() const {
		std::vector<Facility*> result;
		result.reserve(facilities_.size());
//		std::set<Facility*, FacilityCompare> set;
//		std::transform(facilities_.begin(), facilities_.end(), std::inserter(set, set.end()), [](const auto& i) { return i.get(); });
//		std::copy(set.begin(), set.end(), std::back_inserter(result));
		
		std::transform(facilities_.begin(), facilities_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}
	
	Facility* Planet::operator[] (Facility::Identifier key) const {
		auto i = std::find_if(facilities_.begin(), facilities_.end(), [key](const auto& i) { return i->identifier() == key; });
		return i != facilities_.end() ? i->get() : nullptr;
	}

	void Planet::add(const Route& route) {
		if (!route.from || !route.to)
			throw InvalidRoute();
		route.from->outputs_.insert(route);
		route.to->inputs_.insert(route);
	}
	
	void Planet::remove(const Route& route) {
		route.from->outputs_.erase(route);
		route.to->inputs_.erase(route);
	}
	
	std::optional<std::chrono::seconds> Planet::nextCycleTime(const std::set<Facility*, FacilityCompare>& facilities) const noexcept {
		std::optional<std::chrono::seconds> next = std::nullopt;
		for (auto& facility: facilities) {
			if (auto time = facility->nextUpdateTime(); time && *time >= timestamp_)
				next = next ? std::min(*next, *time) : time;
		}
		return next;
	}
	
	std::chrono::seconds Planet::run() {
		auto endTime = std::chrono::seconds::zero();
		timestamp_ = endTime;

		std::set<Facility*, FacilityCompare> facilities;
		for (const auto& i: facilities_) {
			if (i->configured()) {
				facilities.insert(i.get());
			}
		}
		
		while(true) {
			if (timestamp_.count() == 442800)
				assert(1);
			if (auto next = nextCycleTime(facilities); next && next->count() >= 0) {
				timestamp_ = *next;
				for (auto& i: facilities)
					i->update(timestamp_);
				endTime = *next;
			}
			else
				break;
		}
		
		return endTime;
	}

}
