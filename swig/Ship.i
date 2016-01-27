%include "Item.i"
%include "DamagePattern.i"

%shared_ptr(dgmpp::Ship);

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
		
		std::shared_ptr<dgmpp::Module> addModule(dgmpp::TypeID typeID);
		void removeModule(std::shared_ptr<dgmpp::Module> module);
		std::shared_ptr<dgmpp::Drone> addDrone(dgmpp::TypeID typeID);
		void removeDrone(std::shared_ptr<dgmpp::Drone> drone);
		
		%extend {
			std::vector<std::shared_ptr<dgmpp::Module>> getModules() {
				const dgmpp::ModulesList& modules = $self->getModules();
				return std::vector<std::shared_ptr<dgmpp::Module>>(modules.begin(), modules.end());
			}

			std::vector<std::shared_ptr<dgmpp::Drone>> getDrones() {
				const dgmpp::DronesList& drones = $self->getDrones();
				return std::vector<std::shared_ptr<dgmpp::Drone>>(drones.begin(), drones.end());
			}

			std::vector<std::shared_ptr<dgmpp::Module>> getProjectedModules() {
				std::vector<std::shared_ptr<dgmpp::Module>> modules;
				for (auto module: $self->getProjectedModules())
					modules.push_back(module.lock());
				return modules;
			}
			
			std::vector<std::shared_ptr<dgmpp::Drone>> getProjectedDrones() {
				std::vector<std::shared_ptr<dgmpp::Drone>> drones;
				for (auto drone: $self->getProjectedDrones())
					drones.push_back(drone.lock());
				return drones;
			}
		}

		bool isDisallowedAssistance();
		bool isDisallowedOffensiveModifiers();
		
		void addProjectedModule(std::shared_ptr<dgmpp::Module> module);
		void removeProjectedModule(std::shared_ptr<dgmpp::Module> module);
		void addProjectedDrone(std::shared_ptr<dgmpp::Drone> drone);
		void removeProjectedDrone(std::shared_ptr<dgmpp::Drone> drone);
		
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
		dgmpp::DamageVector getWeaponDps();
		dgmpp::DamageVector getWeaponVolley();
		dgmpp::DamageVector getDroneDps();
		dgmpp::DamageVector getDroneVolley();
		
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
		dgmpp::Ship::ScanType getScanType();
		float getProbeSize();
		float getScanResolution();
		
		//Drones
		int getMaxActiveDrones();
		int getActiveDrones();
		
	};
}