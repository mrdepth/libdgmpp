
namespace dgmpp {
	
	%nodefaultctor ControlTower;
	
	class ControlTower : public dgmpp::Item
	{
	public:
		dgmpp::Structure* addStructure(dgmpp::TypeID typeID);
		void removeStructure(dgmpp::Structure* structure);
		
		%extend {
			std::vector<dgmpp::Structure*> getStructures() {
				const dgmpp::StructuresList& structures = $self->getStructures();
				return std::vector<dgmpp::Structure*>(structures.begin(), structures.end());
			}
		}
		bool canFit(dgmpp::Structure* structure);
		
		const dgmpp::DamagePattern& getDamagePattern();
		void setDamagePattern(const dgmpp::DamagePattern& damagePattern);
		
		//Calculations
		
		float getPowerGridUsed();
		float getTotalPowerGrid();
		float getCpuUsed();
		float getTotalCpu();
		
		//Tank
		const dgmpp::Resistances& getResistances();
		const dgmpp::Tank& getTank();
		const dgmpp::Tank& getEffectiveTank();
		
		const dgmpp::HitPoints& getHitPoints();
		const dgmpp::HitPoints& getEffectiveHitPoints();
		
		float getShieldRecharge();
		
		//DPS
		float getWeaponDps();
		float getWeaponVolley();
	};
}