%include "Item.i"
%include "Charge.i"

%shared_ptr(dgmpp::Module);
%shared_ptr(dgmpp::Ship);

namespace dgmpp {

	%nodefaultctor Module;

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
			SLOT_MODE
			
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
		
		Slot getSlot();
		Hardpoint getHardpoint();
		virtual bool canHaveState(State state);
		State getState();
		State getPreferredState();
		%extend {
			void setState(State state) {
				$self->setPreferredState(state);
			}
		}
		
		std::shared_ptr<dgmpp::Charge> setCharge(dgmpp::TypeID typeID);
		void clearCharge();
		std::shared_ptr<dgmpp::Charge> getCharge();
		const std::vector<dgmpp::TypeID>& getChargeGroups();
		int getChargeSize();
		
		bool requireTarget();
		void setTarget(const std::shared_ptr<dgmpp::Ship>& target = NULL);
		void clearTarget();
		std::shared_ptr<dgmpp::Ship> getTarget();
		float getReloadTime();
		
		//Calculations
		
		float getCycleTime();
		float getRawCycleTime();
		bool factorReload();
		void setFactorReload(bool factorReload);

		int getCharges();
		int getShots();
		float getCapUse();
		
		dgmpp::DamageVector getVolley();
		dgmpp::DamageVector getDps();
		float getMaxRange();
		float getFalloff();
		float getTrackingSpeed();
		
		float getLifeTime();
		void setLifeTime(float lifeTime);
	};
}