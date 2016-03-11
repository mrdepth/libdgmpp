#pragma once
#include "Item.h"
#include "HostileTarget.h"
#include "DamageVector.h"

namespace dgmpp {
	
	class Module : public Item
	{
	public:
		enum Slot
		{
			SLOT_UNKNOWN = -1,
			SLOT_NONE = 0,
			SLOT_HI,
			SLOT_MED,
			SLOT_LOW,
			SLOT_RIG,
			SLOT_SUBSYSTEM,
			SLOT_STRUCTURE,
			SLOT_MODE,
			SLOT_SERVICE
		};

		enum State
		{
			STATE_UNKNOWN = -1,
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
		Module(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner = std::shared_ptr<Item>(nullptr));
		virtual ~Module(void);
		std::shared_ptr<Module> shared_from_this() {
			return std::static_pointer_cast<Module>(Item::shared_from_this());
		}

        typedef std::invalid_argument BadTargetException;
        typedef std::invalid_argument BadStateException;

		//virtual Attribute* getAttribute(TypeID attributeID);

		Slot getSlot();
		Hardpoint getHardpoint();
		virtual bool canHaveState(State state);
		State getState();
		State getPreferredState();
		void setPreferredState(State state);
		bool canBeOnline() {return canBeOnline_;};
		bool canBeActive() {return canBeActive_;};
		bool canBeOverloaded() {return canBeOverloaded_;};
		bool isAssistance();
		bool isOffensive();

		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		virtual void reset();
		
		std::shared_ptr<Charge> setCharge(TypeID typeID);
		void clearCharge();
		std::shared_ptr<Charge> getCharge();
		const std::vector<TypeID>& getChargeGroups();
		int getChargeSize();
		bool canFit(std::shared_ptr<Charge> const& charge);
		bool requireTarget();
		void setTarget(std::shared_ptr<Ship> const& target = std::shared_ptr<Ship>(nullptr));
		void clearTarget();
		std::shared_ptr<Ship> getTarget();
		float getReloadTime();
		
		//Calculations
		
		float getCycleTime();
		float getRawCycleTime();
		bool factorReload();
		void setFactorReload(bool factorReload);
		
		int getCharges();
		int getShots();
		float getCapUse();
		
		DamageVector getVolley();
		DamageVector getDps(const HostileTarget& target = HostileTarget::defaultTarget);
		//float getDps(float range, float angularSpeed, float targetSignature);
		float getMaxRange();
		float getFalloff();
		float getTrackingSpeed();
		
		float getLifeTime();
		void setLifeTime(float lifeTime);
		
		void setEnabled(bool enabled);
		bool isEnabled();

		virtual Item* ship();
		virtual Item* character();
		virtual Item* target();

		friend std::ostream& operator<<(std::ostream& os, Module& module);
	protected:
		State state_;
		State preferredState_;
		virtual void lazyLoad();

		friend class Ship;
		virtual void setState(State state);

		
	private:
		bool canBeOnline_;
		bool canBeActive_;
		bool canBeOverloaded_;
		bool forceReload_;
		bool factorReload_;
		bool enabled_;
		Slot slot_;
		Hardpoint hardpoint_;
		std::shared_ptr<Charge> charge_;
		std::vector<TypeID> chargeGroups_;
		std::weak_ptr<Ship> target_;
		float reloadTime_;
		int shots_;
		
		DamageVector volley_;
		DamageVector dps_;
		float maxRange_;
		float falloff_;
		float trackingSpeed_;
		
		float lifeTime_;
		
		void calculateDamageStats();
	};
}