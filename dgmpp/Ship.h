#pragma once
#include "Item.h"
#include "Module.h"
#include "Drone.h"
#include "CapacitorSimulator.h"
#include "HeatSimulator.h"
#include "DamagePattern.h"

namespace dgmpp {

	class Ship : public Item
	{
	public:
		enum ScanType
		{
			SCAN_TYPE_RADAR,
			SCAN_TYPE_LADAR,
			SCAN_TYPE_MAGNETOMETRIC,
			SCAN_TYPE_GRAVIMETRIC,
			SCAN_TYPE_MULTISPECTRAL
		};
		Ship(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner = std::shared_ptr<Character>(nullptr));
		virtual ~Ship(void);
		std::shared_ptr<Ship> shared_from_this() {
			return std::static_pointer_cast<Ship>(Item::shared_from_this());
		}

		std::shared_ptr<Module> addModule(TypeID typeID, bool forced = false);
		std::shared_ptr<Module> replaceModule(std::shared_ptr<Module> const& oldModule, TypeID typeID);
		ModulesList addModules(const std::list<TypeID>& typeIDs);
		void removeModule(std::shared_ptr<Module> const& module);
		
		std::shared_ptr<Drone> addDrone(TypeID typeID);
		void removeDrone(std::shared_ptr<Drone> const& drone);
		
		const ModulesList& getModules();
		void getModules(Module::Slot slot, std::insert_iterator<ModulesList> outIterator);
		const DronesList& getDrones();
		const std::list<std::weak_ptr<Module>>& getProjectedModules();
		const std::list<std::weak_ptr<Drone>>& getProjectedDrones();
		bool canFit(std::shared_ptr<Module> const& module);
		bool isDisallowedAssistance();
		bool isDisallowedOffensiveModifiers();

		virtual void reset();
		
		virtual std::vector<AttributeID> getSupportedModuleCategories() const;
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
		
		//Calculations
		
		int getNumberOfSlots(Module::Slot slot);
		int getFreeSlots(Module::Slot slot);
		int getUsedSlots(Module::Slot slot);
		int getNumberOfHardpoints(Module::Hardpoint hardpoint);
		int getFreeHardpoints(Module::Hardpoint hardpoint);
		int getUsedHardpoints(Module::Hardpoint hardpoint);
		
		float getCapacity();
		float getOreHoldCapacity();
		
		float getCalibrationUsed();
		float getTotalCalibration();
		float getPowerGridUsed();
		float getTotalPowerGrid();
		float getCpuUsed();
		float getTotalCpu();
		float getDroneBandwidthUsed();
		float getTotalDroneBandwidth();
		float getDroneBayUsed();
		float getTotalDroneBay();

		
		//Capacitor
		float getCapCapacity();
		bool isCapStable();
		float getCapLastsTime();
		float getCapStableLevel();
		float getCapUsed();
		float getCapRecharge();
		
		//Tank
		const Resistances& getResistances();
		const Tank& getTank();
		const Tank& getEffectiveTank();
		const Tank& getSustainableTank();
		const Tank& getEffectiveSustainableTank();
		
		const HitPoints& getHitPoints();
		const HitPoints& getEffectiveHitPoints();
		
		float getShieldRecharge();

		//DPS
		DamageVector getWeaponDps(const HostileTarget& target = HostileTarget::defaultTarget);
		DamageVector getWeaponVolley();
		DamageVector getDroneDps(const HostileTarget& target = HostileTarget::defaultTarget);
		DamageVector getDroneVolley();
		
		//Mobility
		float getAlignTime();
		float getWarpSpeed();
		float getMaxWarpDistance();
		float getVelocity();
		float getSignatureRadius();
		float getMass();
		float getVolume();
		float getAgility();
		float getMaxVelocityInOrbit(float r);
		float getOrbitRadiusWithTransverseVelocity(float v);
		float getOrbitRadiusWithAngularVelocity(float v);
		
		//Targeting
		int getMaxTargets();
		float getMaxTargetRange();
		float getScanStrength();
		ScanType getScanType();
		float getProbeSize();
		float getScanResolution();
		
		//Drones
		int getMaxActiveDrones();
		int getActiveDrones();

		//Other
		void updateHeatDamage();
		
		virtual Item* ship();
		virtual Item* character();

		friend std::ostream& operator<<(std::ostream& os, Ship& ship);
		
	private:
		ModulesList modules_;
		DronesList drones_;
		std::list<std::weak_ptr<Module>> projectedModules_;
		std::list<std::weak_ptr<Drone>> projectedDrones_;
		std::shared_ptr<CapacitorSimulator> capacitorSimulator_;
		std::shared_ptr<HeatSimulator> heatSimulator_;
		DamagePattern damagePattern_;
		
		Resistances resistances_;
		Tank tank_;
		Tank effectiveTank_;
		Tank sustainableTank_;
		Tank effectiveSustainableTank_;
		HitPoints hitPoints_;
		HitPoints effectiveHitPoints_;
		float shieldRecharge_;
		
		enum {
			UNKNOWN = -1,
			ALLOWED,
			DISALLOWED
		} disallowAssistance_, disallowOffensiveModifiers_;
		
		void updateModulesState();
		void updateEnabledStatus();

	};
}