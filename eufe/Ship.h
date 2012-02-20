#pragma once
#include "Item.h"
#include "Module.h"
#include "CapacitorSimulator.h"
#include "DamagePattern.h"

namespace eufe {

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
		
		Ship(Engine* engine, TypeID typeID, Character* owner = NULL);
		virtual ~Ship(void);

		boost::shared_ptr<Module> addModule(const boost::shared_ptr<Module>& module);
		boost::shared_ptr<Module> addModule(TypeID typeID);
		void removeModule(const boost::shared_ptr<Module>& module);
		
		boost::shared_ptr<Drone> addDrone(const boost::shared_ptr<Drone>& drone);
		boost::shared_ptr<Drone> addDrone(TypeID typeID);
		void removeDrone(const boost::shared_ptr<Drone>& drone);
		
		const ModulesList& getModules();
		void getModules(Module::Slot slot, std::insert_iterator<ModulesList> outIterator);
		const DronesList& getDrones();
		const ProjectedModulesList& getProjectedModules();
		const ProjectedDronesList& getProjectedDrones();
		bool canFit(const boost::shared_ptr<Module>& module);
		bool isDisallowedAssistance();
		bool isDisallowedOffensiveModifiers();

		virtual boost::shared_ptr<Environment> getEnvironment();
		
		virtual void reset();
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		virtual void addLocationGroupModifier(boost::shared_ptr<Modifier> modifier);
		virtual void addLocationRequiredSkillModifier(boost::shared_ptr<Modifier> modifier);

		
		void addProjectedModule(Module* module);
		void removeProjectedModule(Module* module);
		void addProjectedDrone(Drone* drone);
		void removeProjectedDrone(Drone* drone);
		
		const CapacitorSimulator& getCapacitorSimulator();
		const DamagePattern& getDamagePattern();
		void setDamagePattern(const DamagePattern& damagePattern);
		
		//Calculations
		
		int getNumberOfSlots(Module::Slot slot);
		int getFreeSlots(Module::Slot slot);
		int getUsedSlots(Module::Slot slot);
		int getNumberOfHardpoints(Module::Hardpoint hardpoint);
		int getFreeHardpoints(Module::Hardpoint hardpoint);
		int getUsedHardpoints(Module::Hardpoint hardpoint);
		
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
		float getWeaponDps();
		float getWeaponVolley();
		float getDroneDps();
		float getDroneVolley();
		
		//Mobility
		float getAlignTime();
		float getWarpSpeed();
		float getMaxWarpDistance();
		float getVelocity();
		float getSignatureRadius();
		
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

		
#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Ship& ship);
#endif

	private:
		ModulesList modules_;
		DronesList drones_;
		ProjectedModulesList projectedModules_;
		ProjectedDronesList projectedDrones_;
		CapacitorSimulator capacitorSimulator_;
		DamagePattern damagePattern_;
		
		Resistances resistances_;
		Tank tank_;
		Tank effectiveTank_;
		Tank sustainableTank_;
		Tank effectiveSustainableTank_;
		HitPoints hitPoints_;
		HitPoints effectiveHitPoints_;
		float shieldRecharge_;
		
		float weaponDps_;
		float weaponVolley_;
		float droneDps_;
		float droneVolley_;
		
		enum {
			UNKNOWN = -1,
			ALLOWED,
			DISALLOWED
		} disallowAssistance_, disallowOffensiveModifiers_;
		
		void calculateDamageStats();
		void updateActiveStatus();
	};
}