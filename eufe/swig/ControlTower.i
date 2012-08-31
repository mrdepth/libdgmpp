
namespace eufe {
	
	%nodefaultctor ControlTower;
	
	class ControlTower : public Item
	{
	public:
		Structure* addStructure(TypeID typeID);
		void removeStructure(Structure* structure);
		
		const StructuresList& getStructures();
		bool canFit(Structure* structure);
		
		const DamagePattern& getDamagePattern();
		void setDamagePattern(const DamagePattern& damagePattern);
		
		//Calculations
		
		float getPowerGridUsed();
		float getTotalPowerGrid();
		float getCpuUsed();
		float getTotalCpu();
		
		//Tank
		const Resistances& getResistances();
		const Tank& getTank();
		const Tank& getEffectiveTank();
		
		const HitPoints& getHitPoints();
		const HitPoints& getEffectiveHitPoints();
		
		float getShieldRecharge();
		
		//DPS
		float getWeaponDps();
		float getWeaponVolley();
	};
}