#pragma once
#include "Item.h"
#include "Module.h"
#include "DamagePattern.h"

namespace eufe {
	
	class ControlTower : public Item
	{
	public:
		
		ControlTower(std::shared_ptr<Engine> engine, TypeID typeID);
		virtual ~ControlTower(void);
		std::shared_ptr<ControlTower> shared_from_this() {
			return std::static_pointer_cast<ControlTower>(Item::shared_from_this());
		}

		std::shared_ptr<Structure> addStructure(TypeID typeID);
		void removeStructure(std::shared_ptr<Structure> structure);
		
		const StructuresList& getStructures();
		bool canFit(std::shared_ptr<Structure> structure);

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
		DamageVector getWeaponDps();
		DamageVector getWeaponVolley();
		
		friend std::ostream& operator<<(std::ostream& os, ControlTower& controlTower);
		
	private:
		StructuresList structures_;
		DamagePattern damagePattern_;
		
		Resistances resistances_;
		Tank tank_;
		Tank effectiveTank_;
		HitPoints hitPoints_;
		HitPoints effectiveHitPoints_;
		float shieldRecharge_;
		
		DamageVector weaponDps_;
		DamageVector weaponVolley_;
		
		float cpuUsed_;
		float powerGridUsed_;
		
		void calculateDamageStats();
	};
}