//
//  Gang.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Gang.hpp"
#include "Errors.hpp"

namespace dgmpp {
	
	Gang::Gang(const Gang& other): Type(other)  {

		factorReloadValue_ = other.factorReloadValue_;
		std::map<Ship*, std::shared_ptr<Ship>> shipsMap;
		std::map<Module*, Module*> modulesMap;
		std::map<Drone*, Drone*> dronesMap;
		
		for (const auto& i: other.pilotsList_) {
			auto pilot = std::make_shared<Character>(*i);
			pilotsList_.push_back(pilot);
			pilot->parent_(this);
			auto otherShip = i->ship_();
			auto myShip = pilot->ship_();
			if (myShip && otherShip) {
				shipsMap.emplace(std::make_pair(otherShip.get(),myShip));
				
				auto myModules = myShip->modules_();
				auto j = myModules.begin();
				for (auto m: otherShip->modules_()) {
					modulesMap.emplace(std::make_pair(m.get(),j->get()));
                    j++;
				}
				
				auto myDrones = myShip->drones_();
				auto k = myDrones.begin();
				for (auto d: otherShip->drones_()) {
					dronesMap.emplace(std::make_pair(d.get(),k->get()));
                    k++;
				}

			}
		}
		for (const auto& i: other.pilotsList_) {
			if (auto ship = i->ship_()) {
				for (const auto& j: ship->modules_()) {
					if (auto target = j->target_()) {
						modulesMap[j.get()]->target_(shipsMap[target.get()]);
					}
				}
				for (const auto& j: ship->drones_()) {
					if (auto target = j->target_()) {
						dronesMap[j.get()]->target_(shipsMap[target.get()]);
					}
				}
			}
		}
		
		if (auto area = other.area_()) {
			areaValue_ = std::make_shared<Area>(*area);
		}

		setEnabled_(other.isEnabled_());
	}

    Gang::~Gang(){
        for (const auto& i: pilotsList_) {
            i->parent_(nullptr);
        }
        if (areaValue_ != nullptr) {
            areaValue_->parent_(nullptr);
        }
    }
	
    void Gang::add_ (const std::shared_ptr<Character>& pilot) {
		assert(pilot != nullptr);
        assert(pilot->parent() == nullptr);

        pilot->parent_(this);
        pilotsList_.push_back(pilot);
	}
	
	void Gang::remove_(Character* pilot) {
		assert(pilot != nullptr && pilot->parent() == this);
		pilot->parent_(nullptr);
		pilotsList_.remove_if([=](const auto& i) { return i.get() == pilot; });
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

    
    void Gang::area_(const std::shared_ptr<Area>& area) {
        assert(area == nullptr || area->parent() == nullptr);
        if (areaValue_)
            areaValue_->parent_(nullptr);

		if (area) {
			areaValue_ = area;
			areaValue_->parent_(this);
		}
		else
			areaValue_ = nullptr;
		for (const auto& pilot: pilotsList_) {
			if (auto ship = pilot->ship_()) {
				if (areaValue_)
					ship->area_(std::make_shared<Area>(*areaValue_));
				else
					ship->area_(nullptr);
			}
		}
	}
	
	void Gang::factorReload_(bool factorReload) noexcept {
		factorReloadValue_ = factorReload;
		if (isEnabled_())
			resetCache_();
	}
}


