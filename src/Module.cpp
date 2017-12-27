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
		const auto& effects = this->effects();
		
		
		flags_.canBeOnline = (*this)[EffectID::online] != nullptr || (*this)[EffectID::onlineForStructures];
		
		flags_.canBeOverloaded = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::overloaded;
		});
		
		flags_.requireTarget = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target;
		});
		
		flags_.canBeActive = flags_.canBeOverloaded || flags_.requireTarget || std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::active;
		});
		
		flags_.fail = false;
		
		flags_.forceReload = metaInfo().groupID == GroupID::capacitorBooster;
		flags_.factorReload = false;
		
		if ((*this)[EffectID::loPower])
			slot_ = Module::Slot::low;
		else if ((*this)[EffectID::medPower])
			slot_ = Module::Slot::med;
		else if ((*this)[EffectID::hiPower])
			slot_ = Module::Slot::hi;
		else if ((*this)[EffectID::rigSlot])
			slot_ = Module::Slot::rig;
		else if ((*this)[EffectID::subSystem])
			slot_ = Module::Slot::subsystem;
		else if ((*this)[EffectID::tacticalMode])
			slot_ = Module::Slot::mode;
		else if (metaInfo().categoryID == CategoryID::starbase)
			slot_ = Module::Slot::starbaseStructure;
		else if ((*this)[EffectID::serviceSlot])
			slot_ = Module::Slot::service;
		else
			slot_ = Module::Slot::none;
		
		if ((*this)[EffectID::turretFitted])
			hardpoint_ = Module::Hardpoint::turret;
		else if ((*this)[EffectID::launcherFitted])
			hardpoint_ = Module::Hardpoint::launcher;
		else
			hardpoint_ = Module::Hardpoint::none;
		
		for (auto attributeID : SDE::chargeGroupAttributeIDs) {
			if (auto groupIDAttribute = (*this)[attributeID]) {
				GroupID groupID = static_cast<GroupID>(static_cast<int>(groupIDAttribute->value()));
				if (groupID != GroupID::none) {
					chargeGroups_.push_back(groupID);
					if (groupID == GroupID::capacitorBoosterCharge || groupID == GroupID::naniteRepairPaste)
						flags_.forceReload = true;
				}
			}
		}
		chargeGroups_.shrink_to_fit();
		std::sort(chargeGroups_.begin(), chargeGroups_.end());
		
		if (std::any_of(effects.begin(), effects.end(), [](const auto& i) {
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
		else if (std::any_of(effects.begin(), effects.end(), [](const auto& i) {
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
	
	Module::~Module() {
		if (target_)
			target_->removeProjected(this);
	}
	
	void Module::setEnabled (bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
		if (charge_ != nullptr)
			charge_->setEnabled(enabled);
		adjustState();
	}
	
	void Module::state (dgmpp::Module::State state) {
		preferredState_ = state;
		adjustState();
	}
	
	bool Module::canHaveState (State state) {
		auto states = availableStates();
		return std::find(states.begin(), states.end(), state) != states.end();
	}
	
	std::vector<Module::State> Module::availableStates() {
		if (isEnabled()) {
			std::vector<Module::State> states;
			states.reserve(4);
			states.push_back(Module::State::offline);
			
			if (canBeOnline()) {
				states.push_back(Module::State::online);
				
				bool canBeActive = this->canBeActive();
				
				if (canBeActive) {
					if ((*this)[AttributeID::activationBlocked]->value() > 0)
						canBeActive = false;
					else if (auto ship = dynamic_cast<Ship*>(parent())) {
						if (auto attribute = (*this)[AttributeID::maxGroupActive]) {
							auto maxGroupActive = static_cast<std::size_t>(attribute->value());
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
		batchUpdates([&]() {
			if (target_) {
				if (state() >= State::active)
					deactivateEffects(MetaInfo::Effect::Category::target);
				target_->removeProjected(this);
			}
			target_ = target;
			if (target) {
				assert(!isDescendant(*target));
				
				target_->project(this);
				if (state() >= State::active)
					activateEffects(MetaInfo::Effect::Category::target);
			}
		});
	}
	
	Type* Module::domain (MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::target :
				return target_;
			default:
				return Type::domain(domain);
		}
	}
	
	Charge* Module::charge (std::unique_ptr<Charge>&& charge) {
		batchUpdates([&]() {
			auto enabled = isEnabled();
			
			setEnabled(false);
			if (auto currentCharge = this->charge()) {
				currentCharge->parent(nullptr);
				charge_ = nullptr;
			}
			if (charge != nullptr) {
				if (canFit(charge.get())) {
					charge_ = std::move(charge);
					charge_->parent(this);
				}
				else
					throw CannotFit<Charge>(std::move(charge));
			}
			if (enabled)
				setEnabled(true);
		});
		return charge_.get();
	}
	
	bool Module::canFit(Charge* charge) {
		auto capacity = (*this)[AttributeID::capacity]->value();
		if (capacity > 0 && (*charge)[AttributeID::volume]->value() > capacity)
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
		if (auto attribute = (*this)[AttributeID::chargeSize])
			return static_cast<Charge::Size>(static_cast<int>(attribute->value()));
		else
			return Charge::Size::none;
	}

	bool Module::canBeActive() const noexcept {
		if (flags_.canBeActive)
			return true;
		else if (auto charge = this->charge())
			return charge->canBeActive();
		else
			return false;
	}
	
	bool Module::requireTarget() const noexcept {
		if (flags_.requireTarget)
			return true;
		else if (auto charge = this->charge())
			return charge->requireTarget();
		else
			return false;
	}
	
	void Module::adjustState() {
		batchUpdates([&] {
			if (isEnabled() && !flags_.fail) {
				auto availableStates = this->availableStates();
				auto i = std::lower_bound(availableStates.begin(), availableStates.end(), preferredState_);
				auto state = i != availableStates.end() ? *i : availableStates.back();
				
				if (state != state_) {
					if (state < state_) {
						if (state_ >= State::overloaded	&& state < State::overloaded)
							deactivateEffects(MetaInfo::Effect::Category::overloaded);
						
						if (state_ >= State::active		&& state < State::active) {
							deactivateEffects(MetaInfo::Effect::Category::active);
							if (target())
								deactivateEffects(MetaInfo::Effect::Category::target);
						}
						
						if (state_ >= State::online		&& state < State::online)
							deactivateEffects(MetaInfo::Effect::Category::passive);
					}
					else if (state > state_) {
						if (state_ < State::online		&& state >= State::online)
							activateEffects(MetaInfo::Effect::Category::passive);
						
						if (state_ < State::active		&& state >= State::active) {
							activateEffects(MetaInfo::Effect::Category::active);
							if (target())
								activateEffects(MetaInfo::Effect::Category::target);
						}
						
						if (state_ < State::overloaded	&& state >= State::overloaded)
							activateEffects(MetaInfo::Effect::Category::overloaded);
					}
					state_ = state;
				}
			}
			else {
				if (state_ >= State::overloaded)
					deactivateEffects(MetaInfo::Effect::Category::overloaded);
				if (state_ >= State::active) {
					deactivateEffects(MetaInfo::Effect::Category::active);
					if (target())
						deactivateEffects(MetaInfo::Effect::Category::target);
				}
				if (state_ >= State::online)
					deactivateEffects(MetaInfo::Effect::Category::passive);
                state_ = Module::State::offline;
			}
		});
	}
	
	//Calculations
	
	std::chrono::milliseconds Module::reloadTime() {
		if (auto attribute = (*this)[AttributeID::reloadTime])
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value()));
		else
			return defaultReloadTime_;
	}

	
	std::chrono::milliseconds Module::cycleTime() {
		auto reactivation = 0ms;
		
		if (auto attribute = (*this)[AttributeID::moduleReactivationDelay])
			reactivation = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value()));
		
		auto speed = rawCycleTime();
		auto factorReload = flags_.factorReload || flags_.forceReload;
		
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
			if (auto attribute = (*this)[attributeID]; attribute && attribute->value() > 0)
				return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value()));
		}
		return 0ms;
	}
	
	std::size_t Module::charges() {
		if (auto charge = this->charge()) {
			auto volume = (*charge)[AttributeID::volume]->value();
			if (volume > 0)
				return 0;
			else {
				auto capacity = (*this)[AttributeID::capacity]->value();
				return static_cast<std::size_t>(capacity / volume);
			}
		}
		else
			return 0;
	}
	
	std::size_t Module::shots() {
		if (auto charge = this->charge()) {
			auto charges = this->charges();
			if (charges > 0) {
				if (auto attribute = (*this)[AttributeID::chargeRate]) {
					auto rate = attribute->value();
					if (rate > 0)
						return static_cast<std::size_t>(charges / rate);
				}
				else if (auto attribute = (*this)[AttributeID::crystalsGetDamaged]) {
					auto hp = (*charge)[AttributeID::hp]->value();
					auto chance = (*charge)[AttributeID::crystalVolatilityChance]->value();
					auto damage = (*charge)[AttributeID::crystalVolatilityDamage]->value();
					return static_cast<std::size_t>(charges * hp / (damage * chance));
				}
			}
		}
		return 0;
	}
	
	GigaJoulePerSecond Module::capUse() {
		if (state() >= State::active) {
			GigaJoule capNeed = 0.0;
			if (auto attribute = (*this)[AttributeID::capacitorNeed])
				capNeed = static_cast<GigaJoule>(attribute->value());
			if (capNeed == 0.0 && (*this)[EffectID::energyNosferatuFalloff] != nullptr)
				capNeed -= static_cast<GigaJoule>((*this)[AttributeID::powerTransferAmount]->value());
			if (capNeed == 0.0 && (*this)[EffectID::powerBooster] != nullptr)
				capNeed -= static_cast<GigaJoule>((*this)[AttributeID::capacitorBonus]->value());
			return make_rate(capNeed, cycleTime());
		}
		return GigaJoulePerSecond(0);
	}

	Teraflops Module::cpuUse() {
		return (*this)[AttributeID::cpu]->value();
	}
	
	MegaWatts Module::powerGridUse() {
		return (*this)[AttributeID::power]->value();
	}
	
	CalibrationPoints Module::calibrationUse() {
		return (*this)[AttributeID::upgradeCost]->value();
	}

	Points Module::accuracyScore() {
		if (auto attribute = (*this)[AttributeID::trackingSpeed])
			return attribute->value();
		else
			return 0;
	}
	
	Meter Module::signatureResolution() {
		if (auto attribute = (*this)[AttributeID::optimalSigRadius])
			return attribute->value();
		else
			return 0;
	}
	
	CubicMeterPerSecond Module::miningYield() {
		if (state() >= State::active) {
			CubicMeter volley = 0;
			if (auto attribute = (*this)[AttributeID::specialtyMiningAmount])
				volley += attribute->value();
			if (auto attribute = (*this)[AttributeID::miningAmount])
				volley += attribute->value();
			return make_rate(volley, cycleTime());
		}
		else
			return CubicMeterPerSecond(0.0);
	}

	DamageVector Module::volley() {
		if (state() >= State::active) {
			auto volley = DamageVector(0);
			auto& item = charge_ ? *static_cast<Type*> (charge_.get()) : *static_cast<Type*>(this);
			
			if (auto attribute = item[AttributeID::emDamage])
				volley.em += attribute->value();
			if (auto attribute = item[AttributeID::kineticDamage])
				volley.kinetic += attribute->value();
			if (auto attribute = item[AttributeID::thermalDamage])
				volley.thermal += attribute->value();
			if (auto attribute = item[AttributeID::explosiveDamage])
				volley.explosive += attribute->value();
			
			if (auto attribute = (*this)[AttributeID::damageMultiplier])
				volley *= attribute->value();
			else if (auto attribute = (*this)[AttributeID::missileDamageMultiplier])
				volley *= attribute->value();
			
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
						
						if (auto attribute = (*this)[AttributeID::missileEntityVelocityMultiplier])
							missileEntityVelocityMultiplier = attribute->value();
						auto maxVelocity = MetersPerSecond((*charge)[AttributeID::maxVelocity]->value() * missileEntityVelocityMultiplier);

						if (maxVelocity < target.velocity)
							return DamagePerSecond(0);
					}
					
					Float a = 1;
					if (target.signature > 0) {
						auto e = (*charge)[AttributeID::aoeCloudSize]->value();
						a = e != 0.0 ? target.signature / e : 1;
					}
					Float b = 1;
					if (target.velocity.count() > 0) {
						auto v = (*charge)[AttributeID::aoeCloudSize]->value();
						auto drf = (*charge)[AttributeID::aoeDamageReductionFactor]->value();
						auto drs = (*charge)[AttributeID::aoeDamageReductionSensitivity]->value();
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
			if (auto attribute = (*this)[attributeID])
				return attribute->value();
		}
		
		if (auto charge = this->charge()) {
			auto maxVelocity = (*charge)[AttributeID::maxVelocity];
			auto explosionDelay = (*charge)[AttributeID::explosionDelay];
			auto mass = (*charge)[AttributeID::mass];
			auto agility = (*charge)[AttributeID::agility];
			if (maxVelocity && explosionDelay && mass && agility) {
				Float missileEntityVelocityMultiplier = 1;
				Float missileEntityFlightTimeMultiplier = 1;
				
				if (auto attribute = (*this)[AttributeID::missileEntityVelocityMultiplier])
					missileEntityVelocityMultiplier = attribute->value();
				if (auto attribute = (*this)[AttributeID::missileEntityFlightTimeMultiplier])
					missileEntityFlightTimeMultiplier = attribute->value();

				if (missileEntityVelocityMultiplier == 0)
					missileEntityVelocityMultiplier = 1.0;
				if (missileEntityFlightTimeMultiplier == 0)
					missileEntityFlightTimeMultiplier = 1.0;
				
				rate<Meter, std::chrono::milliseconds> mv = MetersPerSecond(maxVelocity->value() * missileEntityVelocityMultiplier);
				auto flightTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep> (explosionDelay->value() * missileEntityFlightTimeMultiplier));
				Kilogram m = mass->value();
				auto a = agility->value();
				
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
			if (auto attribute = (*this)[attributeID]; attribute && attribute->value() > 0)
				return attribute->value();
		}
		return 0;
	}

	std::optional<std::chrono::milliseconds> Module::lifeTime() {
		if (!lifeTime_) {
			if (auto ship = dynamic_cast<Ship*>(parent())) {
				ship->heatSimulator_.simulate();
			}
		}
		return lifeTime_;
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
