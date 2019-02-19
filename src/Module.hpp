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

		static std::unique_ptr<Module> Create (TypeID typeID) { return std::unique_ptr<Module>(new Module(typeID)); }
		static std::unique_ptr<Module> Create (const Module& other) { return std::unique_ptr<Module>(new Module(other)); }
		
		virtual ~Module();
		
		Slot slot() const noexcept				{return slot_;}
		Hardpoint hardpoint() const noexcept	{return hardpoint_;}

		const std::vector<GroupID>& chargeGroups() const noexcept { return chargeGroups_; };
		Charge::Size chargeSize() const noexcept { return chargeSize_; }

		bool canHaveState (State state) { LOCK(this); return canHaveState_(state); }
		std::vector<State> availableStates() { LOCK(this); return availableStates_(); }

		State state() const noexcept { LOCK(this); return state_(); }
		State preferredState() const noexcept { LOCK(this); return preferredState_(); }
		void state (State state) { LOCK(this); state_(state); }

		Ship* target() const noexcept { LOCK(this); return target_(); }
		void target(Ship* target) { LOCK(this); target_(target); }
		
		Socket socket() const noexcept { LOCK(this); return socket_(); }
		
		Charge* charge() const noexcept { LOCK(this); return charge_(); }
		Charge* charge (std::unique_ptr<Charge>&& charge) { LOCK(this); return charge_(std::move(charge)); }
		Charge* charge (TypeID typeID) { LOCK(this); return charge(Charge::Create(typeID)); }
		void  clearCharge();

		bool canFit (Charge* charge) { LOCK(this); return canFit_(charge); }
		bool canFit (TypeID typeID) { return canFit(Charge::Create(typeID).get()); }
		
		bool requireTarget()	const noexcept { LOCK(this); return requireTarget_(); }
		bool fail()				const noexcept { LOCK(this); return fail_(); }

		//Calculations
		
		std::chrono::milliseconds reloadTime() { LOCK(this); return reloadTime_(); }
		std::chrono::milliseconds cycleTime() { LOCK(this); return cycleTime_(); }
		std::chrono::milliseconds rawCycleTime() { LOCK(this); return rawCycleTime_(); }

		std::size_t charges() { LOCK(this); return charges_(); }
		std::size_t shots() { LOCK(this); return shots_(); }

		GigaJoulePerSecond capUse() { LOCK(this); return capUse_(); }
		Teraflops cpuUse() { LOCK(this); return cpuUse_(); }
		MegaWatts powerGridUse() { LOCK(this); return powerGridUse_(); }
		CalibrationPoints calibrationUse() { LOCK(this); return calibrationUse_(); }

		Points accuracyScore() { LOCK(this); return accuracyScore_(); }
		Meter signatureResolution() { LOCK(this); return signatureResolution_(); }
		CubicMeterPerSecond miningYield() { LOCK(this); return miningYield_(); }

		DamageVector volley() { LOCK(this); return volley_(); }
		DamagePerSecond dps(const HostileTarget& target = HostileTarget::Default()) { LOCK(this); return dps_(target); }
		Meter optimal() { LOCK(this); return optimal_(); }
		Meter falloff() { LOCK(this); return falloff_(); }

		std::optional<std::chrono::milliseconds> lifeTime() { LOCK(this); return lifeTime_(); }

		RadiansPerSecond angularVelocity(Meter targetSignature, Percent hitChance = 0.75) { LOCK(this); return angularVelocity_(targetSignature, hitChance); }

	protected:
		virtual void setEnabled_ (bool enabled) override;
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
		
	private:
		friend class Ship;
		friend class Capacitor;
		friend class HeatSimulator;
		friend class Gang;
		State stateValue_ = State::unknown;
		State preferredStateValue_ = State::unknown;
		
		const Slot slot_ {[this]() {
			if (effect_(EffectID::loPower))
				return Module::Slot::low;
			else if (effect_(EffectID::medPower))
				return Module::Slot::med;
			else if (effect_(EffectID::hiPower))
				return Module::Slot::hi;
			else if (effect_(EffectID::rigSlot))
				return Module::Slot::rig;
			else if (effect_(EffectID::subSystem))
				return Module::Slot::subsystem;
			else if (effect_(EffectID::tacticalMode))
				return Module::Slot::mode;
			else if (metaInfo().categoryID == CategoryID::starbase)
				return Module::Slot::starbaseStructure;
			else if (effect_(EffectID::serviceSlot))
				return Module::Slot::service;
			else
				return Module::Slot::none;
		}()};
		
		
		const Hardpoint hardpoint_ {[this]() {
			if (effect_(EffectID::turretFitted))
				return Module::Hardpoint::turret;
			else if (effect_(EffectID::launcherFitted))
				return Module::Hardpoint::launcher;
			else
				return Module::Hardpoint::none;
		}()};
		
		const Charge::Size chargeSize_ { [this]{
			if (auto attribute = attribute_(AttributeID::chargeSize))
				return static_cast<Charge::Size>(static_cast<int>(attribute->value_()));
			else
				return Charge::Size::none;
		}()};

		
		const std::vector<GroupID> chargeGroups_;

		Socket socketValue_ = anySocket;
		std::chrono::milliseconds defaultReloadTime_;
		std::optional<std::chrono::milliseconds> lifeTimeValue_;
		
		struct {
			bool canBeOnline : 1;
			bool canBeActive : 1;
			bool canBeOverloaded : 1;
			bool forceReload : 1;
			bool requireTarget : 1;
			bool fail : 1;
		} flags_;
		std::unique_ptr<Charge> chargeValue_;
		Ship* targetValue_ {nullptr};
		bool factorReload_() const noexcept;

		Module (TypeID typeID);
		Module (const Module& other);
		
		bool canBeOnline_()		const noexcept	{ return flags_.canBeOnline; }
		bool canBeActive_()		const noexcept;
		bool canBeOverloaded_()	const noexcept	{ return flags_.canBeOverloaded; }

		void socket_ (Socket socket) noexcept { socketValue_ = socket; }
		Socket socket_ () const noexcept { return socketValue_; }
		void adjustState_();
		void fail_ (bool fail) noexcept { flags_.fail = fail; }
		
		
		bool canHaveState_ (State state);
		std::vector<State> availableStates_();
		
		State state_() const noexcept {return stateValue_;}
		State preferredState_() const noexcept {return preferredStateValue_;}
		void state_ (State state);
		
		Ship* target_() const noexcept { return targetValue_; }
		void target_(Ship* target);

		Charge* charge_() const noexcept { return chargeValue_.get(); }
		Charge* charge_ (std::unique_ptr<Charge>&& charge);
		bool canFit_ (Charge* charge);

		bool requireTarget_()	const noexcept;
		bool fail_()				const noexcept	{ return flags_.fail; }

		
		//Calculations
		
		std::chrono::milliseconds reloadTime_();
		std::chrono::milliseconds cycleTime_();
		std::chrono::milliseconds rawCycleTime_();
		
		std::size_t charges_();
		std::size_t shots_();
		
		GigaJoulePerSecond capUse_();
		Teraflops cpuUse_();
		MegaWatts powerGridUse_();
		CalibrationPoints calibrationUse_();
		
		Points accuracyScore_();
		Meter signatureResolution_();
		CubicMeterPerSecond miningYield_();
		
		DamageVector volley_();
		DamagePerSecond dps_(const HostileTarget& target = HostileTarget::Default());
		Meter optimal_();
		Meter falloff_();
		
		std::optional<std::chrono::milliseconds> lifeTime_();
		void lifeTime_ (std::chrono::milliseconds lifeTime) noexcept { lifeTimeValue_ = lifeTime; };

		RadiansPerSecond angularVelocity_(Meter targetSignature, Percent hitChance = 0.75);
	};
}
