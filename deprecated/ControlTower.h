#pragma once
#include "Item.h"
#include "Module.h"
#include "DamagePattern.h"

namespace dgmpp {
	
	class ControlTower : public Item
	{
	public:
		
		ControlTower(std::shared_ptr<Engine> const& engine, TypeID typeID);
		virtual ~ControlTower(void);
		std::shared_ptr<ControlTower> shared_from_this() {
			return std::static_pointer_cast<ControlTower>(Item::shared_from_this());
		}

		std::shared_ptr<StarbaseStructure> addStructure(TypeID typeID);
		void removeStructure(std::shared_ptr<StarbaseStructure> const& structure);
		
		const StarbaseStructuresList& getStructures();
		bool canFit(std::shared_ptr<StarbaseStructure> const& structure);

		virtual void reset();
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		const DamagePattern& getDamagePattern();
		void setDamagePattern(const DamagePattern& damagePattern);
		
		//Calculations
		
		Float getPowerGridUsed();
		Float getTotalPowerGrid();
		Float getCpuUsed();
		Float getTotalCpu();
		
		//Tank
		const Resistances& getResistances();
		const Tank& getTank();
		const Tank& getEffectiveTank();
		
		const HitPoints& getHitPoints();
		const HitPoints& getEffectiveHitPoints();
		
		Float getShieldRecharge();
		
		//DPS
		DamageVector getWeaponDps();
		DamageVector getWeaponVolley();
		
		virtual Item* ship();
		friend std::ostream& operator<<(std::ostream& os, ControlTower& controlTower);
		
	private:
		StarbaseStructuresList structures_;
		DamagePattern damagePattern_;
		
		Resistances resistances_;
		Tank tank_;
		Tank effectiveTank_;
		HitPoints hitPoints_;
		HitPoints effectiveHitPoints_;
		Float shieldRecharge_;
		
		DamageVector weaponDps_;
		DamageVector weaponVolley_;
		
		Float cpuUsed_;
		Float powerGridUsed_;
		
		void calculateDamageStats();
	};
}
