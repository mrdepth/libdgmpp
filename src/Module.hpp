//
//  Module.hpp
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
	class Module: public Type {
	public:
		typedef int Socket;
		static const Socket anySocket;
		
		
		static std::unique_ptr<Module> Create (TypeID typeID) { return std::unique_ptr<Module>(new Module(typeID)); }
		static std::unique_ptr<Module> Create (const Module& other) { return std::unique_ptr<Module>(new Module(other)); }
		
		enum class State {
			unknown = -1,
			offline,
			online,
			active,
			overloaded
		};
		
		enum class Slot {
			none,
			hi,
			med,
			low,
			rig,
			subsystem,
			mode,
			service,
			starbaseStructure
		};
		
		enum class Hardpoint {
			none,
			launcher,
			turret
		};
		
		virtual ~Module();
		
		bool canHaveState (State state);
		std::vector<State> availableStates();
		
		State state() const noexcept {return state_;}
		State preferredState() const noexcept {return preferredState_;}
		void state (State state);
		
		Ship* target() const noexcept { return target_; }
		void target(Ship* target);
		
		Slot slot() const noexcept				{return slot_;}
		Hardpoint hardpoint() const noexcept	{return hardpoint_;}
		Socket socket() const noexcept			{return socket_;}
		
		Charge* charge() const noexcept { return charge_.get(); }
		Charge* charge (std::unique_ptr<Charge>&& charge);
		Charge* charge (TypeID typeID) { return charge(Charge::Create(typeID)); }
		bool canFit (Charge* charge);
		const std::vector<GroupID>& chargeGroups() const noexcept { return chargeGroups_; };
		
		Charge::Size chargeSize();
		
		bool canBeOnline()		const noexcept	{ return flags_.canBeOnline; }
		bool canBeActive()		const noexcept;
		bool canBeOverloaded()	const noexcept	{ return flags_.canBeOverloaded; }
		bool requireTarget()	const noexcept;
		bool fail()				const noexcept	{ return flags_.fail; }

		//Calculations
		
		std::chrono::milliseconds reloadTime();
		std::chrono::milliseconds cycleTime();
		std::chrono::milliseconds rawCycleTime();

		std::size_t charges();
		std::size_t shots();
		
		GigaJoulePerSecond capUse();
		Teraflops cpuUse();
		MegaWatts powerGridUse();
		CalibrationPoints calibrationUse();
		
		Points accuracyScore();
		Meter signatureResolution();
		CubicMeterPerSecond miningYield();

		DamageVector volley();
		DamagePerSecond dps(const HostileTarget& target = HostileTarget::Default());
		Meter optimal();
		Meter falloff();

		std::optional<std::chrono::milliseconds> lifeTime();
		
		RadiansPerSecond angularVelocity(Meter targetSignature, Percent hitChance = 0.75);

	protected:
		virtual void setEnabled (bool enabled) override;
		virtual Type* domain (MetaInfo::Modifier::Domain domain) noexcept override;
		
	private:
		friend class Ship;
		friend class HeatSimulator;
		State state_ = State::unknown;
		State preferredState_ = State::unknown;
		Slot slot_;
		Hardpoint hardpoint_;
		Socket socket_ = anySocket;
		std::chrono::milliseconds defaultReloadTime_;
		std::optional<std::chrono::milliseconds> lifeTime_;
		
		struct {
			bool canBeOnline : 1;
			bool canBeActive : 1;
			bool canBeOverloaded : 1;
			bool forceReload : 1;
//			bool factorReload : 1;
			bool requireTarget : 1;
			bool fail : 1;
		} flags_;
		std::vector<GroupID> chargeGroups_;
		std::unique_ptr<Charge> charge_;
		Ship* target_ = nullptr;
		bool factorReload_() const noexcept;

		Module (TypeID typeID);
		Module (const Module& other);
		
		void socket (Socket socket) noexcept { socket_ = socket; }
		void adjustState();
		void fail(bool fail) noexcept { flags_.fail = fail; }
		void lifeTime (std::chrono::milliseconds lifeTime) noexcept { lifeTime_ = lifeTime; };
	};
}
