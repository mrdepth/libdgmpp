//
//  Gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Gang.hpp"

namespace dgmpp {
	
	Gang::Gang(const Gang& other): Type(other)  {

		factorReloadValue_ = other.factorReloadValue_;
		std::map<Ship*, Ship*> shipsMap;
		std::map<Module*, Module*> modulesMap;
		std::map<Drone*, Drone*> dronesMap;
		
		for (const auto& i: other.pilotsList_) {
			auto pilot = Character::Create(*i);
			auto ptr = pilot.get();
			pilotsList_.emplace_back(std::move(pilot));
			ptr->parent_(this);
			auto otherShip = i->ship_();
			auto myShip = ptr->ship_();
			if (myShip && otherShip) {
				shipsMap.emplace(std::make_pair(otherShip,myShip));
				
				auto myModules = myShip->modules_();
				auto j = myModules.begin();
				for (auto m: otherShip->modules_()) {
					modulesMap.emplace(std::make_pair(m,*(j++)));
				}
				
				auto myDrones = myShip->drones_();
				auto k = myDrones.begin();
				for (auto d: otherShip->drones_()) {
					dronesMap.emplace(std::make_pair(d,*(k++)));
				}

			}
		}
		for (const auto& i: other.pilotsList_) {
			if (auto ship = i->ship_()) {
				for (const auto& j: ship->modules_()) {
					if (auto target = j->target_()) {
						modulesMap[j]->target_(shipsMap[target]);
					}
				}
				for (const auto& j: ship->drones_()) {
					if (auto target = j->target_()) {
						dronesMap[j]->target_(shipsMap[target]);
					}
				}
			}
		}
		
		if (auto area = other.area_()) {
			areaValue_ = Area::Create(*area);
		}

		setEnabled_(other.isEnabled_());
	}
	
	Character* Gang::add_(std::unique_ptr<Character>&& pilot) {
		assert(pilot != nullptr);
		auto ptr = pilot.get();
		pilotsList_.push_back(std::move(pilot));
		ptr->parent_(this);
		return ptr;
	}
	
	void Gang::remove_(Character* pilot) {
		assert(pilot != nullptr);
		pilot->parent_(nullptr);
//		if (pilot->isEnabled())
//			pilot->setEnabled_(false);
		pilotsList_.remove_if([=](const auto& i) { return i.get() == pilot; });
	}
	
	std::vector<Character*> Gang::pilots_() const {
		std::vector<Character*> result;
		result.reserve(pilotsList_.size());
		std::transform(pilotsList_.begin(), pilotsList_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}
	
	Type* Gang::domain_(MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::gang:
				return this;
			default:
				return Type::domain_(domain);
		}
	}
	
	void Gang::setEnabled_ (bool enabled) {
		if (isEnabled_() == enabled)
			return Type::setEnabled_(enabled);
		else
			Type::setEnabled_(enabled);
		
		std::for_each(pilotsList_.begin(), pilotsList_.end(), [enabled](auto& i) {
			i->setEnabled_(enabled);
		});
	}

	Area* Gang::area_(std::unique_ptr<Area>&& area) {
		if (areaValue_)
			areaValue_->parent_(nullptr);
		if (area) {
			areaValue_ = std::move(area);
			areaValue_->parent_(this);
		}
		else
			areaValue_ = nullptr;
		for (const auto& pilot: pilotsList_) {
			if (auto ship = pilot->ship_()) {
				if (areaValue_)
					ship->area_(Area::Create(*areaValue_));
				else
					ship->area_(nullptr);
			}
		}
		return areaValue_.get();
	}
	
	void Gang::factorReload_(bool factorReload) noexcept {
		factorReloadValue_ = factorReload;
		if (isEnabled_())
			resetCache_();
	}
}


