//
//  Ship.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Ship.hpp"
#include "SDE.hpp"
#include <numeric>
#include "Errors.hpp"
#include "Character.hpp"

#include <iostream>

namespace dgmpp {
	
	Ship::Ship (const Ship& other): Type(other), capacitor_(*this), heatSimulator_(*this) {
		damagePattern_ = other.damagePattern_;
		name_ = other.name_;
		for (const auto& i: other.modules_) {
			auto module = Module::Create(*std::get<std::unique_ptr<Module>>(i));
			auto ptr = module.get();
			modules_.emplace(ptr->slot(), ptr->socket(), std::move(module));
			ptr->parent_(this);
		}
		
		for (const auto& i: other.drones_) {
			auto drone = Drone::Create(*std::get<std::unique_ptr<Drone>>(i));
			auto ptr = drone.get();
			drones_.emplace(ptr->metaInfo().typeID, ptr->squadronTag(), std::move(drone));
			ptr->parent_(this);
		}
		
		if (auto area = other.area()) {
			area_ = Area::Create(*area);
		}
	}
	
	void Ship::setEnabled (bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
		
		batchUpdates([&]() {
			std::for_each(modules_.begin(), modules_.end(), [enabled](auto& i) {
				std::get<std::unique_ptr<Module>>(i)->setEnabled(enabled);
			});
			std::for_each(drones_.begin(), drones_.end(), [enabled](auto& i) {
				std::get<std::unique_ptr<Drone>>(i)->setEnabled(enabled);
			});
		});
		
	}
	
	Module* Ship::add (std::unique_ptr<Module>&& module, Module::Socket socket, bool ignoringRequirements) {
		assert(module != nullptr);
		
		if (ignoringRequirements || canFit(module.get())) {
			auto state = module->preferredState();
			module->state(dgmpp::Module::State::unknown);
			if (socket == Module::anySocket)
				socket = Module::Socket(0);
			else
				socket = std::min(socket, static_cast<Module::Socket>(totalSlots(module->slot())) - 1);
			
			auto l = modules_.lower_bound(std::make_tuple(module->slot(), socket));
			auto u = modules_.upper_bound(std::make_tuple(module->slot()));
			
			for (; l != u && std::get<Module::Socket>(*l) == socket; l++) {
				socket++;
			}

			auto ptr = module.get();
			ptr->socket(socket);
			modules_.emplace_hint(l, module->slot(), socket, std::move(module));
			
			batchUpdates([&]() {
				ptr->parent_(this);
				
				if (state == Module::State::unknown) {
					if (ptr->canBeActive())
						ptr->state(dgmpp::Module::State::active);
					else if (ptr->canBeOnline())
						ptr->state(dgmpp::Module::State::online);
					else
						ptr->state(dgmpp::Module::State::offline);
				}
				else
					ptr->state(state);
			});
			
//			resetCache();
			return ptr;
		}
		else
			throw CannotFit<Module>(std::move(module));
	}
	
	Drone* Ship::add (std::unique_ptr<Drone>&& drone, Drone::SquadronTag squadronTag) {
		assert(drone != nullptr);
		
		if (canFit(drone.get())) {
			
			if (squadronTag == Drone::anySquadronTag) {
				auto range = equal_range(drones_, std::make_tuple(drone->metaInfo().typeID));
				
				if (range.first != range.second) {
					auto squadron = range.first;
					squadronTag = std::get<Drone::SquadronTag>(*squadron);
					std::size_t size = 1;
					
					auto i = range.first;
					i++;
					
					for (; i != range.second; i++) {
						auto tag = std::get<Drone::SquadronTag>(*i);
						if (tag == squadronTag) {
							size++;
						}
						else {
							if (size < std::get<std::unique_ptr<Drone>>(*squadron)->squadronSize())
								break;
							else {
								size = 1;
								squadronTag = tag;
								squadron = i;
							}
						}
					}
					
					if (size < std::get<std::unique_ptr<Drone>>(*squadron)->squadronSize()) {
						drone->active(std::get<std::unique_ptr<Drone>>(*squadron)->active());
					}
					else
						squadronTag++;

				}
				else {
					squadronTag = 0;
				}
				
			}
			auto ptr = drone.get();
			ptr->squadronTag(squadronTag);
			drones_.emplace(ptr->metaInfo().typeID, squadronTag, std::move(drone));
			ptr->parent_(this);
			return ptr;
		}
		else
			throw CannotFit<Drone>(std::move(drone));
	}
	
	void Ship::remove (Module* module) {
		assert(module != nullptr);

		auto i = modules_.find(std::make_tuple(module->slot(), module->socket(), module));
		assert (i != modules_.end());
		std::get<std::unique_ptr<Module>>(*i)->parent_(nullptr);
		modules_.erase(i);
		
	}
	
	void Ship::remove (Drone* drone) {
		assert(drone != nullptr);
		auto i = drones_.find(std::make_tuple(drone->metaInfo().typeID, drone->squadronTag(), drone));
		assert(i != drones_.end());
		std::get<std::unique_ptr<Drone>>(*i)->parent_(nullptr);
		drones_.erase(i);
	}
	
	bool Ship::canFit(Module* module) {
		assert(module != nullptr);
		
		if (freeSlots(module->slot()) <= 0 || freeHardpoints(module->hardpoint()) <= 0)
			return false;
		
		std::vector<GroupID> groups;
		groups.reserve(SDE::canFitShipGroupAttributes.size());
		
		for (auto id: SDE::canFitShipGroupAttributes) {
			if (auto attribute = module->attribute(id)) {
				groups.push_back(static_cast<GroupID>(static_cast<int>(attribute->value_())));
			}
		}
		
		auto groupID = metaInfo().groupID;
		char matchGroup = 1;
		if (!groups.empty()) {
			matchGroup = std::any_of(groups.begin(), groups.end(), [=](auto i) {return i == groupID;}) ? 0 : -1;
		}
		
		std::vector<TypeID> types;
		types.reserve(SDE::canFitShipTypeAttributes.size());
		
		types.clear();
		
		for (auto id: SDE::canFitShipTypeAttributes) {
			if (auto attribute = module->attribute(id)) {
				types.push_back(static_cast<TypeID>(static_cast<int>(attribute->value_())));
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
				auto subSystemSlot = static_cast<int>(module->attribute(AttributeID::subSystemSlot)->value_());
				auto v = modulesSlice(Module::Slot::subsystem);
				auto isFull = std::any_of(v.begin(), v.end(), [=](const auto& i) {
					return static_cast<int>(std::get<std::unique_ptr<Module>>(i)->attribute(AttributeID::subSystemSlot)->value_()) == subSystemSlot;
				});
				if (isFull)
					return false;
				break;
			}
				
			case Module::Slot::rig: {
				auto rigSize = static_cast<RigSize>(static_cast<int>(module->attribute(AttributeID::rigSize)->value_()));
				if (rigSize != this->rigSize())
					return false;
				break;
			}
			default:
				break;
		}
		
		if (auto attribute = this->attribute(AttributeID::maxGroupFitted)) {
			auto max = static_cast<std::size_t>(attribute->value_());
			auto groupID = module->metaInfo().groupID;
			for (const auto& i: modules_) {
				if (std::get<std::unique_ptr<Module>>(i)->metaInfo().groupID == groupID)
					max--;
				if (max <= 0)
					return false;
			}
		}
		
		if (auto attribute = this->attribute(AttributeID::maxTypeFitted)) {
			auto max = static_cast<std::size_t>(attribute->value_());
			auto typeID = module->metaInfo().typeID;
			for (const auto& i: modules_) {
				if (std::get<std::unique_ptr<Module>>(i)->metaInfo().typeID == typeID)
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
	
	slice<Ship::ModulesContainer::const_iterator> Ship::modulesSlice (Module::Slot slot) const noexcept {
		return equal_range(modules_, std::make_tuple(slot));
//		auto first = std::lower_bound(modules_.cbegin(), modules_.cend(), slot, [](auto a, auto b) {
//			return a->slot() < b;
//		});
//		auto last = std::upper_bound(modules_.cbegin(), modules_.cend(), slot, [](auto a, auto b) {
//			return a < b->slot();
//		});
//		return {first, last};
	}
	
	std::vector<Module*> Ship::modules (Module::Slot slot) const {
		auto s = modulesSlice(slot);
		std::vector<Module*> result;
		result.reserve(s.size());
		std::transform(s.begin(), s.end(), std::back_inserter(result), [](const auto& i) { return std::get<std::unique_ptr<Module>>(i).get(); });
		return result;
	}

	std::vector<Module*> Ship::modules () const {
		std::vector<Module*> result;
		result.reserve(modules_.size());
		std::transform(modules_.begin(), modules_.end(), std::back_inserter(result), [](const auto& i) { return std::get<std::unique_ptr<Module>>(i).get(); });
		return result;
	}

	std::vector<Drone*> Ship::drones () const {
		std::vector<Drone*> result;
		result.reserve(drones_.size());
		std::transform(drones_.begin(), drones_.end(), std::back_inserter(result), [](const auto& i) { return std::get<std::unique_ptr<Drone>>(i).get(); });
		return result;
	}
	
	Area* Ship::area(std::unique_ptr<Area>&& area) {
		if (area_)
			area_->parent_(nullptr);
		if (area) {
			area_ = std::move(area);
			area_->parent_(this);
		}
		else
			area_ = nullptr;
		return area_.get();
	}
	
	bool Ship::factorReload() const noexcept {
		if (auto character = dynamic_cast<Character*>(parent_()))
			return character->factorReload();
			else
				return false;
	}


	Type* Ship::domain (MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::ship :
				return this;
			default:
				return Type::domain(domain);
		}
	}
	
	RaceID Ship::raceID() {
		return static_cast<RaceID>(static_cast<int>(attribute(AttributeID::raceID)->value_()));
	}
	
	std::vector<CategoryID> Ship::supportedDroneCategories() {
		if (attribute(AttributeID::fighterCapacity))
			return {CategoryID::fighter};
		else
			return {CategoryID::drone};
	}
	
	Ship::RigSize Ship::rigSize() {
		return static_cast<RigSize>(static_cast<int>(attribute(AttributeID::rigSize)->value_()));
	}
	
	//Drones
	std::size_t Ship::totalDroneSquadron (Drone::Squadron squadron) {
		switch (squadron) {
			case Drone::Squadron::heavy:
				return static_cast<std::size_t>(attribute(AttributeID::fighterHeavySlots)->value_());
			case Drone::Squadron::light:
				return static_cast<std::size_t>(attribute(AttributeID::fighterLightSlots)->value_());
			case Drone::Squadron::support:
				return static_cast<std::size_t>(attribute(AttributeID::fighterSupportSlots)->value_());
			default:
				if (auto character = domain(MetaInfo::Modifier::Domain::character)) {
					return static_cast<std::size_t>(character->attribute(AttributeID::maxActiveDrones)->value_());
				}
				else
					return 0;
		}
	}
	
	std::size_t Ship::usedDroneSquadron (Drone::Squadron squadron) {
		if (squadron == Drone::Squadron::none) {
			return std::accumulate(drones_.begin(), drones_.end(), 0, [](auto sum, const auto& i) {
				auto& drone = std::get<std::unique_ptr<Drone>>(i);
				if (drone->active() && drone->squadron() == Drone::Squadron::none)
					return sum + 1;
				else
					return sum;
			});
		}
		else {
			std::set<std::pair<TypeID, Drone::SquadronTag>> squadrons;
			for (const auto& i: drones_) {
				auto& drone = std::get<std::unique_ptr<Drone>>(i);
				if (drone->active() && drone->squadron() == squadron)
					squadrons.emplace(drone->metaInfo().typeID, drone->squadronTag());
			}
			return squadrons.size();
		}
		
	}
	
	std::size_t Ship::totalFighterLaunchTubes() {
		return static_cast<std::size_t>(attribute(AttributeID::fighterTubes)->value_());
	}
	
	std::size_t Ship::usedFighterLaunchTubes() {
		std::set<std::pair<TypeID, Drone::SquadronTag>> squadrons;
		for (const auto& i: drones_) {
			auto& drone = std::get<std::unique_ptr<Drone>>(i);
			if (drone->active() && drone->squadron() != Drone::Squadron::none)
				squadrons.emplace(drone->metaInfo().typeID, drone->squadronTag());
		}
		return squadrons.size();
	}

	
	std::size_t Ship::totalSlots (Module::Slot slot) {
		switch (slot) {
			case Module::Slot::hi:
				return static_cast<std::size_t>(attribute(AttributeID::hiSlots)->value_());
			case Module::Slot::med:
				return static_cast<std::size_t>(attribute(AttributeID::medSlots)->value_());
			case Module::Slot::low:
				return static_cast<std::size_t>(attribute(AttributeID::lowSlots)->value_());
			case Module::Slot::rig:
				return static_cast<std::size_t>(attribute(AttributeID::rigSlots)->value_());
			case Module::Slot::subsystem:
				return static_cast<std::size_t>(attribute(AttributeID::maxSubSystems)->value_());
			case Module::Slot::mode:
				return static_cast<std::size_t>(attribute(AttributeID::tacticalModes)->value_());
			case Module::Slot::service:
				return static_cast<std::size_t>(attribute(AttributeID::serviceSlots)->value_());
			default:
				return 0;
		}
	}
	
	std::size_t Ship::totalHardpoints (Module::Hardpoint hardpoint) {
		return usedHardpoints(hardpoint) + freeHardpoints(hardpoint);
	}
	
	std::size_t Ship::freeHardpoints (Module::Hardpoint hardpoint) {
		switch (hardpoint) {
			case Module::Hardpoint::none:
				return std::numeric_limits<std::size_t>::max();
			case Module::Hardpoint::launcher:
				return static_cast<std::size_t>(attribute(AttributeID::launcherSlotsLeft)->value_());
			case Module::Hardpoint::turret:
				return static_cast<std::size_t>(attribute(AttributeID::turretSlotsLeft)->value_());
			default:
				return 0;
		}
	}
	
	std::size_t Ship::usedHardpoints (Module::Hardpoint hardpoint) {
		return std::count_if(modules_.begin(), modules_.end(), [=](const auto& a) {return std::get<std::unique_ptr<Module>>(a)->hardpoint() == hardpoint;});
	}
	
	CalibrationPoints Ship::usedCalibration() {
		auto rigs = modulesSlice(Module::Slot::rig);
		return std::accumulate(rigs.begin(), rigs.end(), CalibrationPoints(0), [](auto sum, const auto& i) {
			return std::get<std::unique_ptr<Module>>(i)->calibrationUse() + sum;
		});
	}
	
	CalibrationPoints Ship::totalCalibration() {
		return attribute(AttributeID::upgradeCapacity)->value_();
	}
	
	GigaJoule Ship::usedPowerGrid() {
		return attribute(AttributeID::powerLoad)->value_();
	}
	
	GigaJoule Ship::totalPowerGrid() {
		return attribute(AttributeID::powerOutput)->value_();
	}
	
	Teraflops Ship::usedCPU() {
		return attribute(AttributeID::cpuLoad)->value_();
	}
	
	Teraflops Ship::totalCPU() {
		return attribute(AttributeID::cpuOutput)->value_();
	}
	
	MegabitsPerSecond Ship::usedDroneBandwidth() {
		return std::accumulate(drones_.begin(), drones_.end(), MegabitsPerSecond(0), [](auto sum, const auto& i) {
			auto& drone = *std::get<std::unique_ptr<Drone>>(i);
			return drone.active() ? sum + drone.attribute(AttributeID::droneBandwidthUsed)->value_() : sum;
		});
	}
	
	MegabitsPerSecond Ship::totalDroneBandwidth() {
		return attribute(AttributeID::droneBandwidth)->value_();
	}
	
	CubicMeter Ship::usedDroneBay() {
		return std::accumulate(drones_.begin(), drones_.end(), CubicMeter(0), [](auto sum, const auto& i) {
			auto& drone = *std::get<std::unique_ptr<Drone>>(i);
			return drone.squadron() == Drone::Squadron::none ? sum + drone.attribute(AttributeID::volume)->value_() : sum;
		});
	}
	
	CubicMeter Ship::totalDroneBay() {
		return attribute(AttributeID::droneCapacity)->value_();
	}
	
	CubicMeter Ship::usedFighterHangar() {
		return std::accumulate(drones_.begin(), drones_.end(), CubicMeter(0), [](auto sum, const auto& i) {
			auto& drone = *std::get<std::unique_ptr<Drone>>(i);
			return drone.squadron() != Drone::Squadron::none ? sum + drone.attribute(AttributeID::volume)->value_() : sum;
		});
	}
	
	CubicMeter Ship::totalFighterHangar() {
		return attribute(AttributeID::fighterCapacity)->value_();
	}
	
	CubicMeter Ship::cargoCapacity() {
		return attribute(AttributeID::capacity)->value_();
	}
	
	CubicMeter Ship::oreHoldCapacity() {
		return attribute(AttributeID::specialOreHoldCapacity)->value_();
	}
	
	//Tank
	Resistances Ship::resistances() {
		Resistances resistances;
		resistances.armor.em		 = 1.0 - attribute(AttributeID::armorEmDamageResonance)->value_();
		resistances.armor.explosive = 1.0 - attribute(AttributeID::armorExplosiveDamageResonance)->value_();
		resistances.armor.kinetic   = 1.0 - attribute(AttributeID::armorKineticDamageResonance)->value_();
		resistances.armor.thermal   = 1.0 - attribute(AttributeID::armorThermalDamageResonance)->value_();
		
		resistances.shield.em		  = 1.0 - attribute(AttributeID::shieldEmDamageResonance)->value_();
		resistances.shield.explosive = 1.0 - attribute(AttributeID::shieldExplosiveDamageResonance)->value_();
		resistances.shield.kinetic   = 1.0 - attribute(AttributeID::shieldKineticDamageResonance)->value_();
		resistances.shield.thermal   = 1.0 - attribute(AttributeID::shieldThermalDamageResonance)->value_();
		
		resistances.hull.em		= 1.0 - attribute(AttributeID::emDamageResonance)->value_();
		resistances.hull.explosive = 1.0 - attribute(AttributeID::explosiveDamageResonance)->value_();
		resistances.hull.kinetic   = 1.0 - attribute(AttributeID::kineticDamageResonance)->value_();
		resistances.hull.thermal   = 1.0 - attribute(AttributeID::thermalDamageResonance)->value_();
		return resistances;
	}
	
	Tank Ship::tank() {
		using namespace std::chrono_literals;
		
		auto capacity = attribute(AttributeID::shieldCapacity)->value_();
		auto rechargeTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute(AttributeID::shieldRechargeRate)->value_()));
		
		auto shieldRecharge  = 10.0 * config::shieldPeakRecharge * (1 - config::shieldPeakRecharge) * capacity;
		HP armorRepair = fabs(attribute(AttributeID::armorDamage)->value_());
		HP hullRepair = fabs(attribute(AttributeID::damage)->value_());
		HP shieldRepair = fabs(attribute(AttributeID::shieldCharge)->value_());

		return {make_rate(shieldRecharge, rechargeTime),
			make_rate(shieldRepair, 1s),
			make_rate(armorRepair, 1s),
			make_rate(hullRepair, 1s)};
	}
	
	Tank Ship::effectiveTank() {
		return tank().effective(resistances(), damagePattern_);
	}
	
	Tank Ship::sustainableTank() {
		if (capacitor().isStable())
			return tank();
		else {
			struct Repairer {
				enum class Type {
					Shield,
					Armor,
					Hull
				};
				Repairer(Module* module, HPPerSecond hpPerSec, rate<GigaJoule, std::chrono::seconds> capPerSec, Float effectivity, Type type)
				: module(module), hpPerSec(hpPerSec), capPerSec(capPerSec), effectivity(effectivity), type(type) {}
				
				Module* module;
				HPPerSecond hpPerSec;
				rate<GigaJoule, std::chrono::seconds> capPerSec;
				Float effectivity;
				Type type;
				
				bool operator< (const Repairer& other) const {
					return effectivity < other.effectivity;
				}
				bool operator> (const Repairer& other) const {
					return effectivity > other.effectivity;
				}
			};

			auto sustainableTank = tank();
			std::set<Repairer, std::greater<>> repairers;
			
			auto me = domain(MetaInfo::Modifier::Domain::character);
			auto capUse = capacitor().use();
			auto capRecharge = capacitor().recharge();
			
			std::tuple<AttributeID, Repairer::Type, HPPerSecond&> t[] = {
				{AttributeID::shieldCharge, Repairer::Type::Shield, sustainableTank.shieldRepair},
				{AttributeID::armorDamage, Repairer::Type::Armor, sustainableTank.armorRepair},
				{AttributeID::damage, Repairer::Type::Hull, sustainableTank.hullRepair}
			};
			
			for (auto& i: t) {
				for (auto modifier: modifiers(attribute(std::get<AttributeID>(i))->metaInfo())) {
					auto isProjected = me && !modifier->owner().isDescendant(*me);
					if (auto module = dynamic_cast<Module*>(&modifier->owner()); module && !isProjected) {
						switch (modifier->metaInfo().association) {
							case MetaInfo::Modifier::Association::addRate:
							case MetaInfo::Modifier::Association::subRate: {
								auto cap = module->capUse();
								auto hp = make_rate(modifier->value(), 1s);
								if (cap.count() > 0 && hp.count() > 0) {
									std::get<2>(i) -= hp;
									capUse -= cap;
									repairers.emplace(module, hp, cap, (hp * 1s) / (cap * 1s), std::get<Repairer::Type>(i));
								}
								break;
							}
							default:
								break;
						}
					}
				}
			}
			
			for (const auto& repairer: repairers) {
				if (capUse > capRecharge)
					break;
				auto sustainability = std::min(Float(1.0), (capRecharge - capUse) / repairer.capPerSec);
				auto amount = repairer.hpPerSec * sustainability;
				switch (repairer.type) {
					case Repairer::Type::Shield:
						sustainableTank.shieldRepair += amount;
						break;
					case Repairer::Type::Armor:
						sustainableTank.armorRepair += amount;
						break;
					case Repairer::Type::Hull:
						sustainableTank.hullRepair += amount;
						break;
					default:
						break;
				}
				capUse += repairer.capPerSec;
			}
			
			return sustainableTank;
		}
	}
	
	Tank Ship::effectiveSustainableTank() {
		return sustainableTank().effective(resistances(), damagePattern_);
	}
	
	HitPoints Ship::hitPoints() {
		return {
			attribute(AttributeID::shieldCapacity)->value_(),
			attribute(AttributeID::armorHP)->value_(),
			attribute(AttributeID::hp)->value_()
		};
	}
	
	HitPoints Ship::effectiveHitPoints() {
		return hitPoints().effective(resistances(), damagePattern_);
	}

	//DPS
	DamageVector Ship::turretsVolley() {
		return std::accumulate(modules_.begin(), modules_.end(), DamageVector(0), [](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() != Module::Hardpoint::launcher)
				return sum + module->volley();
			else
				return sum;
		});
	}
	
	DamageVector Ship::launchersVolley() {
		return std::accumulate(modules_.begin(), modules_.end(), DamageVector(0), [](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() == Module::Hardpoint::launcher)
				return sum + module->volley();
			else
				return sum;
		});
	}
	
	DamageVector Ship::dronesVolley() {
		return std::accumulate(drones_.begin(), drones_.end(), DamageVector(0), [](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Drone>>(i)->volley();
		});
	}
	
	DamagePerSecond Ship::turretsDPS (const HostileTarget& target) {
		return std::accumulate(modules_.begin(), modules_.end(), DamagePerSecond(0), [&target](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() != Module::Hardpoint::launcher)
				return sum + module->dps(target);
			else
				return sum;
		});
	}
	
	DamagePerSecond Ship::launchersDPS (const HostileTarget& target) {
		return std::accumulate(modules_.begin(), modules_.end(), DamagePerSecond(0), [&target](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() == Module::Hardpoint::launcher)
				return sum + module->dps(target);
			else
				return sum;
		});
	}
	
	DamagePerSecond Ship::dronesDPS (const HostileTarget& target) {
		return std::accumulate(drones_.begin(), drones_.end(), DamagePerSecond(0), [&target](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Drone>>(i)->dps(target);
		});
	}

	//Mining
	
	CubicMeterPerSecond Ship::minerYield() {
		return std::accumulate(modules_.begin(), modules_.end(), CubicMeterPerSecond(0), [](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Module>>(i)->miningYield();
		});
	}
	
	CubicMeterPerSecond Ship::droneYield() {
		return std::accumulate(drones_.begin(), drones_.end(), CubicMeterPerSecond(0), [](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Drone>>(i)->miningYield();
		});
	}

	//Mobility
	std::chrono::milliseconds Ship::alignTime() {
		return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(-std::log(0.25) * agility() * mass() / 1'000'000.0 * 1000.0));
	}
	
	AstronomicalUnitsPerSecond Ship::warpSpeed() {
		auto base = AstronomicalUnitsPerSecond(attribute(AttributeID::baseWarpSpeed)->value_());
		auto multiplier = attribute(AttributeID::warpSpeedMultiplier)->value_();
		if (base.count() == 0.0)
			base = AstronomicalUnitsPerSecond(1);
		if (multiplier == 0.0)
			return base;
		else
			return base * multiplier;
	}
	
	AstronomicalUnit Ship::maxWarpDistance() {
		auto capacity = capacitor().capacity();
		auto warpCapacitorNeed = attribute(AttributeID::warpCapacitorNeed)->value_();
		return capacity / (mass() * warpCapacitorNeed);
	}
	
	MetersPerSecond Ship::velocity() {
		return MetersPerSecond(attribute(AttributeID::maxVelocity)->value_());
	}
	
	Meter Ship::signatureRadius() {
		return attribute(AttributeID::signatureRadius)->value_();
	}
	
	Kilogram Ship::mass() {
		return attribute(AttributeID::mass)->value_();
	}
	
	CubicMeter Ship::volume() {
		return attribute(AttributeID::volume)->value_();
	}
	
	Multiplier Ship::agility() {
		return attribute(AttributeID::agility)->value_();
	}
	
	MetersPerSecond Ship::maxVelocityInOrbit(Meter r) {
		using namespace std::chrono_literals;
		
		std::pow(1, 1);
		auto i = agility();
		auto m = mass() / 1'000'000.0;
		auto v = velocity();
		auto i2 = std::pow(i, 2);
		auto m2 = std::pow(m, 2);
		auto r2 = std::pow(r, 2);
		auto r4 = std::pow(r2, 2);
		auto v2 = std::pow(v * 1s, 2);
		return MetersPerSecond(std::sqrt((std::sqrt(4 * i2 * m2 * r2 * v2 + r4) / (2 * i2 * m2)) - r2 / (2 * i2 * m2)));

	}
	
	Meter Ship::orbitRadiusWithTransverseVelocity(MetersPerSecond v) {
		auto i = agility();
		auto m = mass() / 1'000'000.0;
		auto vm = velocity();
		auto v2 = std::pow(v * 1s, 2);
		double s = std::pow(vm * 1s, 2) - v2;
		if (s <= 0)
			return 0;
		return (i * m * v2) / sqrt(s);

	}
	
	Meter Ship::orbitRadiusWithAngularVelocity(RadiansPerSecond v) {
		auto lv = velocity();
		Meter r = 0;
		for (int i = 0; i < 10; i++) {
			r = lv / v;
			lv = maxVelocityInOrbit(r);
			auto av = lv / r;
			if (fabs((av - v) / v) < 0.001)
				break;
		}
		return r;
	}
	
	//Targeting
	std::size_t Ship::maxTargets() {
		auto maxTargets = static_cast<std::size_t>(attribute(AttributeID::maxLockedTargets)->value_());
		if (auto character = domain(MetaInfo::Modifier::Domain::character)) {
			auto maxTargets2 = static_cast<std::size_t>(character->attribute(AttributeID::maxLockedTargets)->value_());
			return std::min(maxTargets, maxTargets2);
		}
		else
			return maxTargets;
	}
	
	Meter Ship::maxTargetRange() {
		return attribute(AttributeID::maxTargetRange)->value_();
	}
	
	Points Ship::scanStrength() {
		return std::accumulate(SDE::scanStrengthAttributes.begin(), SDE::scanStrengthAttributes.end(), Points(0), [&] (auto strength, auto attributeID) {
			return std::max(strength, attribute(attributeID)->value_());
		});
	}
	
	Ship::ScanType Ship::scanType() {
		auto maxStrength = Points(0);
		auto scanType = ScanType::multispectral;
		
		for (auto attributeID: SDE::scanStrengthAttributes) {
			auto strength = attribute(attributeID)->value_();
			if (strength > maxStrength) {
				maxStrength = strength;
				switch (attributeID) {
					case AttributeID::scanRadarStrength:
						scanType = ScanType::radar;
						break;
					case AttributeID::scanLadarStrength:
						scanType = ScanType::ladar;
						break;
					case AttributeID::scanMagnetometricStrength:
						scanType = ScanType::magnetometric;
						break;
					case AttributeID::scanGravimetricStrength:
						scanType = ScanType::gravimetric;
						break;
					default:
						break;
				}
			}
			else if (strength == maxStrength)
				scanType = ScanType::multispectral;
		}
		return scanType;
	}
	
	Meter Ship::probeSize() {
		auto strength = scanStrength();
		return strength > 0 ? signatureRadius() / strength : 0.0;
	}
	
	Millimeter Ship::scanResolution() {
		return attribute(AttributeID::scanResolution)->value_();
	}

	
	
	void Ship::reset() {
//		std::cout << "reset" << std::endl;
		Type::reset();
		isDisallowedAssistanceValue_ = std::nullopt;
		isDisallowedOffenseValue_ = std::nullopt;
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
			for (const auto& i: modulesSlice(slot)) {
				std::get<std::unique_ptr<Module>>(i)->fail(n <= 0);
				n--;
			}
		}
		
		for (const auto& i: modules_) {
			std::get<std::unique_ptr<Module>>(i)->adjustState();
		}
		capacitor_.reset();
		heatSimulator_.reset();
	}
	
	void Ship::project(Module* module) {
		assert(std::find(projectedModules_.begin(), projectedModules_.end(), module) == projectedModules_.end());
		projectedModules_.push_back(module);
	}
	
	void Ship::project(Drone* drone) {
		assert(std::find(projectedDrones_.begin(), projectedDrones_.end(), drone) == projectedDrones_.end());
		projectedDrones_.push_back(drone);
	}
	
	void Ship::removeProjected(Module* module) {
		projectedModules_.remove(module);
	}
	
	void Ship::removeProjected(Drone* drone) {
		projectedDrones_.remove(drone);
	}

	bool Ship::isDisallowedAssistance() {
		if (!isDisallowedAssistanceValue_){
			if (auto attribute = this->attribute(AttributeID::disallowAssistance); attribute->value_() != 0)
				isDisallowedAssistanceValue_ = true;
			else {
				auto i = std::find_if(modules_.begin(), modules_.end(), [](const auto& i) {
					auto module = std::get<std::unique_ptr<Module>>(i).get();
					if (module->state() >= Module::State::active) {
						if (auto attribute = module->attribute(AttributeID::disallowAssistance); attribute && attribute->value_() != 0)
							return true;
						if (module->metaInfo().groupID == GroupID::warpDisruptFieldGenerator && module->charge() != nullptr)
							return true;
					}
					return false;
				});
				isDisallowedAssistanceValue_ = i != modules_.end();
			}
		}
		return *isDisallowedAssistanceValue_;
	}
	
	bool Ship::isDisallowedOffense() {
		if (!isDisallowedOffenseValue_)
		{
			if (auto attribute = this->attribute(AttributeID::disallowOffensiveModifiers); attribute->value_() != 0)
				isDisallowedOffenseValue_ = true;
			else
			{
				auto i = std::find_if(modules_.begin(), modules_.end(), [](const auto& i) {
					auto module = std::get<std::unique_ptr<Module>>(i).get();
					if (module->state() >= Module::State::active) {
						if (auto attribute = module->attribute(AttributeID::disallowOffensiveModifiers); attribute && attribute->value_() != 0)
							return true;
					}
					return false;
				});
				isDisallowedOffenseValue_ = i != modules_.end();
			}
		}
		return *isDisallowedOffenseValue_;
	}

}
