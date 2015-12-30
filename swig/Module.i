%include "Item.i"

namespace dgmpp {
	
	%nodefaultctor Module;

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
		
		virtual dgmpp::Attribute* getAttribute(dgmpp::TypeID attributeID);
		
		Slot getSlot();
		Hardpoint getHardpoint();
		virtual bool canHaveState(State state);
		State getState();
		virtual void setState(State state);
		
		dgmpp::Charge* setCharge(dgmpp::TypeID typeID);
		void clearCharge();
		dgmpp::Charge* getCharge();
		const std::vector<dgmpp::TypeID>& getChargeGroups();
		int getChargeSize();
		void removeCharge();
		bool canFit(dgmpp::Charge* charge);
		bool requireTarget();
		void setTarget(dgmpp::Ship* target = NULL);
		void clearTarget();
		dgmpp::Ship* getTarget();
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
	};
}