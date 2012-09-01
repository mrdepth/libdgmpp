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
			SLOT_STRUCTURE
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

		typedef boost::error_info<struct BadStateExceptionInfoTag, State> BadStateExceptionInfo;
		struct BadStateException : virtual boost::exception {};
		typedef boost::error_info<struct BadTargetExceptionInfoTag, Ship*> BadTargetExceptionInfo;
		struct BadTargetException : virtual boost::exception {};

		Module(Engine* engine, TypeID typeID, Item* owner = NULL);
		Module(const Module& from);
		virtual ~Module(void);

		virtual Attribute* getAttribute(TypeID attributeID);

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
		const std::list<TypeID>& getChargeGroups();
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
		

#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Module& module);
#endif
	protected:
		State state_;
		
	private:
		bool canBeOnline_;
		bool canBeActive_;
		bool canBeOverloaded_;
		bool requireTarget_;
		bool forceReload_;
		Slot slot_;
		Hardpoint hardpoint_;
		Charge* charge_;
		std::list<TypeID> chargeGroups_;
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