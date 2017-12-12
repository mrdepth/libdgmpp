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
#include "Area.hpp"
#include "HeatSimulator.hpp"

namespace dgmpp {
	class Module;
	
	class Ship: public Type {
	public:
//		using Position = std::vector<Module*>::const_iterator;
		
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
		
		void damagePattern (const DamageVector& pattern) noexcept { damagePattern_ = pattern; resetCache(); }
		const DamageVector& damagePattern() const noexcept { return damagePattern_; }

		//Fitting
		Module* add (std::unique_ptr<Module>&& module, bool ignoringRequirements = false, Module::Socket socket = Module::anySocket);
		Drone* add (std::unique_ptr<Drone>&& drone, Drone::SquadronTag squadronTag = Drone::anySquadronTag);
		Module* addModule (TypeID typeID, bool ignoringRequirements = false, Module::Socket socket = Module::anySocket) { return add(Module::Create(typeID), ignoringRequirements, socket); }
		Drone* add (TypeID typeID, Drone::SquadronTag squadronTag = Drone::anySquadronTag) { return add(Drone::Create(typeID), squadronTag); }

		void remove (Module* module);
		void remove (Drone* drone);
		bool canFit (Module* module);
		bool canFit (Drone* drone);
		std::vector<Module*> modules (Module::Slot slot) const;
		std::vector<Module*> modules () const;// {return modules_;}
		std::vector<Drone*> drones () const;// {return drones_;}
		
		Area* area() const noexcept { return area_.get(); }
		Area* area(std::unique_ptr<Area>&& area);
		Area* area(TypeID typeID) { return area(Area::Create(typeID)); }
		
		//Drones
		size_t totalDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none);
		size_t usedDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none);
		size_t totalFighterLaunchTubes();
		size_t usedFighterLaunchTubes();

		
		//Resources
		size_t totalSlots	(Module::Slot slot);
		size_t freeSlots	(Module::Slot slot) {return totalSlots(slot) - usedSlots(slot);}
		size_t usedSlots	(Module::Slot slot) {return slice(slot).size();}
		
		size_t totalHardpoints	(Module::Hardpoint hardpoint);
		size_t freeHardpoints	(Module::Hardpoint hardpoint);
		size_t usedHardpoints	(Module::Hardpoint hardpoint);
		
		Capacitor& capacitor() noexcept { return capacitor_; }

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
		AstronomicalUnitsPerSecond warpSpeed();
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
		using ModulesContainer = TuplesSet<Module::Slot, Module::Socket, std::unique_ptr<Module>>;
		using DronesContainer = TuplesSet<TypeID, Drone::SquadronTag, std::unique_ptr<Drone>>;

		ModulesContainer modules_;
		DronesContainer drones_;
		
		std::list<Module*> projectedModules_;
		std::list<Drone*> projectedDrones_;

		Ship (TypeID typeID): Type(typeID), capacitor_(*this), heatSimulator_(*this) {};
		
		virtual Type* domain (MetaInfo::Modifier::Domain domain) noexcept override;
		virtual void reset() override;
		
		const std::list<Module*>& projectedModules() const noexcept { return projectedModules_; }
		const std::list<Drone*>& projectedDrones() const noexcept { return projectedDrones_; }
		void project(Module* module);
		void project(Drone* drone);
		void removeProjected(Module* module);
		void removeProjected(Drone* drone);

		slice<ModulesContainer::const_iterator> slice (Module::Slot slot) const noexcept;

	private:
		friend class Character;
		friend class Capacitor;
		friend class Module;
		friend class Drone;
		
		std::unique_ptr<Area> area_;
		
		Capacitor capacitor_;
		HeatSimulator heatSimulator_;
		DamageVector damagePattern_ = {0.25};

	};
}
