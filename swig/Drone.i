%include "Type.i"

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
		
		void active (bool active);
		bool active() const noexcept;
		bool hasKamikazeAbility() const noexcept;
		void kamikaze (bool kamikaze);
		bool kamikaze() const noexcept;

		Charge* charge() const noexcept;
		
		Squadron squadron() const noexcept;
		size_t squadronSize();
		
		SquadronTag squadronTag() const noexcept;
		
		Ship* target() const noexcept;
		void target(Ship* target);
		
		//Calculations
		DamageVector volley();
		DamagePerSecond dps();
		Meter optimal();
		Meter falloff();
		Points accuracyScore();
		CubicMeterPerSecond miningYield();
		MetersPerSecond velocity();
		
		%extend {
			Seconds cycleTime() {
				return dgmpp::MakeSeconds($self->cycleTime());
			}
		}
	};
}

