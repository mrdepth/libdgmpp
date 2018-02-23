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
	
	Ship::Ship (TypeID typeID): Type(typeID), capacitor_(*this), heatSimulator_(*this) {
		if (!std::any_of(SDE::shipCategories.begin(), SDE::shipCategories.end(), [categoryID = metaInfo().categoryID](const auto& i) { return categoryID == i; })) {
			throw InvalidCategoryID(metaInfo().categoryID);
		}
	}
	
	Ship::Ship (const Ship& other): Type(other), capacitor_(*this), heatSimulator_(*this) {
		damagePatternValue_ = other.damagePatternValue_;
		nameValue_ = other.nameValue_;
		for (const auto& i: other.modulesSet_) {
			auto module = Module::Create(*std::get<std::unique_ptr<Module>>(i));
			auto ptr = module.get();
			modulesSet_.emplace(ptr->slot(), ptr->socket_(), std::move(module));
			ptr->parent_(this);
		}
		
		for (const auto& i: other.dronesSet_) {
			auto drone = Drone::Create(*std::get<std::unique_ptr<Drone>>(i));
			auto ptr = drone.get();
			dronesSet_.emplace(ptr->metaInfo().typeID, ptr->squadronTag_(), std::move(drone));
			ptr->parent_(this);
		}
		
		if (auto area = other.area_()) {
			areaValue_ = Area::Create(*area);
		}
	}
	
	void Ship::setEnabled_ (bool enabled) {
		if (isEnabled_() == enabled)
			return Type::setEnabled_(enabled);
		else
			Type::setEnabled_(enabled);
		
		batchUpdates_([&]() {
			std::for_each(modulesSet_.begin(), modulesSet_.end(), [enabled](auto& i) {
				std::get<std::unique_ptr<Module>>(i)->setEnabled_(enabled);
			});
			std::for_each(dronesSet_.begin(), dronesSet_.end(), [enabled](auto& i) {
				std::get<std::unique_ptr<Drone>>(i)->setEnabled_(enabled);
			});
		});
		
	}
	
	Module* Ship::add_ (std::unique_ptr<Module>&& module, Module::Socket socket, bool ignoringRequirements) {
		assert(module != nullptr);
		
		if (ignoringRequirements || canFit_(module.get())) {
			auto state = module->preferredState_();
			module->state_(dgmpp::Module::State::unknown);
			if (socket == Module::anySocket)
				socket = Module::Socket(0);
			else
				socket = std::min(socket, std::max(static_cast<Module::Socket>(totalSlots_(module->slot())) - 1, 0));
			
			auto l = modulesSet_.lower_bound(std::make_tuple(module->slot(), socket));
			auto u = modulesSet_.upper_bound(std::make_tuple(module->slot()));
			
			for (; l != u && std::get<Module::Socket>(*l) == socket; l++) {
				socket++;
			}

			auto ptr = module.get();
			ptr->socket_(socket);
			modulesSet_.emplace_hint(l, module->slot(), socket, std::move(module));
			
			batchUpdates_([&]() {
				ptr->parent_(this);
				
				if (state == Module::State::unknown) {
					if (ptr->canBeActive_())
						ptr->state_(dgmpp::Module::State::active);
					else if (ptr->canBeOnline_())
						ptr->state_(dgmpp::Module::State::online);
					else
						ptr->state_(dgmpp::Module::State::offline);
				}
				else
					ptr->state_(state);
			});
			
//			resetCache();
			return ptr;
		}
		else
			throw CannotFit<Module>(std::move(module));
	}
	
	Drone* Ship::add_ (std::unique_ptr<Drone>&& drone, Drone::SquadronTag squadronTag) {
		assert(drone != nullptr);
		
		if (canFit(drone.get())) {
			
			auto squadron = drone->squadron();
			auto active = false;
			
			if (totalDroneSquadron(squadron) - usedDroneSquadron(squadron) > 0) {
				if (squadron == Drone::Squadron::none) {
					active = true;
				}
				else if (totalFighterLaunchTubes() - usedFighterLaunchTubes() > 0) {
					active = true;
				}
			}
			
			if (squadronTag == Drone::anySquadronTag) {
				auto range = equal_range(dronesSet_, std::make_tuple(drone->metaInfo().typeID));
				
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
							if (size < std::get<std::unique_ptr<Drone>>(*squadron)->squadronSize_)
								break;
							else {
								size = 1;
								squadronTag = tag;
								squadron = i;
							}
						}
					}
					
					if (size < std::get<std::unique_ptr<Drone>>(*squadron)->squadronSize_) {
						active = std::get<std::unique_ptr<Drone>>(*squadron)->active_();
					}
					else
						squadronTag++;

				}
				else {
					squadronTag = 0;
				}
				
			}
			drone->active(active);
			auto ptr = drone.get();
			ptr->squadronTag_(squadronTag);
			dronesSet_.emplace(ptr->metaInfo().typeID, squadronTag, std::move(drone));
			ptr->parent_(this);
			return ptr;
		}
		else
			throw CannotFit<Drone>(std::move(drone));
	}
	
	void Ship::remove_ (Module* module) {
		assert(module != nullptr);

		auto i = modulesSet_.find(std::make_tuple(module->slot(), module->socket_(), module));
		assert (i != modulesSet_.end());
		std::get<std::unique_ptr<Module>>(*i)->parent_(nullptr);
		modulesSet_.erase(i);
		
	}
	
	void Ship::remove_ (Drone* drone) {
		assert(drone != nullptr);
		auto i = dronesSet_.find(std::make_tuple(drone->metaInfo().typeID, drone->squadronTag_(), drone));
		assert(i != dronesSet_.end());
		std::get<std::unique_ptr<Drone>>(*i)->parent_(nullptr);
		dronesSet_.erase(i);
	}
	
	bool Ship::canFit_(Module* module) {
		assert(module != nullptr);
		
		if (freeSlots_(module->slot()) <= 0 || freeHardpoints_(module->hardpoint()) <= 0)
			return false;
		
		std::vector<GroupID> groups;
		groups.reserve(SDE::canFitShipGroupAttributes.size());
		
		for (auto id: SDE::canFitShipGroupAttributes) {
			if (auto attribute = module->attribute_(id)) {
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
			if (auto attribute = module->attribute_(id)) {
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
				auto subSystemSlot = static_cast<int>(module->attribute_(AttributeID::subSystemSlot)->value_());
				auto v = modulesSlice_(Module::Slot::subsystem);
				auto isFull = std::any_of(v.begin(), v.end(), [=](const auto& i) {
					return static_cast<int>(std::get<std::unique_ptr<Module>>(i)->attribute_(AttributeID::subSystemSlot)->value_()) == subSystemSlot;
				});
				if (isFull)
					return false;
				break;
			}
				
			case Module::Slot::rig: {
				auto rigSize = static_cast<RigSize>(static_cast<int>(module->attribute_(AttributeID::rigSize)->value_()));
				if (rigSize != this->rigSize())
					return false;
				break;
			}
			default:
				break;
		}
		
		if (auto attribute = attribute_(AttributeID::maxGroupFitted)) {
			auto max = static_cast<std::size_t>(attribute->value_());
			auto groupID = module->metaInfo().groupID;
			for (const auto& i: modulesSet_) {
				if (std::get<std::unique_ptr<Module>>(i)->metaInfo().groupID == groupID)
					max--;
				if (max <= 0)
					return false;
			}
		}
		
		if (auto attribute = attribute_(AttributeID::maxTypeFitted)) {
			auto max = static_cast<std::size_t>(attribute->value_());
			auto typeID = module->metaInfo().typeID;
			for (const auto& i: modulesSet_) {
				if (std::get<std::unique_ptr<Module>>(i)->metaInfo().typeID == typeID)
					max--;
				if (max <= 0)
					return false;
			}
		}
		
		return true;
	}
	
	bool Ship::canFit_(Drone* drone) {
		assert(drone != nullptr);
		auto categoryID = drone->metaInfo().categoryID;
		for (auto i: supportedDroneCategories()) {
			if (i == categoryID) {
				return drone->squadron() == Drone::Squadron::none || totalDroneSquadron_(drone->squadron()) > 0;
			}
		}
		
		return false;
	}
	
	slice<Ship::ModulesContainer::const_iterator> Ship::modulesSlice_ (Module::Slot slot) const noexcept {
		return equal_range(modulesSet_, std::make_tuple(slot));
//		auto first = std::lower_bound(modulesSet_.cbegin(), modulesSet_.cend(), slot, [](auto a, auto b) {
//			return a->slot() < b;
//		});
//		auto last = std::upper_bound(modulesSet_.cbegin(), modulesSet_.cend(), slot, [](auto a, auto b) {
//			return a < b->slot();
//		});
//		return {first, last};
	}
	
	std::vector<Module*> Ship::modules_ (Module::Slot slot) const {
		auto s = modulesSlice_(slot);
		std::vector<Module*> result;
		result.reserve(s.size());
		std::transform(s.begin(), s.end(), std::back_inserter(result), [](const auto& i) { return std::get<std::unique_ptr<Module>>(i).get(); });
		return result;
	}

	std::vector<Module*> Ship::modules_ () const {
		std::vector<Module*> result;
		result.reserve(modulesSet_.size());
		std::transform(modulesSet_.begin(), modulesSet_.end(), std::back_inserter(result), [](const auto& i) { return std::get<std::unique_ptr<Module>>(i).get(); });
		return result;
	}

	std::vector<Drone*> Ship::drones_ () const {
		std::vector<Drone*> result;
		result.reserve(dronesSet_.size());
		std::transform(dronesSet_.begin(), dronesSet_.end(), std::back_inserter(result), [](const auto& i) { return std::get<std::unique_ptr<Drone>>(i).get(); });
		return result;
	}
	
	Area* Ship::area_(std::unique_ptr<Area>&& area) {
		if (areaValue_)
			areaValue_->parent_(nullptr);
		if (area) {
			areaValue_ = std::move(area);
			areaValue_->parent_(this);
		}
		else
			areaValue_ = nullptr;
		return areaValue_.get();
	}
	
	bool Ship::factorReload_() const noexcept {
		if (auto character = dynamic_cast<Character*>(parent_()))
			return character->factorReload_();
		else
			return false;
	}


	Type* Ship::domain_ (MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::ship:
				return this;
			default:
				return Type::domain_(domain);
		}
	}
	
	//Drones
	std::size_t Ship::totalDroneSquadron_ (Drone::Squadron squadron) {
		switch (squadron) {
			case Drone::Squadron::heavy:
				if (auto attribute = attribute_(AttributeID::fighterHeavySlots))
					return attribute->value();
				else
					return 0;
			case Drone::Squadron::light:
				if (auto attribute = attribute_(AttributeID::fighterLightSlots))
					return attribute->value();
				else
					return 0;
			case Drone::Squadron::support:
				if (auto attribute = attribute_(AttributeID::fighterSupportSlots))
					return attribute->value();
				else
					return 0;
			case Drone::Squadron::standupHeavy:
				if (auto attribute = attribute_(AttributeID::fighterStandupHeavySlots))
					return attribute->value();
				else
					return 0;
			case Drone::Squadron::standupLight:
				if (auto attribute = attribute_(AttributeID::fighterStandupLightSlots))
					return attribute->value();
				else
					return 0;
			case Drone::Squadron::standupSupport:
				if (auto attribute = attribute_(AttributeID::fighterStandupSupportSlots))
					return attribute->value();
				else
					return 0;
			default:
				if (auto character = domain_(MetaInfo::Modifier::Domain::character)) {
					return static_cast<std::size_t>(character->attribute_(AttributeID::maxActiveDrones)->value_());
				}
				else
					return 5;
		}
	}
	
	std::size_t Ship::usedDroneSquadron_ (Drone::Squadron squadron) {
		if (squadron == Drone::Squadron::none) {
			return std::accumulate(dronesSet_.begin(), dronesSet_.end(), 0, [](auto sum, const auto& i) {
				auto& drone = std::get<std::unique_ptr<Drone>>(i);
				if (drone->active_() && drone->squadron_ == Drone::Squadron::none)
					return sum + 1;
				else
					return sum;
			});
		}
		else {
			std::set<std::pair<TypeID, Drone::SquadronTag>> squadrons;
			for (const auto& i: dronesSet_) {
				auto& drone = std::get<std::unique_ptr<Drone>>(i);
				if (drone->active_() && drone->squadron_ == squadron)
					squadrons.emplace(drone->metaInfo().typeID, drone->squadronTag_());
			}
			return squadrons.size();
		}
		
	}
	
	std::size_t Ship::totalFighterLaunchTubes_() {
		return static_cast<std::size_t>(attribute_(AttributeID::fighterTubes)->value_());
	}
	
	std::size_t Ship::usedFighterLaunchTubes_() {
		std::set<std::pair<TypeID, Drone::SquadronTag>> squadrons;
		for (const auto& i: dronesSet_) {
			auto& drone = std::get<std::unique_ptr<Drone>>(i);
			if (drone->active_() && drone->squadron_ != Drone::Squadron::none)
				squadrons.emplace(drone->metaInfo().typeID, drone->squadronTag_());
		}
		return squadrons.size();
	}

	
	std::size_t Ship::totalSlots_ (Module::Slot slot) {
		switch (slot) {
			case Module::Slot::hi:
				return static_cast<std::size_t>(attribute_(AttributeID::hiSlots)->value_());
			case Module::Slot::med:
				return static_cast<std::size_t>(attribute_(AttributeID::medSlots)->value_());
			case Module::Slot::low:
				return static_cast<std::size_t>(attribute_(AttributeID::lowSlots)->value_());
			case Module::Slot::rig:
				return static_cast<std::size_t>(attribute_(AttributeID::rigSlots)->value_());
			case Module::Slot::subsystem:
				return static_cast<std::size_t>(attribute_(AttributeID::maxSubSystems)->value_());
			case Module::Slot::mode:
				return static_cast<std::size_t>(attribute_(AttributeID::tacticalModes)->value_());
			case Module::Slot::service:
				return static_cast<std::size_t>(attribute_(AttributeID::serviceSlots)->value_());
			default:
				return 0;
		}
	}
	
	std::size_t Ship::totalHardpoints_ (Module::Hardpoint hardpoint) {
		return usedHardpoints_(hardpoint) + freeHardpoints_(hardpoint);
	}
	
	std::size_t Ship::freeHardpoints_ (Module::Hardpoint hardpoint) {
		switch (hardpoint) {
			case Module::Hardpoint::none:
				return std::numeric_limits<std::size_t>::max();
			case Module::Hardpoint::launcher:
				return static_cast<std::size_t>(attribute_(AttributeID::launcherSlotsLeft)->value_());
			case Module::Hardpoint::turret:
				return static_cast<std::size_t>(attribute_(AttributeID::turretSlotsLeft)->value_());
			default:
				return 0;
		}
	}
	
	std::size_t Ship::usedHardpoints_ (Module::Hardpoint hardpoint) {
		return std::count_if(modulesSet_.begin(), modulesSet_.end(), [=](const auto& a) {return std::get<std::unique_ptr<Module>>(a)->hardpoint() == hardpoint;});
	}
	
	CalibrationPoints Ship::usedCalibration_() {
		auto rigs = modulesSlice_(Module::Slot::rig);
		return std::accumulate(rigs.begin(), rigs.end(), CalibrationPoints(0), [](auto sum, const auto& i) {
			return std::get<std::unique_ptr<Module>>(i)->calibrationUse_() + sum;
		});
	}
	
	CalibrationPoints Ship::totalCalibration_() {
		return attribute_(AttributeID::upgradeCapacity)->value_();
	}
	
	GigaJoule Ship::usedPowerGrid_() {
		return attribute_(AttributeID::powerLoad)->value_();
	}
	
	GigaJoule Ship::totalPowerGrid_() {
		return attribute_(AttributeID::powerOutput)->value_();
	}
	
	Teraflops Ship::usedCPU_() {
		return attribute_(AttributeID::cpuLoad)->value_();
	}
	
	Teraflops Ship::totalCPU_() {
		return attribute_(AttributeID::cpuOutput)->value_();
	}
	
	MegabitsPerSecond Ship::usedDroneBandwidth_() {
		return std::accumulate(dronesSet_.begin(), dronesSet_.end(), MegabitsPerSecond(0), [](auto sum, const auto& i) {
			auto& drone = *std::get<std::unique_ptr<Drone>>(i);
			return drone.active_() ? sum + drone.attribute_(AttributeID::droneBandwidthUsed)->value_() : sum;
		});
	}
	
	MegabitsPerSecond Ship::totalDroneBandwidth_() {
		return attribute_(AttributeID::droneBandwidth)->value_();
	}
	
	CubicMeter Ship::usedDroneBay_() {
		return std::accumulate(dronesSet_.begin(), dronesSet_.end(), CubicMeter(0), [](auto sum, const auto& i) {
			auto& drone = *std::get<std::unique_ptr<Drone>>(i);
			return drone.squadron_ == Drone::Squadron::none ? sum + drone.attribute_(AttributeID::volume)->value_() : sum;
		});
	}
	
	CubicMeter Ship::totalDroneBay_() {
		return attribute_(AttributeID::droneCapacity)->value_();
	}
	
	CubicMeter Ship::usedFighterHangar_() {
		return std::accumulate(dronesSet_.begin(), dronesSet_.end(), CubicMeter(0), [](auto sum, const auto& i) {
			auto& drone = *std::get<std::unique_ptr<Drone>>(i);
			return drone.squadron_ != Drone::Squadron::none ? sum + drone.attribute_(AttributeID::volume)->value_() : sum;
		});
	}
	
	CubicMeter Ship::totalFighterHangar_() {
		return attribute_(AttributeID::fighterCapacity)->value_();
	}
	
	CubicMeter Ship::cargoCapacity_() {
		return attribute_(AttributeID::capacity)->value_();
	}
	
	CubicMeter Ship::specialHoldCapacity_() {
		for (auto attributeID: SDE::specialHoldCapacityAttributes) {
			if (auto attribute = attribute_(attributeID))
				return attribute->value();
		}
		return 0;
	}
	
	//Tank
	Resistances Ship::resistances_() {
		Resistances resistances;
		resistances.armor.em		 = 1.0 - attribute_(AttributeID::armorEmDamageResonance)->value_();
		resistances.armor.explosive = 1.0 - attribute_(AttributeID::armorExplosiveDamageResonance)->value_();
		resistances.armor.kinetic   = 1.0 - attribute_(AttributeID::armorKineticDamageResonance)->value_();
		resistances.armor.thermal   = 1.0 - attribute_(AttributeID::armorThermalDamageResonance)->value_();
		
		resistances.shield.em		  = 1.0 - attribute_(AttributeID::shieldEmDamageResonance)->value_();
		resistances.shield.explosive = 1.0 - attribute_(AttributeID::shieldExplosiveDamageResonance)->value_();
		resistances.shield.kinetic   = 1.0 - attribute_(AttributeID::shieldKineticDamageResonance)->value_();
		resistances.shield.thermal   = 1.0 - attribute_(AttributeID::shieldThermalDamageResonance)->value_();
		
		resistances.hull.em		= 1.0 - attribute_(AttributeID::emDamageResonance)->value_();
		resistances.hull.explosive = 1.0 - attribute_(AttributeID::explosiveDamageResonance)->value_();
		resistances.hull.kinetic   = 1.0 - attribute_(AttributeID::kineticDamageResonance)->value_();
		resistances.hull.thermal   = 1.0 - attribute_(AttributeID::thermalDamageResonance)->value_();
		return resistances;
	}
	
	Tank Ship::tank_() {
		using namespace std::chrono_literals;
		
		auto capacity = attribute_(AttributeID::shieldCapacity)->value_();
		auto rechargeTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute_(AttributeID::shieldRechargeRate)->value_()));
		
		auto shieldRecharge  = 10.0 * config::shieldPeakRecharge * (1 - config::shieldPeakRecharge) * capacity;
		HP armorRepair = fabs(attribute_(AttributeID::armorDamage)->value_());
		HP hullRepair = fabs(attribute_(AttributeID::damage)->value_());
		HP shieldRepair = fabs(attribute_(AttributeID::shieldCharge)->value_());

		return {make_rate(shieldRecharge, rechargeTime),
			make_rate(shieldRepair, 1s),
			make_rate(armorRepair, 1s),
			make_rate(hullRepair, 1s)};
	}
	
	Tank Ship::effectiveTank_() {
		return tank_().effective(resistances_(), damagePatternValue_);
	}
	
	Tank Ship::sustainableTank_() {
		if (capacitor().isStable_())
			return tank_();
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

			auto sustainableTank = tank_();
			std::set<Repairer, std::greater<>> repairers;
			
			auto me = domain_(MetaInfo::Modifier::Domain::character);
			auto capUse = capacitor().use_();
			auto capRecharge = capacitor().recharge_();
			
			std::tuple<AttributeID, Repairer::Type, HPPerSecond&> t[] = {
				{AttributeID::shieldCharge, Repairer::Type::Shield, sustainableTank.shieldRepair},
				{AttributeID::armorDamage, Repairer::Type::Armor, sustainableTank.armorRepair},
				{AttributeID::damage, Repairer::Type::Hull, sustainableTank.hullRepair}
			};
			
			for (auto& i: t) {
				for (auto modifier: modifiers_(attribute_(std::get<AttributeID>(i))->metaInfo())) {
					auto isProjected = me && !modifier->owner().isDescendant_(*me);
					if (auto module = dynamic_cast<Module*>(&modifier->owner()); module && !isProjected) {
						switch (modifier->metaInfo().association) {
							case MetaInfo::Modifier::Association::addRate:
							case MetaInfo::Modifier::Association::subRate: {
								auto cap = module->capUse_();
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
	
	Tank Ship::effectiveSustainableTank_() {
		return sustainableTank_().effective(resistances_(), damagePatternValue_);
	}
	
	HitPoints Ship::hitPoints_() {
		return {
			attribute_(AttributeID::shieldCapacity)->value_(),
			attribute_(AttributeID::armorHP)->value_(),
			attribute_(AttributeID::hp)->value_()
		};
	}
	
	HitPoints Ship::effectiveHitPoints_() {
		return hitPoints_().effective(resistances_(), damagePatternValue_);
	}

	//DPS
	DamageVector Ship::turretsVolley_() {
		return std::accumulate(modulesSet_.begin(), modulesSet_.end(), DamageVector(0), [](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() != Module::Hardpoint::launcher)
				return sum + module->volley_();
			else
				return sum;
		});
	}
	
	DamageVector Ship::launchersVolley_() {
		return std::accumulate(modulesSet_.begin(), modulesSet_.end(), DamageVector(0), [](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() == Module::Hardpoint::launcher)
				return sum + module->volley_();
			else
				return sum;
		});
	}
	
	DamageVector Ship::dronesVolley_() {
		return std::accumulate(dronesSet_.begin(), dronesSet_.end(), DamageVector(0), [](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Drone>>(i)->volley_();
		});
	}
	
	DamagePerSecond Ship::turretsDPS_ (const HostileTarget& target) {
		return std::accumulate(modulesSet_.begin(), modulesSet_.end(), DamagePerSecond(0), [&target](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() != Module::Hardpoint::launcher)
				return sum + module->dps_(target);
			else
				return sum;
		});
	}
	
	DamagePerSecond Ship::launchersDPS_ (const HostileTarget& target) {
		return std::accumulate(modulesSet_.begin(), modulesSet_.end(), DamagePerSecond(0), [&target](auto sum, const auto& i) {
			auto module = std::get<std::unique_ptr<Module>>(i).get();
			if (module->hardpoint() == Module::Hardpoint::launcher)
				return sum + module->dps_(target);
			else
				return sum;
		});
	}
	
	DamagePerSecond Ship::dronesDPS_ (const HostileTarget& target) {
		return std::accumulate(dronesSet_.begin(), dronesSet_.end(), DamagePerSecond(0), [&target](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Drone>>(i)->dps_(target);
		});
	}

	//Mining
	
	CubicMeterPerSecond Ship::minerYield_() {
		return std::accumulate(modulesSet_.begin(), modulesSet_.end(), CubicMeterPerSecond(0), [](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Module>>(i)->miningYield_();
		});
	}
	
	CubicMeterPerSecond Ship::droneYield_() {
		return std::accumulate(dronesSet_.begin(), dronesSet_.end(), CubicMeterPerSecond(0), [](auto sum, const auto& i) {
			return sum + std::get<std::unique_ptr<Drone>>(i)->miningYield_();
		});
	}

	//Mobility
	std::chrono::milliseconds Ship::alignTime_() {
		return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(-std::log(0.25) * agility_() * mass_() / 1'000'000.0 * 1000.0));
	}
	
	AstronomicalUnitsPerSecond Ship::warpSpeed_() {
		auto base = AstronomicalUnitsPerSecond(attribute_(AttributeID::baseWarpSpeed)->value_());
		auto multiplier = attribute_(AttributeID::warpSpeedMultiplier)->value_();
		if (base.count() == 0.0)
			base = AstronomicalUnitsPerSecond(1);
		if (multiplier == 0.0)
			return base;
		else
			return base * multiplier;
	}
	
	AstronomicalUnit Ship::maxWarpDistance_() {
		auto capacity = capacitor().capacity_();
		auto warpCapacitorNeed = attribute_(AttributeID::warpCapacitorNeed)->value_();
		return capacity / (mass_() * warpCapacitorNeed);
	}
	
	MetersPerSecond Ship::velocity_() {
		return MetersPerSecond(attribute_(AttributeID::maxVelocity)->value_());
	}
	
	Meter Ship::signatureRadius_() {
		return attribute_(AttributeID::signatureRadius)->value_();
	}
	
	Kilogram Ship::mass_() {
		return attribute_(AttributeID::mass)->value_();
	}
	
	CubicMeter Ship::volume_() {
		return attribute_(AttributeID::volume)->value_();
	}
	
	Multiplier Ship::agility_() {
		return attribute_(AttributeID::agility)->value_();
	}
	
	MetersPerSecond Ship::maxVelocityInOrbit_(Meter r) {
		using namespace std::chrono_literals;
		
		std::pow(1, 1);
		auto i = agility_();
		auto m = mass_() / 1'000'000.0;
		auto v = velocity_();
		auto i2 = std::pow(i, 2);
		auto m2 = std::pow(m, 2);
		auto r2 = std::pow(r, 2);
		auto r4 = std::pow(r2, 2);
		auto v2 = std::pow(v * 1s, 2);
		return MetersPerSecond(std::sqrt((std::sqrt(4 * i2 * m2 * r2 * v2 + r4) / (2 * i2 * m2)) - r2 / (2 * i2 * m2)));

	}
	
	Meter Ship::orbitRadiusWithTransverseVelocity_(MetersPerSecond v) {
		auto i = agility_();
		auto m = mass_() / 1'000'000.0;
		auto vm = velocity_();
		auto v2 = std::pow(v * 1s, 2);
		double s = std::pow(vm * 1s, 2) - v2;
		if (s <= 0)
			return 0;
		return (i * m * v2) / sqrt(s);

	}
	
	Meter Ship::orbitRadiusWithAngularVelocity_(RadiansPerSecond v) {
		auto lv = velocity_();
		Meter r = 0;
		for (int i = 0; i < 10; i++) {
			r = lv / v;
			lv = maxVelocityInOrbit_(r);
			auto av = lv / r;
			if (fabs((av - v) / v) < 0.001)
				break;
		}
		return r;
	}
	
	//Targeting
	std::size_t Ship::maxTargets_() {
		auto maxTargets = static_cast<std::size_t>(attribute_(AttributeID::maxLockedTargets)->value_());
		if (auto character = domain_(MetaInfo::Modifier::Domain::character)) {
			auto maxTargets2 = static_cast<std::size_t>(character->attribute_(AttributeID::maxLockedTargets)->value_());
			return std::min(maxTargets, maxTargets2);
		}
		else
			return maxTargets;
	}
	
	Meter Ship::maxTargetRange_() {
		return attribute_(AttributeID::maxTargetRange)->value_();
	}
	
	Points Ship::scanStrength_() {
		return std::accumulate(SDE::scanStrengthAttributes.begin(), SDE::scanStrengthAttributes.end(), Points(0), [&] (auto strength, auto attributeID) {
			return std::max(strength, attribute_(attributeID)->value_());
		});
	}
	
	Ship::ScanType Ship::scanType_() {
		auto maxStrength = Points(0);
		auto scanType = ScanType::multispectral;
		
		for (auto attributeID: SDE::scanStrengthAttributes) {
			auto strength = attribute_(attributeID)->value_();
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
	
	Meter Ship::probeSize_() {
		auto strength = scanStrength_();
		return strength > 0 ? signatureRadius_() / strength : 0.0;
	}
	
	Millimeter Ship::scanResolution_() {
		return attribute_(AttributeID::scanResolution)->value_();
	}

	
	
	void Ship::reset_() {
//		std::cout << "reset" << std::endl;
		Type::reset_();
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
			auto n = totalSlots_(slot);
			for (const auto& i: modulesSlice_(slot)) {
				std::get<std::unique_ptr<Module>>(i)->fail_(n <= 0);
				n--;
			}
		}
		
		for (const auto& i: modulesSet_) {
			std::get<std::unique_ptr<Module>>(i)->adjustState_();
		}
		capacitor_.reset_();
		heatSimulator_.reset_();
	}
	
	void Ship::project_(Module* module) {
		assert(std::find(projectedModules_.begin(), projectedModules_.end(), module) == projectedModules_.end());
		projectedModules_.push_back(module);
	}
	
	void Ship::project_(Drone* drone) {
		assert(std::find(projectedDrones_.begin(), projectedDrones_.end(), drone) == projectedDrones_.end());
		projectedDrones_.push_back(drone);
	}
	
	void Ship::removeProjected_(Module* module) {
		projectedModules_.remove(module);
	}
	
	void Ship::removeProjected_(Drone* drone) {
		projectedDrones_.remove(drone);
	}

	bool Ship::isDisallowedAssistance_() {
		if (!isDisallowedAssistanceValue_){
			if (auto attribute = attribute_(AttributeID::disallowAssistance); attribute->value_() != 0)
				isDisallowedAssistanceValue_ = true;
			else {
				auto i = std::find_if(modulesSet_.begin(), modulesSet_.end(), [](const auto& i) {
					auto module = std::get<std::unique_ptr<Module>>(i).get();
					if (module->state_() >= Module::State::active) {
						if (auto attribute = module->attribute_(AttributeID::disallowAssistance); attribute && attribute->value_() != 0)
							return true;
						if (module->metaInfo().groupID == GroupID::warpDisruptFieldGenerator && module->charge_() != nullptr)
							return true;
					}
					return false;
				});
				isDisallowedAssistanceValue_ = i != modulesSet_.end();
			}
		}
		return *isDisallowedAssistanceValue_;
	}
	
	bool Ship::isDisallowedOffense_() {
		if (!isDisallowedOffenseValue_)
		{
			if (auto attribute = attribute_(AttributeID::disallowOffensiveModifiers); attribute->value_() != 0)
				isDisallowedOffenseValue_ = true;
			else
			{
				auto i = std::find_if(modulesSet_.begin(), modulesSet_.end(), [](const auto& i) {
					auto module = std::get<std::unique_ptr<Module>>(i).get();
					if (module->state_() >= Module::State::active) {
						if (auto attribute = module->attribute_(AttributeID::disallowOffensiveModifiers); attribute && attribute->value_() != 0)
							return true;
					}
					return false;
				});
				isDisallowedOffenseValue_ = i != modulesSet_.end();
			}
		}
		return *isDisallowedOffenseValue_;
	}

}
