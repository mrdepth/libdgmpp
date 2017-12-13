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
		
		void active (bool active);
		bool active() const noexcept { return flags_.active; }

		Charge* charge() const noexcept { return charge_.get(); }

		Squadron squadron() const noexcept { return squadron_; }
		size_t squadronSize();

		SquadronTag squadronTag() const noexcept { return squadronTag_; };

		Ship* target() const noexcept { return target_; }
		void target(Ship* target);

		virtual void setEnabled (bool enabled) override;
		
		//Calculations
		std::chrono::milliseconds cycleTime();
		DamageVector volley();
		DamagePerSecond dps(const HostileTarget& target = HostileTarget::Default());
		Meter optimal();
		Meter falloff();
		Points accuracyScore();
		CubicMeterPerSecond miningYield();
		MetersPerSecond velocity();

	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) noexcept override;
		
		bool isAssistance() const noexcept	{ return flags_.isAssistance; }
		bool isOffensive() const noexcept	{ return flags_.isOffensive; }
		bool dealsDamage() const noexcept	{ return flags_.dealsDamage; }

	private:
		friend class Ship;
		
		struct {
			bool active : 1;
			bool isAssistance : 1;
			bool isOffensive : 1;
			bool dealsDamage : 1;
		} flags_;
		
		SquadronTag squadronTag_ = anySquadronTag;
		Squadron squadron_;
		std::unique_ptr<Charge> charge_;
		Ship* target_ = nullptr;
		
		Drone (TypeID typeID);
		void squadronTag (SquadronTag squadronTag) noexcept { squadronTag_ = squadronTag; }
		
		DamageVector droneVolley();
		DamageVector fighterAttackMissileVolley();
		DamageVector fighterAttackTurretVolley();
		DamageVector fighterMissileVolley();
		DamagePerSecond rawDPS();

	};
}

