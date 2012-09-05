#pragma once
#include "Item.h"
#include "Module.h"
#include "DamagePattern.h"

namespace eufe {
	
	class ControlTower : public Item
	{
	public:
		
		ControlTower(Engine* engine, TypeID typeID);
		virtual ~ControlTower(void);
		
		Structure* addStructure(Structure* structure);
		Structure* addStructure(TypeID typeID);
		void removeStructure(Structure* structure);
		
		const StructuresList& getStructures();
		bool canFit(Structure* structure);

		virtual Environment getEnvironment();
		
		virtual void reset();
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
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
		
#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, ControlTower& controlTower);
#endif
		
	private:
		StructuresList structures_;
		DamagePattern damagePattern_;
		
		Resistances resistances_;
		Tank tank_;
		Tank effectiveTank_;
		HitPoints hitPoints_;
		HitPoints effectiveHitPoints_;
		float shieldRecharge_;
		
		float weaponDps_;
		float weaponVolley_;
		
		float cpuUsed_;
		float powerGridUsed_;
		
		void calculateDamageStats();
	};
}