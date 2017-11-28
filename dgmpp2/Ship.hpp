//
//  Ship.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Type.hpp"
#include "Module.hpp"
#include "Drone.hpp"
#include "Capacitor.hpp"
#include "Tank.hpp"
#include "HitPoints.hpp"

namespace dgmpp2 {
	class Module;
	
	class Ship: public Type {
	public:
//		using Position = std::vector<Module*>::const_iterator;
		using ModulesContainer = TuplesSet<Module::Slot, Module::Socket, std::unique_ptr<Module>>;
		using DronesContainer = TuplesSet<TypeID, Drone::SquadronTag, std::unique_ptr<Drone>>;
		
		enum class ScanType
		{
			radar,
			ladar,
			magnetometric,
			gravimetric,
			multispectral
		};
		
		
		static std::unique_ptr<Ship> Create (TypeID typeID) { return std::unique_ptr<Ship>(new Ship(typeID)); }

		RaceID raceID();
		std::vector<CategoryID> supportedDroneCategories();
		int rigSize() { return static_cast<int>((*this)[AttributeID::rigSize]->value()); }
		
		void damagePattern (const DamageVector& pattern) { damagePattern_ = pattern; resetCache(); }
		const DamageVector& damagePattern() const { return damagePattern_; }

		//Fitting
		Module* add (std::unique_ptr<Module> module, bool forced = false, Module::Socket socket = Module::anySocket);
		Drone* add (std::unique_ptr<Drone> drone, Drone::SquadronTag squadronTag = Drone::anySquadronTag);
		void remove (Module* module);
		void remove (Drone* drone);
		bool canFit (Module* module);
		bool canFit (Drone* drone);
		std::vector<Module*> modules (Module::Slot slot) const;
		std::vector<Module*> modules () const;// {return modules_;}
		std::vector<Drone*> drones () const;// {return drones_;}
		
		//Drones
		size_t totalDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none);
		size_t usedDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none);
		size_t totalFighterLaunchTubes();
		size_t usedFighterLaunchTubes();

		
		//Resources
		size_t totalSlots (Module::Slot slot);
		size_t freeSlots (Module::Slot slot) {return totalSlots(slot) - usedSlots(slot);}
		size_t usedSlots (Module::Slot slot) {return slice(slot).size();}
		
		size_t totalHardpoints (Module::Hardpoint hardpoint);
		size_t freeHardpoints (Module::Hardpoint hardpoint);
		size_t usedHardpoints (Module::Hardpoint hardpoint);
		
		Capacitor& capacitor() { return capacitor_; }

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
		CubicMeter			oreHoldCapacity();

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
		DamagePerSecond	turretsDPS		(const HostileTarget& target = HostileTarget::Default());
		DamagePerSecond	launchersDPS	(const HostileTarget& target = HostileTarget::Default());
		DamagePerSecond dronesDPS		(const HostileTarget& target = HostileTarget::Default());

		//Mining
		CubicMeterPerSecond minerYield();
		CubicMeterPerSecond droneYield();

		//Mobility
		std::chrono::milliseconds alignTime();
		AstronomicalUnitsPerSecond getWarpSpeed();
		AstronomicalUnit maxWarpDistance();
		MetersPerSecond velocity();
		Meter signatureRadius();
		Kilogram mass();
		CubicMeter volume();
		Multiplier agility();
		MetersPerSecond maxVelocityInOrbit(Meter r);
		Meter orbitRadiusWithTransverseVelocity(MetersPerSecond v);
		Meter orbitRadiusWithAngularVelocity(RadiansPerSecond v);

		//Targeting
		size_t maxTargets();
		Meter maxTargetRange();
		Points scanStrength();
		ScanType scanType();
		Meter probeSize();
		Millimeter scanResolution();
		
		virtual void setEnabled (bool enabled) override;
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		virtual void reset() override;
		
		const std::list<Module*>& projectedModules() const { return projectedModules_; }
		const std::list<Drone*>& projectedDrones() const { return projectedDrones_; }
		void project(Module* module);
		void project(Drone* drone);
		void removeProjected(Module* module);
		void removeProjected(Drone* drone);

		slice<ModulesContainer::const_iterator> slice (Module::Slot slot) const;

	private:
		friend class Character;
		friend class Capacitor;
		friend class Module;
		friend class Drone;
		
		Ship (TypeID typeID): Type(typeID), capacitor_(*this) {};
		
		ModulesContainer modules_;
		DronesContainer drones_;
		
		std::list<Module*> projectedModules_;
		std::list<Drone*> projectedDrones_;
		
		Capacitor capacitor_;
		DamageVector damagePattern_ = {0.25};

	};
}
