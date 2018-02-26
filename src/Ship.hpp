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

		
		
		static std::unique_ptr<Ship> Create (TypeID typeID) { return std::unique_ptr<Ship>(new Ship(typeID)); }
		static std::unique_ptr<Ship> Create (const Ship& other) { return std::unique_ptr<Ship>(new Ship(other)); }
		
		RaceID raceID() const noexcept { return raceID_; }
		std::vector<CategoryID> supportedDroneCategories() const noexcept { return supportedDroneCategories_; }
		RigSize rigSize() const noexcept { return rigSize_; }

		const std::string& name() const noexcept { LOCK(this); return name_(); }
		template<typename T>
		void name (T&& name) noexcept { LOCK(this); name_(name); }

		void damagePattern (const DamageVector& pattern) noexcept { LOCK(this); damagePattern_(pattern); }
		const DamageVector& damagePattern() const noexcept { LOCK(this); return damagePattern_(); }

		//Fitting
		Module* add (std::unique_ptr<Module>&& module, Module::Socket socket = Module::anySocket, bool ignoringRequirements = false) { LOCK(this); return add_(std::move(module), socket, ignoringRequirements); }
		Drone* add (std::unique_ptr<Drone>&& drone, Drone::SquadronTag squadronTag = Drone::anySquadronTag) { LOCK(this); return add_(std::move(drone), squadronTag); }
		Module* addModule (TypeID typeID, Module::Socket socket = Module::anySocket, bool ignoringRequirements = false) { return add(Module::Create(typeID), socket, ignoringRequirements); }
		Drone* addDrone (TypeID typeID, Drone::SquadronTag squadronTag = Drone::anySquadronTag) { return add(Drone::Create(typeID), squadronTag); }

		void remove (Module* module) { LOCK(this); remove_(module); }
		void remove (Drone* drone) { LOCK(this); remove_(drone); }
		bool canFit (Module* module) { LOCK(this); return canFit_(module); }
		bool canFit (Drone* drone) { LOCK(this); return canFit_(drone); }
		std::vector<Module*> modules (Module::Slot slot) const { LOCK(this); return modules_(slot); }
		std::vector<Module*> modules () const { LOCK(this); return modules_(); }
		std::vector<Drone*> drones () const { LOCK(this); return drones_(); }
		
		//Drones
		std::size_t totalDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none) { LOCK(this); return totalDroneSquadron_(squadron); }
		std::size_t usedDroneSquadron (Drone::Squadron squadron = Drone::Squadron::none) { LOCK(this); return usedDroneSquadron_(squadron); }
		std::size_t totalFighterLaunchTubes() { LOCK(this); return totalFighterLaunchTubes_(); }
		std::size_t usedFighterLaunchTubes() { LOCK(this); return usedFighterLaunchTubes_(); }


		//Resources
		std::size_t totalSlots	(Module::Slot slot) { LOCK(this); return totalSlots_(slot); }
		std::size_t freeSlots	(Module::Slot slot) { LOCK(this); return freeSlots_(slot); }
		std::size_t usedSlots	(Module::Slot slot) { LOCK(this); return usedSlots_(slot); }

		std::size_t totalHardpoints	(Module::Hardpoint hardpoint) { LOCK(this); return totalHardpoints_(hardpoint); }
		std::size_t freeHardpoints	(Module::Hardpoint hardpoint) { LOCK(this); return freeHardpoints_(hardpoint); }
		std::size_t usedHardpoints	(Module::Hardpoint hardpoint) { LOCK(this); return usedHardpoints_(hardpoint); }
		
		Capacitor& capacitor() noexcept { return capacitor_; }

		CalibrationPoints	usedCalibration()		{ LOCK(this); return usedCalibration_(); }
		CalibrationPoints	totalCalibration()		{ LOCK(this); return totalCalibration_(); }
		GigaJoule			usedPowerGrid()			{ LOCK(this); return usedPowerGrid_(); }
		GigaJoule			totalPowerGrid()		{ LOCK(this); return totalPowerGrid_(); }
		Teraflops			usedCPU()				{ LOCK(this); return usedCPU_(); }
		Teraflops			totalCPU()				{ LOCK(this); return totalCPU_(); }
		MegabitsPerSecond	usedDroneBandwidth()	{ LOCK(this); return usedDroneBandwidth_(); }
		MegabitsPerSecond	totalDroneBandwidth()	{ LOCK(this); return totalDroneBandwidth_(); }
		CubicMeter			usedDroneBay()			{ LOCK(this); return usedDroneBay_(); }
		CubicMeter			totalDroneBay()			{ LOCK(this); return totalDroneBay_(); }
		CubicMeter			usedFighterHangar()		{ LOCK(this); return usedFighterHangar_(); }
		CubicMeter			totalFighterHangar()	{ LOCK(this); return totalFighterHangar_(); }
		CubicMeter			cargoCapacity()			{ LOCK(this); return cargoCapacity_(); }
		CubicMeter			specialHoldCapacity()	{ LOCK(this); return specialHoldCapacity_(); }

		//Tank
		Resistances resistances()	{ LOCK(this); return resistances_(); }
		Tank tank()	{ LOCK(this); return tank_(); }
		Tank effectiveTank()	{ LOCK(this); return effectiveTank_(); }
		Tank sustainableTank()	{ LOCK(this); return sustainableTank_(); }
		Tank effectiveSustainableTank()	{ LOCK(this); return effectiveSustainableTank_(); }

		HitPoints hitPoints()	{ LOCK(this); return hitPoints_(); }
		HitPoints effectiveHitPoints()	{ LOCK(this); return effectiveHitPoints_(); }

		//DPS
		DamageVector	turretsVolley()	{ LOCK(this); return turretsVolley_(); }
		DamageVector	launchersVolley()	{ LOCK(this); return launchersVolley_(); }
		DamageVector	dronesVolley()	{ LOCK(this); return dronesVolley_(); }
		DamagePerSecond	turretsDPS		(const HostileTarget& target = HostileTarget::Default())	{ LOCK(this); return turretsDPS_(target); }
		DamagePerSecond	launchersDPS	(const HostileTarget& target = HostileTarget::Default())	{ LOCK(this); return launchersDPS_(target); }
		DamagePerSecond dronesDPS		(const HostileTarget& target = HostileTarget::Default())	{ LOCK(this); return dronesDPS_(target); }

		//Mining
		CubicMeterPerSecond minerYield()	{ LOCK(this); return minerYield_(); }
		CubicMeterPerSecond droneYield()	{ LOCK(this); return droneYield_(); }

		//Mobility
		std::chrono::milliseconds alignTime()	{ LOCK(this); return alignTime_(); }
		AstronomicalUnitsPerSecond warpSpeed()	{ LOCK(this); return warpSpeed_(); }
		AstronomicalUnit maxWarpDistance()	{ LOCK(this); return maxWarpDistance_(); }
		MetersPerSecond velocity()	{ LOCK(this); return velocity_(); }
		Meter signatureRadius()	{ LOCK(this); return signatureRadius_(); }
		Kilogram mass()	{ LOCK(this); return mass_(); }
		CubicMeter volume()	{ LOCK(this); return volume_(); }
		Multiplier agility()	{ LOCK(this); return agility_(); }
		MetersPerSecond maxVelocityInOrbit (Meter r)	{ LOCK(this); return maxVelocityInOrbit_(r); }
		Meter orbitRadiusWithTransverseVelocity (MetersPerSecond v)	{ LOCK(this); return orbitRadiusWithTransverseVelocity_(v); }
		Meter orbitRadiusWithAngularVelocity (RadiansPerSecond v)	{ LOCK(this); return orbitRadiusWithAngularVelocity_(v); }

		//Targeting
		std::size_t maxTargets()	{ LOCK(this); return maxTargets_(); }
		Meter maxTargetRange()	{ LOCK(this); return maxTargetRange_(); }
		Points scanStrength()	{ LOCK(this); return scanStrength_(); }
		ScanType scanType()	{ LOCK(this); return scanType_(); }
		Meter probeSize()	{ LOCK(this); return probeSize_(); }
		Millimeter scanResolution()	{ LOCK(this); return scanResolution_(); }
		
	protected:
		using ModulesContainer = TuplesSet<Module::Slot, Module::Socket, std::unique_ptr<Module>>;
		using DronesContainer = TuplesSet<TypeID, Drone::SquadronTag, std::unique_ptr<Drone>>;

		ModulesContainer modulesSet_;
		DronesContainer dronesSet_;
		
		std::list<Module*> projectedModules_;
		std::list<Drone*> projectedDrones_;

		const RigSize rigSize_ {[this]() {
			return static_cast<RigSize>(static_cast<int>(attribute_(AttributeID::rigSize)->value_()));
		}()};
		
		const RaceID raceID_ {[this]() {
			return static_cast<RaceID>(static_cast<int>(attribute_(AttributeID::raceID)->value_()));
		}()};

		Ship (TypeID typeID);
		Ship (const Ship& other);
		
		virtual void setEnabled_ (bool enabled) override;
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
		virtual void reset_() override;
		
		void project_ (Module* module);
		void project_ (Drone* drone);
		void removeProjected_ (Module* module);
		void removeProjected_ (Drone* drone);

		slice<ModulesContainer::const_iterator> modulesSlice_ (Module::Slot slot) const noexcept;

		virtual bool isDisallowedAssistance_() override;
		virtual bool isDisallowedOffense_() override;

		Area* area_() const noexcept { return areaValue_.get(); }
		Area* area_(std::unique_ptr<Area>&& area);

	private:
		friend class Character;
		friend class Capacitor;
		friend class HeatSimulator;
		friend class Module;
		friend class Drone;
		friend class Gang;
		
		std::unique_ptr<Area> areaValue_;
		
		Capacitor capacitor_;
		HeatSimulator heatSimulator_;
		DamageVector damagePatternValue_ = {0.25};
		std::string nameValue_;
		
		
		const std::vector<CategoryID> supportedDroneCategories_ {[this]() -> std::vector<CategoryID> {
			if (attribute_(AttributeID::fighterCapacity))
				return {CategoryID::fighter};
			else
				return {CategoryID::drone};
		}()};
		
		
		std::optional<bool> isDisallowedAssistanceValue_;
		std::optional<bool> isDisallowedOffenseValue_;

		bool factorReload_() const noexcept;

		
		const std::string& name_() const noexcept { return nameValue_; }
		template<typename T>
		void name_ (T&& name) noexcept { nameValue_ = std::forward<T>(name); }
		
		void damagePattern_ (const DamageVector& pattern) noexcept { damagePatternValue_ = pattern; resetCache_(); }
		const DamageVector& damagePattern_() const noexcept { return damagePatternValue_; }

		//Fitting
		Module* add_ (std::unique_ptr<Module>&& module, Module::Socket socket = Module::anySocket, bool ignoringRequirements = false);
		Drone* add_ (std::unique_ptr<Drone>&& drone, Drone::SquadronTag squadronTag = Drone::anySquadronTag);

		void remove_ (Module* module);
		void remove_ (Drone* drone);
		bool canFit_ (Module* module);
		bool canFit_ (Drone* drone);
		std::vector<Module*> modules_ (Module::Slot slot) const;
		std::vector<Module*> modules_ () const;
		std::vector<Drone*> drones_ () const;

		//Drones
		std::size_t totalDroneSquadron_ (Drone::Squadron squadron = Drone::Squadron::none);
		std::size_t usedDroneSquadron_ (Drone::Squadron squadron = Drone::Squadron::none);
		std::size_t totalFighterLaunchTubes_();
		std::size_t usedFighterLaunchTubes_();
		
		
		//Resources
		std::size_t totalSlots_	(Module::Slot slot);
		std::size_t freeSlots_	(Module::Slot slot) {return totalSlots_(slot) - usedSlots_(slot);}
		std::size_t usedSlots_	(Module::Slot slot) {return modulesSlice_(slot).size();}
		
		std::size_t totalHardpoints_	(Module::Hardpoint hardpoint);
		std::size_t freeHardpoints_		(Module::Hardpoint hardpoint);
		std::size_t usedHardpoints_		(Module::Hardpoint hardpoint);

		CalibrationPoints	usedCalibration_();
		CalibrationPoints	totalCalibration_();
		GigaJoule			usedPowerGrid_();
		GigaJoule			totalPowerGrid_();
		Teraflops			usedCPU_();
		Teraflops			totalCPU_();
		MegabitsPerSecond	usedDroneBandwidth_();
		MegabitsPerSecond	totalDroneBandwidth_();
		CubicMeter			usedDroneBay_();
		CubicMeter			totalDroneBay_();
		CubicMeter			usedFighterHangar_();
		CubicMeter			totalFighterHangar_();
		CubicMeter			cargoCapacity_();
		CubicMeter			specialHoldCapacity_();
		
		//Tank
		Resistances resistances_();
		Tank tank_();
		Tank effectiveTank_();
		Tank sustainableTank_();
		Tank effectiveSustainableTank_();
		
		HitPoints hitPoints_();
		HitPoints effectiveHitPoints_();
		
		//DPS
		DamageVector	turretsVolley_();
		DamageVector	launchersVolley_();
		DamageVector	dronesVolley_();
		DamagePerSecond	turretsDPS_		(const HostileTarget& target = HostileTarget::Default());
		DamagePerSecond	launchersDPS_	(const HostileTarget& target = HostileTarget::Default());
		DamagePerSecond dronesDPS_		(const HostileTarget& target = HostileTarget::Default());
		
		//Mining
		CubicMeterPerSecond minerYield_();
		CubicMeterPerSecond droneYield_();
		
		//Mobility
		std::chrono::milliseconds alignTime_();
		AstronomicalUnitsPerSecond warpSpeed_();
		AstronomicalUnit maxWarpDistance_();
		MetersPerSecond velocity_();
		Meter signatureRadius_();
		Kilogram mass_();
		CubicMeter volume_();
		Multiplier agility_();
		MetersPerSecond maxVelocityInOrbit_ (Meter r);
		Meter orbitRadiusWithTransverseVelocity_ (MetersPerSecond v);
		Meter orbitRadiusWithAngularVelocity_ (RadiansPerSecond v);
		
		//Targeting
		std::size_t maxTargets_();
		Meter maxTargetRange_();
		Points scanStrength_();
		ScanType scanType_();
		Meter probeSize_();
		Millimeter scanResolution_();
	};
}
