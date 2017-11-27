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

namespace dgmpp2 {
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
		bool active() const			{ return flags_.active; }
		bool isAssistance() const	{ return flags_.isAssistance; }
		bool isOffensive() const	{ return flags_.isOffensive; }
		bool dealsDamage() const	{ return flags_.dealsDamage; }

		Charge* charge() const { return charge_.get(); }

		Squadron squadron() const { return squadron_; }
		size_t squadronSize();

		SquadronTag squadronTag() const { return squadronTag_; };

		Ship* target() const { return target_; }
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
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		
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
		Ship* target_;
		
		Drone (TypeID typeID);
		void squadronTag (SquadronTag squadronTag) { squadronTag_ = squadronTag; }
		
		DamageVector droneVolley();
		DamageVector fighterAttackMissileVolley();
		DamageVector fighterAttackTurretVolley();
		DamageVector fighterMissileVolley();
		DamagePerSecond rawDPS();

	};
}

