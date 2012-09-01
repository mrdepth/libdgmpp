
namespace eufe {
	
	%nodefaultctor Drone;

	class Drone : public Item
	{
	public:
		void setTarget(Ship* target = NULL);
		void clearTarget();
		Ship* getTarget();
		
		bool dealsDamage();
		Charge* getCharge();
		
		void setActive(bool active);
		bool isActive();
		
		//Calculations
		
		float getCycleTime();
		
		float getVolley();
		float getDps();
		float getMaxRange();
		float getFalloff();
		float getTrackingSpeed();
	};
	
}