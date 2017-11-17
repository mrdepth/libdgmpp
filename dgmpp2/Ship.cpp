//
//  Ship.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Ship.hpp"

namespace dgmpp2 {
	
	const Module::Socket Module::anySocket = -1;
	
	Module* Ship::add (std::unique_ptr<Module> module, bool forced, Module::Socket socket) {
		assert(module != nullptr);
		
		if (forced || canFit(module.get())) {
			auto state = module->preferredState();
			module->state(dgmpp2::Module::State::unknown);
			
			auto modulePtr = Type::add(std::move(module));
			
			auto v = modules(modulePtr->slot());
			
			auto i = std::lower_bound(v.begin(), v.end(), socket, [](auto a, auto b) {
				return a->socket() < b;
			});
			
			modulePtr->socket(socket);
			
			auto last = v.end();
			if (i < last) {
				for (auto j = i; j < last && (*j)->socket() == socket; j++) {
					(*j)->socket(++socket);
				}
			}
			
			modules_.insert(i, modulePtr);
			
			if (state == Module::State::unknown) {
				if (modulePtr->canBeActive())
					modulePtr->state(dgmpp2::Module::State::active);
				else if (modulePtr->canBeOnline())
					modulePtr->state(dgmpp2::Module::State::online);
				else
					modulePtr->state(dgmpp2::Module::State::offline);
			}
			else
				modulePtr->state(state);
			
			reset();
			return modulePtr;
		}
		else
			throw CannotFit<Module>(std::move(module));
	}
	
	Drone* Ship::add (std::unique_ptr<Drone> drone, Drone::SquadronTag squadronTag) {
		assert(drone != nullptr);
		
		if (canFit(drone.get())) {
			auto dronePtr = Type::add(std::move(drone));
			
			if (squadronTag == Drone::anySquadronTag) {
				auto range = equal_range(drones_, std::make_tuple(dronePtr->metaInfo().typeID));
				
				if (range.first != range.second) {
					auto squadron = range.first;
					squadronTag = std::get<Drone::SquadronTag>(*squadron);
					size_t size = 1;
					
					auto i = range.first;
					i++;
					
					for (; i != range.second; i++) {
						auto tag = std::get<Drone::SquadronTag>(*i);
						if (tag == squadronTag) {
							size++;
						}
						else {
							if (size < std::get<Drone*>(*squadron)->squadronSize())
								break;
							else {
								size = 1;
								squadronTag = tag;
								squadron = i;
							}
						}
					}
					
					if (size < std::get<Drone*>(*squadron)->squadronSize()) {
						drone->active(std::get<Drone*>(*squadron)->active());
					}
					else
						squadronTag++;

				}
				else {
					squadronTag = 0;
				}
				
			}
			
			dronePtr->squadronTag(squadronTag);
			drones_.emplace(dronePtr->metaInfo().typeID, squadronTag, dronePtr);
			return dronePtr;
		}
		else
			throw CannotFit<Drone>(std::move(drone));
	}
	
	void Ship::remove (Module* module) {
		assert(module != nullptr);
		
		auto v = modules(module->slot());
		auto i = std::find(v.begin(), v.end(), module);
		assert(i != v.end());
		modules_.erase(i);
		
		Type::remove(module);
		
	}
	
	void Ship::remove (Drone* drone) {
		assert(drone != nullptr);
		
		auto i = drones_.find(std::make_tuple(drone->metaInfo().typeID, drone->squadronTag(), drone));
		assert(i != drones_.end());
		drones_.erase(i);
		
		Type::remove(drone);
	}
	
	bool Ship::canFit(Module* module) {
		assert(module != nullptr);
		
		if (freeSlots(module->slot()) <= 0 || freeHardpoints(module->hardpoint()) <= 0)
			return false;
		
		auto attr = {
			AttributeID::canFitShipGroup01,
			AttributeID::canFitShipGroup02,
			AttributeID::canFitShipGroup03,
			AttributeID::canFitShipGroup04,
			AttributeID::canFitShipGroup05,
			AttributeID::canFitShipGroup06,
			AttributeID::canFitShipGroup07,
			AttributeID::canFitShipGroup08,
			AttributeID::canFitShipGroup09,
			AttributeID::canFitShipGroup10,
			AttributeID::canFitShipGroup11,
			AttributeID::canFitShipGroup12,
			AttributeID::canFitShipGroup13,
			AttributeID::canFitShipGroup14,
			AttributeID::canFitShipGroup15,
			AttributeID::canFitShipGroup16,
			AttributeID::canFitShipGroup17,
			AttributeID::canFitShipGroup18,
			AttributeID::canFitShipGroup19,
			AttributeID::canFitShipGroup20
		};
		std::vector<GroupID> groups;
		groups.reserve(attr.size());
		
		for (auto id: attr) {
			if (auto attribute = (*module)[id]) {
				groups.push_back(static_cast<GroupID>(attribute->value()));
			}
		}
		
		auto groupID = metaInfo().groupID;
		char matchGroup = 1;
		if (!groups.empty()) {
			matchGroup = std::any_of(groups.begin(), groups.end(), [=](auto i) {return i == groupID;}) ? 0 : -1;
		}
		
		attr = {
			AttributeID::fitsToShipType,
			AttributeID::canFitShipType1,
			AttributeID::canFitShipType2,
			AttributeID::canFitShipType3,
			AttributeID::canFitShipType4,
			AttributeID::canFitShipType5,
			AttributeID::canFitShipType6,
			AttributeID::canFitShipType7,
			AttributeID::canFitShipType8,
			AttributeID::canFitShipType9,
			AttributeID::canFitShipType10,
		};
		std::vector<TypeID> types;
		types.reserve(attr.size());
		
		types.clear();
		
		for (auto id: attr) {
			if (auto attribute = (*module)[id]) {
				types.push_back(static_cast<TypeID>(attribute->value()));
			}
		}
		
		auto typeID = metaInfo().typeID;
		char matchType = 1;
		if (!types.empty()) {
			matchType = std::any_of(types.begin(), types.end(), [=](auto i) {return i == typeID;}) ? 0 : -1;
		}
		
		if ((matchType == -1 && matchGroup == -1) || matchType * matchGroup < 0)
			return false;
		
		switch (module->slot()) {
			case Module::Slot::subsystem: {
				auto subSystemSlot = static_cast<int>((*module)[AttributeID::subSystemSlot]->value());
				auto v = modules(Module::Slot::subsystem);
				auto isFull = std::any_of(v.begin(), v.end(), [=](auto i) {
					return static_cast<int>((*i)[AttributeID::subSystemSlot]->value()) == subSystemSlot;
				});
				if (isFull)
					return false;
				break;
			}
				
			case Module::Slot::rig: {
				auto rigSize = static_cast<int>((*module)[AttributeID::rigSize]->value());
				if (rigSize != this->rigSize())
					return false;
				break;
			}
			default:
				break;
		}
		
		if (auto attribute = (*this)[AttributeID::maxGroupFitted]) {
			auto max = static_cast<size_t>(attribute->value());
			auto groupID = module->metaInfo().groupID;
			for (auto i: modules_) {
				if (i->metaInfo().groupID == groupID)
					max--;
				if (max <= 0)
					return false;
			}
		}
		
		if (auto attribute = (*this)[AttributeID::maxTypeFitted]) {
			auto max = static_cast<size_t>(attribute->value());
			auto typeID = module->metaInfo().typeID;
			for (auto i: modules_) {
				if (i->metaInfo().typeID == typeID)
					max--;
				if (max <= 0)
					return false;
			}
		}
		
		return true;
	}
	
	bool Ship::canFit(Drone* drone) {
		assert(drone != nullptr);
		auto categoryID = drone->metaInfo().categoryID;
		for (auto i: supportedDroneCategories()) {
			if (i == categoryID)
				return true;
		}
		return false;
	}
	
	slice<Ship::ModulesContainer::const_iterator> Ship::modules (Module::Slot slot) const {
		auto first = std::lower_bound(modules_.cbegin(), modules_.cend(), slot, [](auto a, auto b) {
			return a->slot() < b;
		});
		auto last = std::upper_bound(modules_.cbegin(), modules_.cend(), slot, [](auto a, auto b) {
			return a < b->slot();
		});
		return {first, last};
	}
	
	Type* Ship::domain (MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::ship :
				return this;
			default:
				return Type::domain(domain);
		}
	}
	
	std::vector<CategoryID> Ship::supportedDroneCategories() {
		if ((*this)[AttributeID::fighterCapacity])
			return {CategoryID::fighter};
		else
			return {CategoryID::drone};
	}
	
	size_t Ship::totalSlots (Module::Slot slot) {
		switch (slot) {
			case Module::Slot::hi:
				return static_cast<size_t>((*this)[AttributeID::hiSlots]->value());
			case Module::Slot::med:
				return static_cast<size_t>((*this)[AttributeID::medSlots]->value());
			case Module::Slot::low:
				return static_cast<size_t>((*this)[AttributeID::lowSlots]->value());
			case Module::Slot::rig:
				return static_cast<size_t>((*this)[AttributeID::rigSlots]->value());
			case Module::Slot::subsystem:
				return static_cast<size_t>((*this)[AttributeID::maxSubSystems]->value());
			case Module::Slot::mode:
				return static_cast<size_t>((*this)[AttributeID::tacticalModes]->value());
			case Module::Slot::service:
				return static_cast<size_t>((*this)[AttributeID::serviceSlots]->value());
			default:
				return 0;
		}
	}
	
	size_t Ship::totalHardpoints (Module::Hardpoint hardpoint) {
		return usedHardpoints(hardpoint) + freeHardpoints(hardpoint);
	}
	
	size_t Ship::freeHardpoints (Module::Hardpoint hardpoint) {
		switch (hardpoint) {
			case Module::Hardpoint::none:
				return std::numeric_limits<size_t>::max();
			case Module::Hardpoint::launcher:
				return static_cast<size_t>((*this)[AttributeID::launcherSlotsLeft]->value());
			case Module::Hardpoint::turret:
				return static_cast<size_t>((*this)[AttributeID::turretSlotsLeft]->value());
			default:
				return 0;
		}
	}
	
	size_t Ship::usedHardpoints (Module::Hardpoint hardpoint) {
		return std::count_if(modules_.begin(), modules_.end(), [=](auto a) {return a->hardpoint() == hardpoint;});
	}
	
	void Ship::reset() {
//		std::cout << "reset" << std::endl;
		Type::reset();
		const auto slots = {Module::Slot::hi,
			Module::Slot::med,
			Module::Slot::low,
			Module::Slot::rig,
			Module::Slot::subsystem,
			Module::Slot::mode,
			Module::Slot::service,
			Module::Slot::starbaseStructure};
		for (auto slot: slots) {
			auto n = totalSlots(slot);
			for (auto module: modules(slot)) {
				module->setEnabled(n > 0);
				n--;
			}
		}
		
		for (auto module: modules()) {
			module->adjustState();
		}
		capacitor_.reset();
	}
}
