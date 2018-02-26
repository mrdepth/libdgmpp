%include "Type.i"
%include "Module.i"
%include "Drone.i"
%include "Area.i"

namespace std {
	%template(CategoryIDs) vector<dgmpp::CategoryID>;
	%template(Modules) vector<dgmpp::Module*>;
	%template(Drones) vector<dgmpp::Drone*>;
}


namespace dgmpp {
	
	%nodefaultctor Capacitor;
	class Capacitor {
	public:
		GigaJoule capacity();
		bool isStable();
		Percent stableLevel();
		%extend {
			
			dgmpp::Seconds rechargeTime() {
				return dgmpp::MakeSeconds($self->rechargeTime());
			}
			
			dgmpp::Seconds lastsTime() {
				return dgmpp::MakeSeconds($self->lastsTime());
			}
		};
		GigaJoulePerSecond use();
		GigaJoulePerSecond recharge();

	};
	
	class Ship: public Type {
	public:
		enum class ScanType {
			radar,
			ladar,
			magnetometric,
			gravimetric,
			multispectral
		};
		
		enum class RigSize {
			none = 0,
			small = 1,
			medium = 2,
			large = 3,
			xLarge = 4
		};
		
		std::vector<CategoryID> supportedDroneCategories();
		RigSize rigSize();
		
		void damagePattern (const DamageVector& pattern) noexcept;
		const DamageVector& damagePattern() const noexcept;
		
		//Fitting
		Module* addModule (TypeID typeID, Module::Socket socket = Module::anySocket, bool ignoringRequirements = false);
		Drone* addDrone (TypeID typeID, Drone::SquadronTag squadronTag = Drone::anySquadronTag);
		
		void remove (Module* module);
		void remove (Drone* drone);
		bool canFit (Module* module);
		bool canFit (Drone* drone);
		std::vector<Module*> modules (Module::Slot slot) const;
		std::vector<Module*> modules () const;
		std::vector<Drone*> drones () const;
		
//		bool factorReload() const noexcept;

		//Drones
		size_t totalDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none);
		size_t usedDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none);
		size_t totalFighterLaunchTubes();
		size_t usedFighterLaunchTubes();
		
		
		//Resources
		size_t totalSlots	(Module::Slot slot);
		size_t freeSlots	(Module::Slot slot);
		size_t usedSlots	(Module::Slot slot);
		
		size_t totalHardpoints	(Module::Hardpoint hardpoint);
		size_t freeHardpoints	(Module::Hardpoint hardpoint);
		size_t usedHardpoints	(Module::Hardpoint hardpoint);
		
		Capacitor& capacitor() noexcept;
		
		CalibrationPoints	usedCalibration();
		CalibrationPoints	totalCalibration();
		GigaJoule			usedPowerGrid();
		GigaJoule			totalPowerGrid();
		Teraflops			usedCPU();
		Teraflops			totalCPU();
		MegabitsPerSecond	usedDroneBandwidth();
		MegabitsPerSecond	totalDroneBandwidth();
		CubicMeter			usedDroneBay();
		CubicMeter			totalDroneBay();
		CubicMeter			usedFighterHangar();
		CubicMeter			totalFighterHangar();
		CubicMeter			cargoCapacity();
		CubicMeter			specialHoldCapacity();
		
		//Tank
		Resistances resistances();
		Tank tank();
		Tank effectiveTank();
		Tank sustainableTank();
		Tank effectiveSustainableTank();
		
		HitPoints hitPoints();
		HitPoints effectiveHitPoints();
		
		//DPS
		DamageVector	turretsVolley();
		DamageVector	launchersVolley();
		DamageVector	dronesVolley();
		DamagePerSecond	turretsDPS		();
		DamagePerSecond	launchersDPS	();
		DamagePerSecond dronesDPS		();
		
		//Mining
		CubicMeterPerSecond minerYield();
		CubicMeterPerSecond droneYield();
		
		//Mobility
		%extend {
			Seconds alignTime() {
				return dgmpp::MakeSeconds($self->alignTime());
			}
		}
		AstronomicalUnitsPerSecond warpSpeed();
		AstronomicalUnit maxWarpDistance();
		MetersPerSecond velocity();
		Meter signatureRadius();
		Kilogram mass();
		CubicMeter volume();
		Multiplier agility();
		MetersPerSecond maxVelocityInOrbit (Meter r);
		Meter orbitRadiusWithTransverseVelocity (MetersPerSecond v);
		Meter orbitRadiusWithAngularVelocity (RadiansPerSecond v);
		
		//Targeting
		size_t maxTargets();
		Meter maxTargetRange();
		Points scanStrength();
		ScanType scanType();
		Meter probeSize();
		Millimeter scanResolution();
	};
}
