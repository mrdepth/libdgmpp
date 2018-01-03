//
//  Module.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Module.hpp"
#include "Ship.hpp"
#include "SDE.hpp"
#include "Errors.hpp"

namespace dgmpp {
	using namespace std::chrono_literals;

	const Module::Socket Module::anySocket = -1;
	
	Module::Module (TypeID typeID) : Type(typeID) {

		flags_.canBeOnline = effect_(EffectID::online) != nullptr || effect_(EffectID::onlineForStructures);
		
		flags_.canBeOverloaded = std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::overloaded;
		});
		
		flags_.requireTarget = std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target;
		});
		
		flags_.canBeActive = flags_.canBeOverloaded || flags_.requireTarget || std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::active;
		});
		
		flags_.fail = false;
		
		flags_.forceReload = metaInfo().groupID == GroupID::capacitorBooster;
//		flags_.factorReload = false;
		
		if (effect_(EffectID::loPower))
			slot_ = Module::Slot::low;
		else if (effect_(EffectID::medPower))
			slot_ = Module::Slot::med;
		else if (effect_(EffectID::hiPower))
			slot_ = Module::Slot::hi;
		else if (effect_(EffectID::rigSlot))
			slot_ = Module::Slot::rig;
		else if (effect_(EffectID::subSystem))
			slot_ = Module::Slot::subsystem;
		else if (effect_(EffectID::tacticalMode))
			slot_ = Module::Slot::mode;
		else if (metaInfo().categoryID == CategoryID::starbase)
			slot_ = Module::Slot::starbaseStructure;
		else if (effect_(EffectID::serviceSlot))
			slot_ = Module::Slot::service;
		else
			slot_ = Module::Slot::none;
		
		if (effect_(EffectID::turretFitted))
			hardpoint_ = Module::Hardpoint::turret;
		else if (effect_(EffectID::launcherFitted))
			hardpoint_ = Module::Hardpoint::launcher;
		else
			hardpoint_ = Module::Hardpoint::none;
		
		for (auto attributeID : SDE::chargeGroupAttributeIDs) {
			if (auto groupIDAttribute = attribute_(attributeID)) {
				GroupID groupID = static_cast<GroupID>(static_cast<int>(groupIDAttribute->value_()));
				if (groupID != GroupID::none) {
					chargeGroups_.push_back(groupID);
					if (groupID == GroupID::capacitorBoosterCharge || groupID == GroupID::naniteRepairPaste)
						flags_.forceReload = true;
				}
			}
		}
		chargeGroups_.shrink_to_fit();
		std::sort(chargeGroups_.begin(), chargeGroups_.end());
		
		if (std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			switch (i->metaInfo().effectID) {
				case EffectID::miningLaser:
				case EffectID::targetAttack:
				case EffectID::useMissiles:
					return true;
				default:
					return false;
			}
		})) {
			defaultReloadTime_ = std::chrono::seconds(1);
		}
		else if (std::any_of(effects_.begin(), effects_.end(), [](const auto& i) {
			switch (i->metaInfo().effectID) {
				case EffectID::powerBooster:
				case EffectID::projectileFired:
					return true;
				default:
					return false;
			}
		})) {
			defaultReloadTime_ = std::chrono::seconds(10);
		}
	}
	
	Module::Module (const Module& other): Type(other) {
		flags_ = other.flags_;
		slot_ = other.slot_;
		hardpoint_ = other.hardpoint_;
		chargeGroups_ = other.chargeGroups_;
		defaultReloadTime_ = other.defaultReloadTime_;
		preferredState_ = other.preferredState_;
		state_ = State::unknown;
		socketValue_ = other.socketValue_;
		if (auto charge = other.charge()) {
			charge_ = Charge::Create(*charge);
		}
	}
	
	Module::~Module() {
		if (target_)
			target_->removeProjected_(this);
	}
	
	void Module::setEnabled_ (bool enabled) {
		if (isEnabled_() == enabled)
			return Type::setEnabled_(enabled);
		else
			Type::setEnabled_(enabled);
		if (charge_ != nullptr)
			charge_->setEnabled_(enabled);
		adjustState_();
	}
	
	void Module::state (dgmpp::Module::State state) {
		preferredState_ = state;
		adjustState_();
	}
	
	bool Module::canHaveState (State state) {
		auto states = availableStates();
		return std::find(states.begin(), states.end(), state) != states.end();
	}
	
	std::vector<Module::State> Module::availableStates() {
		if (isEnabled_()) {
			std::vector<Module::State> states;
			states.reserve(4);
			states.push_back(Module::State::offline);
			
			if (canBeOnline()) {
				states.push_back(Module::State::online);
				
				bool canBeActive = this->canBeActive();
				
				if (canBeActive) {
					if (attribute_(AttributeID::activationBlocked)->value_() > 0)
						canBeActive = false;
					else if (auto ship = dynamic_cast<Ship*>(parent_())) {
						if (auto attribute = attribute_(AttributeID::maxGroupActive)) {
							auto maxGroupActive = static_cast<std::size_t>(attribute->value_());
							auto groupID = metaInfo().groupID;
							
							for (const auto& i: ship->modules_) {
								auto module = std::get<std::unique_ptr<Module>>(i).get();
								if (module == this)
									continue;
								
								if (module->state() >= Module::State::active && module->metaInfo().groupID == groupID)
									maxGroupActive--;
								if (maxGroupActive <= 0) {
									canBeActive = false;
									break;
								}
							}
						}
					}
					
					if (canBeActive) {
						states.push_back(Module::State::active);
						if (canBeOverloaded())
							states.push_back(Module::State::overloaded);
					}
				}
			}
			
			
			return states;
		}
		else
			return {};
	}
	
	void Module::target(Ship* target) {
		batchUpdates_([&]() {
			if (target_) {
				if (state() >= State::active)
					deactivateEffects_(MetaInfo::Effect::Category::target);
				target_->removeProjected_(this);
			}
			target_ = target;
			if (target) {
				assert(!isDescendant_(*target));
				
				target_->project_(this);
				if (state() >= State::active)
					activateEffects_(MetaInfo::Effect::Category::target);
			}
		});
	}
	
	Type* Module::domain_ (MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::target :
				return target_;
			default:
				return Type::domain_(domain);
		}
	}
	
	Charge* Module::charge (std::unique_ptr<Charge>&& charge) {
		batchUpdates_([&]() {
			auto enabled = isEnabled_();
			
			setEnabled_(false);
			if (auto currentCharge = this->charge()) {
				currentCharge->parent_(nullptr);
				charge_ = nullptr;
			}
			if (charge != nullptr) {
				if (canFit(charge.get())) {
					charge_ = std::move(charge);
					charge_->parent_(this);
				}
				else
					throw CannotFit<Charge>(std::move(charge));
			}
			if (enabled)
				setEnabled_(true);
		});
		return charge_.get();
	}
	
	bool Module::canFit(Charge* charge) {
		auto capacity = attribute_(AttributeID::capacity)->value_();
		if (capacity > 0 && charge->attribute_(AttributeID::volume)->value_() > capacity)
			return false;
		
		auto chargeSize = this->chargeSize();
		if (chargeSize != Charge::Size::none && chargeSize != charge->size())
			return false;
		
		auto chargeGroup = charge->metaInfo().groupID;
		for (auto i: chargeGroups_) {
			if (i == chargeGroup)
				return true;
		}
		return false;
	}
	
	Charge::Size Module::chargeSize() {
		if (auto attribute = attribute_(AttributeID::chargeSize))
			return static_cast<Charge::Size>(static_cast<int>(attribute->value_()));
		else
			return Charge::Size::none;
	}

	bool Module::canBeActive() const noexcept {
		if (flags_.canBeActive)
			return true;
		else if (auto charge = this->charge())
			return charge->flags_.canBeActive;
		else
			return false;
	}
	
	bool Module::requireTarget() const noexcept {
		if (flags_.requireTarget)
			return true;
		else if (auto charge = this->charge())
			return charge->flags_.requireTarget;
		else
			return false;
	}
	
	bool Module::factorReload_() const noexcept {
		if (auto ship = dynamic_cast<Ship*>(parent_()))
			return ship->factorReload_();
			else
				return false;
	}

	
	void Module::adjustState_() {
		batchUpdates_([&] {
			if (isEnabled_() && !flags_.fail) {
				auto availableStates = this->availableStates();
				auto i = std::lower_bound(availableStates.begin(), availableStates.end(), preferredState_);
				auto state = i != availableStates.end() ? *i : availableStates.back();
				
				if (state != state_) {
					if (state < state_) {
						if (state_ >= State::overloaded	&& state < State::overloaded)
							deactivateEffects_(MetaInfo::Effect::Category::overloaded);
						
						if (state_ >= State::active		&& state < State::active) {
							deactivateEffects_(MetaInfo::Effect::Category::active);
							if (target())
								deactivateEffects_(MetaInfo::Effect::Category::target);
						}
						
						if (state_ >= State::online		&& state < State::online)
							deactivateEffects_(MetaInfo::Effect::Category::passive);
					}
					else if (state > state_) {
						if (state_ < State::online		&& state >= State::online)
							activateEffects_(MetaInfo::Effect::Category::passive);
						
						if (state_ < State::active		&& state >= State::active) {
							activateEffects_(MetaInfo::Effect::Category::active);
							if (target())
								activateEffects_(MetaInfo::Effect::Category::target);
						}
						
						if (state_ < State::overloaded	&& state >= State::overloaded)
							activateEffects_(MetaInfo::Effect::Category::overloaded);
					}
					state_ = state;
				}
			}
			else {
				if (state_ >= State::overloaded)
					deactivateEffects_(MetaInfo::Effect::Category::overloaded);
				if (state_ >= State::active) {
					deactivateEffects_(MetaInfo::Effect::Category::active);
					if (target())
						deactivateEffects_(MetaInfo::Effect::Category::target);
				}
				if (state_ >= State::online)
					deactivateEffects_(MetaInfo::Effect::Category::passive);
                state_ = Module::State::offline;
			}
		});
	}
	
	//Calculations
	
	std::chrono::milliseconds Module::reloadTime() {
		if (auto attribute = attribute_(AttributeID::reloadTime))
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		else
			return defaultReloadTime_;
	}

	
	std::chrono::milliseconds Module::cycleTime() {
		auto reactivation = 0ms;
		
		if (auto attribute = attribute_(AttributeID::moduleReactivationDelay))
			reactivation = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		
		auto speed = rawCycleTime();
		auto factorReload = this->factorReload_() || flags_.forceReload;
		
		if (factorReload && charge() != nullptr) {
			auto reload = reloadTime();
			if (reload > 0ms) {
				auto shots = this->shots();
				if (shots > 0)
					speed = (speed * shots + std::max(reload, reactivation)) / shots;
			}
		}
		
		
		return speed;
	}
	
	std::chrono::milliseconds Module::rawCycleTime() {
		for (auto attributeID: SDE::moduleCycleTimeAttributes) {
			if (auto attribute = attribute_(attributeID); attribute && attribute->value_() > 0)
				return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value_()));
		}
		return 0ms;
	}
	
	std::size_t Module::charges() {
		if (auto charge = this->charge()) {
			auto volume = charge->attribute_(AttributeID::volume)->value_();
			if (volume > 0) {
				auto capacity = attribute_(AttributeID::capacity)->value_();
				return static_cast<std::size_t>(capacity / volume);
			}
			else {
				return 0;
			}
		}
		else
			return 0;
	}
	
	std::size_t Module::shots() {
		if (auto charge = this->charge()) {
			auto charges = this->charges();
			if (charges > 0) {
				if (auto attribute = attribute_(AttributeID::chargeRate)) {
					auto rate = attribute->value_();
					if (rate > 0)
						return static_cast<std::size_t>(charges / rate);
				}
				else if (auto attribute = attribute_(AttributeID::crystalsGetDamaged)) {
					auto hp = charge->attribute_(AttributeID::hp)->value_();
					auto chance = charge->attribute_(AttributeID::crystalVolatilityChance)->value_();
					auto damage = charge->attribute_(AttributeID::crystalVolatilityDamage)->value_();
					return static_cast<std::size_t>(charges * hp / (damage * chance));
				}
			}
		}
		return 0;
	}
	
	GigaJoulePerSecond Module::capUse() {
		if (state() >= State::active) {
			GigaJoule capNeed = 0.0;
			if (auto attribute = attribute_(AttributeID::capacitorNeed))
				capNeed = static_cast<GigaJoule>(attribute->value_());
			if (capNeed == 0.0 && effect_(EffectID::energyNosferatuFalloff) != nullptr)
				capNeed -= static_cast<GigaJoule>(attribute_(AttributeID::powerTransferAmount)->value_());
			if (capNeed == 0.0 && effect_(EffectID::powerBooster) != nullptr)
				capNeed -= static_cast<GigaJoule>(attribute_(AttributeID::capacitorBonus)->value_());
			return make_rate(capNeed, cycleTime());
		}
		return GigaJoulePerSecond(0);
	}

	Teraflops Module::cpuUse() {
		return attribute_(AttributeID::cpu)->value_();
	}
	
	MegaWatts Module::powerGridUse() {
		return attribute_(AttributeID::power)->value_();
	}
	
	CalibrationPoints Module::calibrationUse() {
		return attribute_(AttributeID::upgradeCost)->value_();
	}

	Points Module::accuracyScore() {
		if (auto attribute = attribute_(AttributeID::trackingSpeed))
			return attribute->value_();
		else
			return 0;
	}
	
	Meter Module::signatureResolution() {
		if (auto attribute = attribute_(AttributeID::optimalSigRadius))
			return attribute->value_();
		else
			return 0;
	}
	
	CubicMeterPerSecond Module::miningYield() {
		if (state() >= State::active) {
			CubicMeter volley = 0;
			if (auto attribute = attribute_(AttributeID::specialtyMiningAmount))
				volley += attribute->value_();
			if (auto attribute = attribute_(AttributeID::miningAmount))
				volley += attribute->value_();
			return make_rate(volley, cycleTime());
		}
		else
			return CubicMeterPerSecond(0.0);
	}

	DamageVector Module::volley() {
		if (state() >= State::active) {
			auto volley = DamageVector(0);
			auto& item = charge_ ? *static_cast<Type*> (charge_.get()) : *static_cast<Type*>(this);
			
			if (auto attribute = item.attribute_(AttributeID::emDamage))
				volley.em += attribute->value_();
			if (auto attribute = item.attribute_(AttributeID::kineticDamage))
				volley.kinetic += attribute->value_();
			if (auto attribute = item.attribute_(AttributeID::thermalDamage))
				volley.thermal += attribute->value_();
			if (auto attribute = item.attribute_(AttributeID::explosiveDamage))
				volley.explosive += attribute->value_();
			
			if (auto attribute = attribute_(AttributeID::damageMultiplier))
				volley *= attribute->value_();
			else if (auto attribute = attribute_(AttributeID::missileDamageMultiplier))
				volley *= attribute->value_();
			
			return volley;
		}
		else
			return {0};
	}
	
	DamagePerSecond Module::dps(const HostileTarget& target) {
		auto dps = make_rate(volley(), cycleTime());
		
		switch (hardpoint()) {
			case Module::Hardpoint::turret: {
				if (target.range > 0 || target.angularVelocity.count() > 0 || target.signature > 0) {
					
					Float a = 0;
					if (target.angularVelocity.count() > 0) {
						if (auto accuracyScore = this->accuracyScore(); accuracyScore > 0)
							a = target.angularVelocity * 1s / accuracyScore;
					}

					if (target.signature > 0) {
						auto signatureResolution = this->signatureResolution();
						if (signatureResolution > 0)
							a *= signatureResolution / target.signature;
					}
					
					Float b = 0;
					if (target.range > 0) {
						auto optimal = this->optimal();
						auto falloff = this->falloff();
						b = falloff > 0 ? std::max(0.0, (target.range - optimal) / falloff) : 0;
					}
					
					auto blob = std::pow(a, 2) + std::pow(b, 2);
					auto hitChance = std::pow(0.5, blob);
					auto relativeDPS = hitChance > 0.01
						? (hitChance - 0.01) * (0.5 + (hitChance + 0.49)) / 2 + 0.01 * 3
						: hitChance * 3;
					return dps * relativeDPS;

				}
				else
					return dps;
			}
			case Module::Hardpoint::launcher: {
				if (auto charge = this->charge(); optimal() >= target.range) {
					if (target.velocity.count() > 0) {
						Float missileEntityVelocityMultiplier = 1;
						
						if (auto attribute = attribute_(AttributeID::missileEntityVelocityMultiplier))
							missileEntityVelocityMultiplier = attribute->value_();
						auto maxVelocity = MetersPerSecond(charge->attribute_(AttributeID::maxVelocity)->value_() * missileEntityVelocityMultiplier);

						if (maxVelocity < target.velocity)
							return DamagePerSecond(0);
					}
					
					Float a = 1;
					if (target.signature > 0) {
						auto e = charge->attribute_(AttributeID::aoeCloudSize)->value_();
						a = e != 0.0 ? target.signature / e : 1;
					}
					Float b = 1;
					if (target.velocity.count() > 0) {
						auto v = charge->attribute_(AttributeID::aoeCloudSize)->value_();
						auto drf = charge->attribute_(AttributeID::aoeDamageReductionFactor)->value_();
						auto drs = charge->attribute_(AttributeID::aoeDamageReductionSensitivity)->value_();
						if (drf > 0 && drs > 0 && v > 0)
							b = std::pow(a * v / (target.velocity * 1s), std::log(drf)/std::log(drs));
					}
					auto relativeDPS = std::min(1.0, std::min(a, b));
					return dps * relativeDPS;
				}
				else
					return DamagePerSecond(0);
			}
			default:
				return optimal() >= target.range ? static_cast<DamagePerSecond>(dps) : DamagePerSecond(0);
		}
		
	}
	
	Meter Module::optimal() {
		
		for (auto attributeID: SDE::moduleOptimalAttributes) {
			if (auto attribute = attribute_(attributeID))
				return attribute->value_();
		}
		
		if (auto charge = this->charge()) {
			auto maxVelocity = charge->attribute_(AttributeID::maxVelocity);
			auto explosionDelay = charge->attribute_(AttributeID::explosionDelay);
			auto mass = charge->attribute_(AttributeID::mass);
			auto agility = charge->attribute_(AttributeID::agility);
			if (maxVelocity && explosionDelay && mass && agility) {
				Float missileEntityVelocityMultiplier = 1;
				Float missileEntityFlightTimeMultiplier = 1;
				
				if (auto attribute = attribute_(AttributeID::missileEntityVelocityMultiplier))
					missileEntityVelocityMultiplier = attribute->value_();
				if (auto attribute = attribute_(AttributeID::missileEntityFlightTimeMultiplier))
					missileEntityFlightTimeMultiplier = attribute->value_();

				if (missileEntityVelocityMultiplier == 0)
					missileEntityVelocityMultiplier = 1.0;
				if (missileEntityFlightTimeMultiplier == 0)
					missileEntityFlightTimeMultiplier = 1.0;
				
				rate<Meter, std::chrono::milliseconds> mv = MetersPerSecond(maxVelocity->value_() * missileEntityVelocityMultiplier);
				auto flightTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep> (explosionDelay->value_() * missileEntityFlightTimeMultiplier));
				Kilogram m = mass->value_();
				auto a = agility->value_();
				
				auto accelerationTime = min(flightTime, std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(m * a / 1'000'000.0 * 1000.0)));
				auto acceleration = mv / 2.0 * accelerationTime;
				auto fullSpeed = mv * (flightTime - accelerationTime);
				return acceleration + fullSpeed;
			}
		}
		
		return 0;
	}
	
	Meter Module::falloff() {
		for (auto attributeID: SDE::moduleFalloffAttributes) {
			if (auto attribute = attribute_(attributeID); attribute && attribute->value_() > 0)
				return attribute->value_();
		}
		return 0;
	}

	std::optional<std::chrono::milliseconds> Module::lifeTime_() {
		if (!lifeTimeValue_) {
			if (auto ship = dynamic_cast<Ship*>(parent_())) {
				ship->heatSimulator_.simulate();
			}
		}
		return lifeTimeValue_;
	}

	RadiansPerSecond Module::angularVelocity(Meter targetSignature, Percent hitChance) {
		auto signatureResolution = this->signatureResolution();
		auto accuracyScore = this->accuracyScore();
		if (signatureResolution > 0 && accuracyScore > 0)
			return make_rate(std::sqrt(std::log(hitChance) / std::log(0.5)) * accuracyScore * targetSignature / signatureResolution, 1s);
		else
			return RadiansPerSecond(0);
	}
}
