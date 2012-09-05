%include "DamagePattern.i"

namespace eufe {
	
	%nodefaultctor Ship;
	
	class Ship : public eufe::Item
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
		
		eufe::Module* addModule(eufe::TypeID typeID);
		void removeModule(eufe::Module* module);
		eufe::Drone* addDrone(eufe::TypeID typeID);
		void removeDrone(eufe::Drone* drone);
		
		%extend {
			std::vector<eufe::Module*> getModules() {
				const eufe::ModulesList& modules = $self->getModules();
				return std::vector<eufe::Module*>(modules.begin(), modules.end());
			}

			std::vector<eufe::Drone*> getDrones() {
				const eufe::DronesList& drones = $self->getDrones();
				return std::vector<eufe::Drone*>(drones.begin(), drones.end());
			}

			std::vector<eufe::Module*> getProjectedModules() {
				const eufe::ModulesList& modules = $self->getProjectedModules();
				return std::vector<eufe::Module*>(modules.begin(), modules.end());
			}
			
			std::vector<eufe::Drone*> getProjectedDrones() {
				const eufe::DronesList& drones = $self->getProjectedDrones();
				return std::vector<eufe::Drone*>(drones.begin(), drones.end());
			}
		}

		bool canFit(eufe::Module* module);
		bool isDisallowedAssistance();
		bool isDisallowedOffensiveModifiers();
		
		void addProjectedModule(eufe::Module* module);
		void removeProjectedModule(eufe::Module* module);
		void addProjectedDrone(eufe::Drone* drone);
		void removeProjectedDrone(eufe::Drone* drone);
		
		const eufe::DamagePattern& getDamagePattern();
		void setDamagePattern(const eufe::DamagePattern& damagePattern);
		
		//Calculations
		
		int getNumberOfSlots(eufe::Module::Slot slot);
		int getFreeSlots(eufe::Module::Slot slot);
		int getUsedSlots(eufe::Module::Slot slot);
		int getNumberOfHardpoints(eufe::Module::Hardpoint hardpoint);
		int getFreeHardpoints(eufe::Module::Hardpoint hardpoint);
		int getUsedHardpoints(eufe::Module::Hardpoint hardpoint);
		
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
		const eufe::Resistances& getResistances();
		const eufe::Tank& getTank();
		const eufe::Tank& getEffectiveTank();
		const eufe::Tank& getSustainableTank();
		const eufe::Tank& getEffectiveSustainableTank();
		
		const eufe::HitPoints& getHitPoints();
		const eufe::HitPoints& getEffectiveHitPoints();
		
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
		eufe::Ship::ScanType getScanType();
		float getProbeSize();
		float getScanResolution();
		
		//Drones
		int getMaxActiveDrones();
		int getActiveDrones();
		
	};
}