%include "DamagePattern.i"

namespace dgmpp {
	
	%nodefaultctor Ship;
	
	class Ship : public dgmpp::Item
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
		
		dgmpp::Module* addModule(dgmpp::TypeID typeID);
		void removeModule(dgmpp::Module* module);
		dgmpp::Drone* addDrone(dgmpp::TypeID typeID);
		void removeDrone(dgmpp::Drone* drone);
		
		%extend {
			std::vector<dgmpp::Module*> getModules() {
				const dgmpp::ModulesList& modules = $self->getModules();
				return std::vector<dgmpp::Module*>(modules.begin(), modules.end());
			}

			std::vector<dgmpp::Drone*> getDrones() {
				const dgmpp::DronesList& drones = $self->getDrones();
				return std::vector<dgmpp::Drone*>(drones.begin(), drones.end());
			}

			std::vector<dgmpp::Module*> getProjectedModules() {
				const dgmpp::ModulesList& modules = $self->getProjectedModules();
				return std::vector<dgmpp::Module*>(modules.begin(), modules.end());
			}
			
			std::vector<dgmpp::Drone*> getProjectedDrones() {
				const dgmpp::DronesList& drones = $self->getProjectedDrones();
				return std::vector<dgmpp::Drone*>(drones.begin(), drones.end());
			}
		}

		bool canFit(dgmpp::Module* module);
		bool isDisallowedAssistance();
		bool isDisallowedOffensiveModifiers();
		
		void addProjectedModule(dgmpp::Module* module);
		void removeProjectedModule(dgmpp::Module* module);
		void addProjectedDrone(dgmpp::Drone* drone);
		void removeProjectedDrone(dgmpp::Drone* drone);
		
		const dgmpp::DamagePattern& getDamagePattern();
		void setDamagePattern(const dgmpp::DamagePattern& damagePattern);
		
		//Calculations
		
		int getNumberOfSlots(dgmpp::Module::Slot slot);
		int getFreeSlots(dgmpp::Module::Slot slot);
		int getUsedSlots(dgmpp::Module::Slot slot);
		int getNumberOfHardpoints(dgmpp::Module::Hardpoint hardpoint);
		int getFreeHardpoints(dgmpp::Module::Hardpoint hardpoint);
		int getUsedHardpoints(dgmpp::Module::Hardpoint hardpoint);
		
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
		const dgmpp::Resistances& getResistances();
		const dgmpp::Tank& getTank();
		const dgmpp::Tank& getEffectiveTank();
		const dgmpp::Tank& getSustainableTank();
		const dgmpp::Tank& getEffectiveSustainableTank();
		
		const dgmpp::HitPoints& getHitPoints();
		const dgmpp::HitPoints& getEffectiveHitPoints();
		
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
		dgmpp::Ship::ScanType getScanType();
		float getProbeSize();
		float getScanResolution();
		
		//Drones
		int getMaxActiveDrones();
		int getActiveDrones();
		
	};
}