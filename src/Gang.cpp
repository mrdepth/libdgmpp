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
		
		for (const auto& i: other.pilots_) {
			auto pilot = Character::Create(*i);
			auto ptr = pilot.get();
			pilots_.emplace_back(std::move(pilot));
			ptr->parent_(this);
			auto otherShip = i->ship_();
			auto myShip = ptr->ship_();
			if (myShip && otherShip) {
				shipsMap.emplace(std::make_pair(otherShip,myShip));
				
				auto myModules = myShip->modules();
				auto j = myModules.begin();
				for (auto m: otherShip->modules()) {
					modulesMap.emplace(std::make_pair(m,*(j++)));
				}
				
				auto myDrones = myShip->drones();
				auto k = myDrones.begin();
				for (auto d: otherShip->drones()) {
					dronesMap.emplace(std::make_pair(d,*(k++)));
				}

			}
		}
		for (const auto& i: other.pilots_) {
			if (auto ship = i->ship_()) {
				for (const auto& j: ship->modules()) {
					if (auto target = j->target()) {
						modulesMap[j]->target(shipsMap[target]);
					}
				}
				for (const auto& j: ship->drones()) {
					if (auto target = j->target_()) {
						dronesMap[j]->target_(shipsMap[target]);
					}
				}
			}
		}
		
		if (auto area = other.area()) {
			area_ = Area::Create(*area);
		}

		setEnabled(other.isEnabled());
	}
	
	Character* Gang::add(std::unique_ptr<Character>&& pilot) {
		assert(pilot != nullptr);
		auto ptr = pilot.get();
		pilots_.push_back(std::move(pilot));
		ptr->parent_(this);
		return ptr;
	}
	
	void Gang::remove(Character* pilot) {
		assert(pilot != nullptr);
		pilot->parent_(nullptr);
//		if (pilot->isEnabled())
//			pilot->setEnabled(false);
		pilots_.remove_if([=](const auto& i) { return i.get() == pilot; });
	}
	
	std::vector<Character*> Gang::pilots() const {
		std::vector<Character*> result;
		result.reserve(pilots_.size());
		std::transform(pilots_.begin(), pilots_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}
	
	Type* Gang::domain(MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::gang:
				return this;
			default:
				return Type::domain(domain);
		}
	}
	
	void Gang::setEnabled (bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
		
		std::for_each(pilots_.begin(), pilots_.end(), [enabled](auto& i) {
			i->setEnabled(enabled);
		});
	}

	Area* Gang::area(std::unique_ptr<Area>&& area) {
		if (area_)
			area_->parent_(nullptr);
		if (area) {
			area_ = std::move(area);
			area_->parent_(this);
		}
		else
			area_ = nullptr;
		for (const auto& pilot: pilots_) {
			if (auto ship = pilot->ship_()) {
				if (area_)
					ship->area(Area::Create(*area_));
				else
					ship->area(nullptr);
			}
		}
		return area_.get();
	}
	
	void Gang::factorReload_(bool factorReload) noexcept {
		factorReloadValue_ = factorReload;
		if (isEnabled())
			resetCache();
	}
}


