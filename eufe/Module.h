#pragma once
#include "Item.h"

namespace eufe {
	
	class Module : public Item
	{
	public:
		enum Slot
		{
			SLOT_NONE,
			SLOT_HI,
			SLOT_MED,
			SLOT_LOW,
			SLOT_RIG,
			SLOT_SUBSYSTEM,
			SLOT_STRUCTURE,
			SLOT_MODE
		};

		enum State
		{
			STATE_OFFLINE,
			STATE_ONLINE,
			STATE_ACTIVE,
			STATE_OVERLOADED
		};
		
		enum Hardpoint
		{
			HARDPOINT_NONE = 0,
			HARDPOINT_LAUNCHER,
			HARDPOINT_TURRET
		};

        typedef std::invalid_argument BadTargetException;
        typedef std::invalid_argument BadStateException;

		//virtual Attribute* getAttribute(TypeID attributeID);

		Slot getSlot();
		Hardpoint getHardpoint();
		virtual bool canHaveState(State state);
		State getState();
		virtual void setState(State state);

		virtual Environment getEnvironment();

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		virtual void reset();
		
		Charge* setCharge(Charge* charge);
		Charge* setCharge(TypeID typeID);
		void clearCharge();
		Charge* getCharge();
		const std::vector<TypeID>& getChargeGroups();
		int getChargeSize();
		void removeCharge();
		bool canFit(Charge* charge);
		bool requireTarget();
		void setTarget(Ship* target = NULL);
		void clearTarget();
		Ship* getTarget();
		float getReloadTime();
		
		//Calculations
		
		float getCycleTime();
		float getRawCycleTime();
		
		int getCharges();
		int getShots();
		float getCapUse();
		
		float getVolley();
		float getDps();
		float getMaxRange();
		float getFalloff();
		float getTrackingSpeed();
		
		float getLifeTime();
		void setLifeTime(float lifeTime);
		

		friend std::ostream& operator<<(std::ostream& os, Module& module);
	protected:
		State state_;
		friend class Ship;
		Module(Engine* engine, TypeID typeID, Item* owner = NULL);
		virtual ~Module(void);

		
	private:
		bool canBeOnline_;
		bool canBeActive_;
		bool canBeOverloaded_;
		bool requireTarget_;
		bool forceReload_;
		Slot slot_;
		Hardpoint hardpoint_;
		Charge* charge_;
		std::vector<TypeID> chargeGroups_;
		Ship* target_;
		float reloadTime_;
		int shots_;
		
		float volley_;
		float dps_;
		float maxRange_;
		float falloff_;
		float trackingSpeed_;
		
		float lifeTime_;
		
		void calculateDamageStats();
	};
}