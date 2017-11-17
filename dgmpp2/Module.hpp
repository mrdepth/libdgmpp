//
//  Module.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Type.hpp"
#include "Charge.hpp"

namespace dgmpp2 {
	
	class Module: public Type {
	public:
		typedef int Socket;
		static const Socket anySocket;
		
		
		static std::unique_ptr<Module> Create (TypeID typeID) { return std::unique_ptr<Module>(new Module(typeID)); }
		
		enum class State {
			unknown = -1,
			offline,
			online,
			active,
			overloaded
		};
		
		enum class Slot
		{
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
		
		enum class Hardpoint
		{
			none,
			launcher,
			turret
		};
		
		bool canHaveState (State state);
		std::vector<State> availableStates();
		
		State state() const {return state_;}
		State preferredState() const {return preferredState_;}
		void state (State state);
		
		Slot slot() const {return slot_;}
		Hardpoint hardpoint() const {return hardpoint_;}
		Socket socket() const {return socket_;}
		
		virtual void setEnabled (bool enabled) override;
		
		Charge* charge() const;
		void charge (std::unique_ptr<Charge> charge);
		bool canFit (Charge* charge);
		const std::vector<GroupID>& chargeGroups() const { return chargeGroups_; };
		
		int chargeSize();
		
		bool canBeOnline()		const	{ return flags_.canBeOnline; }
		bool canBeActive()		const;
		bool canBeOverloaded()	const	{ return flags_.canBeOverloaded; }
		bool requireTarget()	const;

		bool factorReload()		const	{ return flags_.factorReload; }
		void factorReload (bool factorReload) { flags_.factorReload = factorReload; }

		
		//Calculations
		std::chrono::milliseconds reloadTime();
		std::chrono::milliseconds cycleTime();
		std::chrono::milliseconds rawCycleTime();

		size_t charges();
		size_t shots();
		rate<GigaJoule, std::chrono::seconds> capUse();
		
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		
	private:
		friend class Ship;
		State state_ = State::unknown;
		State preferredState_ = State::unknown;
		Slot slot_;
		Hardpoint hardpoint_;
		Socket socket_ = anySocket;
		std::chrono::milliseconds defaultReloadTime_;
		
		struct {
			bool canBeOnline : 1;
			bool canBeActive : 1;
			bool canBeOverloaded : 1;
			bool forceReload : 1;
			bool factorReload : 1;
			bool requireTarget : 1;
		} flags_;
		std::vector<GroupID> chargeGroups_;
		
		Module (TypeID typeID);
		
		void socket (Socket socket) { socket_ = socket; }
		void adjustState();
	};
}
