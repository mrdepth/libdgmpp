%include "std_unique_ptr.i"
%include "Type.i"
%include "Charge.i"

%unique_ptr(dgmpp::Module)

namespace dgmpp {
	class Ship;
	class Module : public Type {
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
		
		static std::unique_ptr<Module> Create (TypeID typeID);
		
		bool canHaveState (State state);
		std::vector<State> availableStates();
		
		State state() const noexcept;
		State preferredState() const noexcept;
		void state (State state);
		
		Ship* target() const noexcept;
		void target(Ship* target);
		
		Slot slot() const noexcept;
		Hardpoint hardpoint() const noexcept;
		Socket socket() const noexcept;
		
		Charge* charge() const noexcept;
		Charge* charge (TypeID typeID);
		bool canFit (Charge* charge);
		const std::vector<GroupID>& chargeGroups() const noexcept;
		
		Charge::Size chargeSize();
		
//		bool canBeOnline()		const noexcept;
//		bool canBeActive()		const noexcept;
//		bool canBeOverloaded()	const noexcept;
		bool requireTarget()	const noexcept;
		bool fail()				const noexcept;
		
//		bool factorReload()		const noexcept;
		
		//Calculations
		
		
		size_t charges();
		size_t shots();
		
		GigaJoulePerSecond capUse();
		Teraflops cpuUse();
		MegaWatts powerGridUse();
		CalibrationPoints calibrationUse();
		
		Points accuracyScore();
		Meter signatureResolution();
		CubicMeterPerSecond miningYield();
		
		DamageVector volley();
		DamagePerSecond dps();
		Meter optimal();
		Meter falloff();
		
		%extend {
			Seconds reloadTime() {
				return dgmpp::MakeSeconds($self->reloadTime());
			}
			
			Seconds cycleTime() {
				return dgmpp::MakeSeconds($self->cycleTime());
			}
			
			Seconds rawCycleTime() {
				return dgmpp::MakeSeconds($self->rawCycleTime());
			}

			Seconds lifeTime() {
				if (auto lifeTime = $self->lifeTime())
					return dgmpp::MakeSeconds(*lifeTime);
				else
					return -1;
			}
		}
	};
}

namespace std {
	%template(GroupIDs) vector<dgmpp::GroupID>;
	%template(States) vector<dgmpp::Module::State>;
}
