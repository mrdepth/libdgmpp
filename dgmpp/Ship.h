#pragma once
#include "Item.h"
#include "Module.h"
#include "Drone.h"
#include "CapacitorSimulator.h"
#include "HeatSimulator.h"
#include "DamagePattern.h"
#include "Cargo.h"
#include "Type.hpp"

namespace dgmpp {

	class Ship : public Item
	{
	public:
		enum class ScanType
		{
			radar,
			ladar,
			magnetometric,
			gravimetric,
			multispectral
		};
		Ship(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner = std::shared_ptr<Character>(nullptr));
		virtual ~Ship(void);
		std::shared_ptr<Ship> shared_from_this() {
			return std::static_pointer_cast<Ship>(Item::shared_from_this());
		}

		std::shared_ptr<Module> addModule(TypeID typeID, bool forced = false, int socket = -1);
		std::shared_ptr<Module> replaceModule(std::shared_ptr<Module> const& oldModule, TypeID typeID);
		ModulesList addModules(const std::list<TypeID>& typeIDs);
		void removeModule(std::shared_ptr<Module> const& module);
		
		std::shared_ptr<Drone> addDrone(TypeID typeID, int squadronTag = -1);
		void removeDrone(std::shared_ptr<Drone> const& drone);
		
		ModulesList getModules(bool includingDummies = false);
		ModulesList getModules(Module::Slot slot, bool includingDummies = false);
		const DronesList& getDrones();
		const std::list<std::weak_ptr<Module>>& getProjectedModules();
		const std::list<std::weak_ptr<Drone>>& getProjectedDrones();
		bool canFit(std::shared_ptr<Module> const& module);
		bool isDisallowedAssistance();
		bool isDisallowedOffensiveModifiers();

		virtual void reset();
		
		virtual std::vector<CategoryID> getSupportedModuleCategories() const;
		virtual std::vector<CategoryID> getSupportedDroneCategories() const;
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		void addProjectedModule(std::shared_ptr<Module> const& module);
		void removeProjectedModule(std::shared_ptr<Module> const& module);
		void addProjectedDrone(std::shared_ptr<Drone> const& drone);
		void removeProjectedDrone(std::shared_ptr<Drone> const& drone);
		
		std::shared_ptr<CapacitorSimulator> getCapacitorSimulator();
		std::shared_ptr<HeatSimulator> getHeatSimulator();
		const DamagePattern& getDamagePattern();
		void setDamagePattern(const DamagePattern& damagePattern);
		
		std::shared_ptr<Cargo> addCargo(TypeID typeID, size_t count);
		void removeCarge(TypeID typeID, size_t count);
		const CargoList& getCargo();
		
		void setName(const char* name);
		const char* getName();

		//Calculations
		
		int getNumberOfSlots(Module::Slot slot);
		int getFreeSlots(Module::Slot slot);
		int getUsedSlots(Module::Slot slot);
		int getNumberOfHardpoints(Module::Hardpoint hardpoint);
		int getFreeHardpoints(Module::Hardpoint hardpoint);
		int getUsedHardpoints(Module::Hardpoint hardpoint);
		int getRigSize();
		RaceID getRaceID();
		
		Float getCapacity();
		Float getOreHoldCapacity();
		
		Float getCalibrationUsed();
		Float getTotalCalibration();
		Float getPowerGridUsed();
		Float getTotalPowerGrid();
		Float getCpuUsed();
		Float getTotalCpu();
		Float getDroneBandwidthUsed();
		Float getTotalDroneBandwidth();
		Float getDroneBayUsed();
		Float getTotalDroneBay();
		Float getFighterHangarUsed();
		Float getTotalFighterHangar();
		
		
		//Capacitor
		Float getCapCapacity();
		bool isCapStable();
		Float getCapLastsTime();
		Float getCapStableLevel();
		Float getCapUsed();
		Float getCapRecharge();
		Float getCapRechargeTime();
		
		//Tank
		const Resistances& getResistances();
		const Tank& getTank();
		const Tank& getEffectiveTank();
		const Tank& getSustainableTank();
		const Tank& getEffectiveSustainableTank();
		
		const HitPoints& getHitPoints();
		const HitPoints& getEffectiveHitPoints();
		
		Float getShieldRecharge();

		//DPS
		DamageVector getWeaponDps(const HostileTarget& target = HostileTarget::defaultTarget);
		DamageVector getWeaponVolley();
		DamageVector getDroneDps(const HostileTarget& target = HostileTarget::defaultTarget);
		DamageVector getDroneVolley();
		
		//Mining
		Float getMinerYield();
		Float getDroneYield();
		
		//Mobility
		Float getAlignTime();
		Float getWarpSpeed();
		Float getMaxWarpDistance();
		Float getVelocity();
		Float getSignatureRadius();
		Float getMass();
		Float getVolume();
		Float getAgility();
		Float getMaxVelocityInOrbit(Float r);
		Float getOrbitRadiusWithTransverseVelocity(Float v);
		Float getOrbitRadiusWithAngularVelocity(Float v);
		
		//Targeting
		int getMaxTargets();
		Float getMaxTargetRange();
		Float getScanStrength();
		ScanType getScanType();
		Float getProbeSize();
		Float getScanResolution();
		
		//Drones
		int getDroneSquadronLimit(Drone::FighterSquadron squadron = Drone::FighterSquadron::none);
		int getDroneSquadronUsed(Drone::FighterSquadron squadron = Drone::FighterSquadron::none);
		int getTotalFighterLaunchTubes();
		int getFighterLaunchTubesUsed();

		//Other
		void updateHeatDamage();
		
		virtual Item* ship();
		virtual Item* character();

		friend std::ostream& operator<<(std::ostream& os, Ship& ship);
	protected:
		std::map<Module::Slot, ModulesList> modules_;
		DronesList drones_;
		CargoList cargo_;
	private:
		std::list<std::weak_ptr<Module>> projectedModules_;
		std::list<std::weak_ptr<Drone>> projectedDrones_;
		std::shared_ptr<CapacitorSimulator> capacitorSimulator_;
		std::shared_ptr<HeatSimulator> heatSimulator_;
		DamagePattern damagePattern_;
		std::string name_;
		
		Resistances resistances_;
		Tank tank_;
		Tank effectiveTank_;
		Tank sustainableTank_;
		Tank effectiveSustainableTank_;
		HitPoints hitPoints_;
		HitPoints effectiveHitPoints_;
		Float shieldRecharge_;
		
		enum {
			UNKNOWN = -1,
			ALLOWED,
			DISALLOWED
		} disallowAssistance_, disallowOffensiveModifiers_;
		
		void updateModulesState();
		void updateEnabledStatus();
		void updateModulesSockets();

	};
}

namespace dgmpp2 {
	class Module;
	
	class Ship: public Type {
	public:
		static std::unique_ptr<Ship> Create (TypeID typeID) { return std::unique_ptr<Ship>(new Ship(typeID)); }
		Module* add (std::unique_ptr<Module> module);
		void remove (Module* module);
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
	private:
		Ship (TypeID typeID): Type(typeID) {};
		std::vector<Module*> modules_;
	};
}
