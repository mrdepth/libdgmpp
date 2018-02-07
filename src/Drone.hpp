//
//  Drone.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Type.hpp"
#include "Charge.hpp"
#include "DamageVector.hpp"

namespace dgmpp {
	class Ship;
	class Drone: public Type {
	public:
		typedef int SquadronTag;
		static const SquadronTag anySquadronTag;

		enum class Squadron {
			none,
			heavy,
			light,
			support
		};

		virtual ~Drone();
		static std::unique_ptr<Drone> Create (TypeID typeID) { return std::unique_ptr<Drone>(new Drone(typeID)); }
		static std::unique_ptr<Drone> Create (const Drone& other) { return std::unique_ptr<Drone>(new Drone(other)); }
		
		void active (bool active) { LOCK(this); active_(active); }
		bool active() const noexcept { LOCK(this); return active_(); }
		bool hasKamikazeAbility() const noexcept { LOCK(this); return hasKamikazeAbility_(); }
		void kamikaze (bool kamikaze) { LOCK(this); kamikaze_(kamikaze); }
		bool kamikaze() const noexcept { LOCK(this); return kamikaze_(); }

		Charge* charge() const noexcept { return charge_.get(); }

		Squadron squadron() const noexcept { return squadron_; }
		std::size_t squadronSize() { return squadronSize_; }
		SquadronTag squadronTag() const noexcept { LOCK(this); return squadronTag_(); };
		Ship* target() const noexcept { LOCK(this); return target_(); }
		void target(Ship* target) { LOCK(this); target_(target); }

		
		//Calculations
		std::chrono::milliseconds cycleTime() { LOCK(this); return cycleTime_(); }
		DamageVector volley() { LOCK(this); return volley_(); }
		DamagePerSecond dps(const HostileTarget& target = HostileTarget::Default()) { LOCK(this); return dps_(target); }
		Meter optimal() { LOCK(this); return optimal_(); }
		Meter falloff() { LOCK(this); return falloff_(); }
		Points accuracyScore() { LOCK(this); return accuracyScore_(); }
		MetersPerSecond velocity() { LOCK(this); return velocity_(); }
		CubicMeterPerSecond miningYield() { LOCK(this); return miningYield_(); }

	protected:
		virtual void setEnabled_ (bool enabled) override;
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
		virtual Type* owner_() const noexcept override { return parent_() ? parent_()->parent_() : nullptr; }
		struct {
			bool active : 1;
			bool kamikaze: 1;
			bool isAssistance : 1;
			bool isOffensive : 1;
			bool dealsDamage : 1;
			bool hasKamikazeAbility : 1;
		} flags_;

	private:
		friend class Ship;
		friend class Capacitor;
		friend class Gang;
		
		
		SquadronTag squadronTagValue_ {anySquadronTag};
		const Squadron squadron_ {[this]() {
			if (attribute_(AttributeID::fighterSquadronIsHeavy))
				return Squadron::heavy;
			else if (attribute_(AttributeID::fighterSquadronIsLight))
				return Squadron::light;
			else if (attribute_(AttributeID::fighterSquadronIsSupport))
				return Squadron::support;
			else
				return Squadron::none;
		}()};
		
		const std::size_t squadronSize_ {[this]() -> std::size_t {
			if (squadron_ == Squadron::none)
				return 5;
			else {
				auto size = static_cast<std::size_t>(attribute_(AttributeID::fighterSquadronMaxSize)->value_());
				return size > 0 ? size : 5;
			}
		}()};

		const std::unique_ptr<Charge> charge_ {[this]() -> std::unique_ptr<Charge> {
			if (auto attribute = attribute_(AttributeID::entityMissileTypeID)) {
				auto typeID = static_cast<TypeID>(static_cast<int>(attribute->value_()));
				auto charge = Charge::Create(typeID);
				charge->parent_(this);
				return charge;
			}
			else if (auto attribute = attribute_(AttributeID::fighterAbilityLaunchBombType)) {
				auto typeID = static_cast<TypeID>(static_cast<int>(attribute->value_()));
				auto charge = Charge::Create(typeID);
				charge->parent_(this);
				return charge;
			}
			else
				return nullptr;
		}()};
		
		Ship* targetValue_ {nullptr};
		
		Drone (TypeID typeID);
		Drone (const Drone& other);

		void active_ (bool active);
		bool active_() const noexcept { return flags_.active; }
		void kamikaze_ (bool kamikaze);
		bool kamikaze_() const noexcept { return flags_.kamikaze; }

		
		bool hasKamikazeAbility_() const noexcept { return flags_.hasKamikazeAbility; }
		
		void squadronTag_ (SquadronTag squadronTag) noexcept { squadronTagValue_ = squadronTag; }
		SquadronTag squadronTag_() const noexcept { return squadronTagValue_; };
		
		Ship* target_() const noexcept { return targetValue_; }
		void target_ (Ship* target);

		std::chrono::milliseconds cycleTime_();
		DamageVector volley_();
		DamagePerSecond dps_(const HostileTarget& target = HostileTarget::Default());
		Meter optimal_();
		Meter falloff_();
		Points accuracyScore_();
		MetersPerSecond velocity_();
		CubicMeterPerSecond miningYield_();
		
		DamageVector droneVolley_();
		DamageVector fighterAttackMissileVolley_();
		DamageVector fighterAttackTurretVolley_();
		DamageVector fighterMissileVolley_();
		DamageVector fighterKamikazeVolley_();
		DamagePerSecond rawDPS_();

	};
}

