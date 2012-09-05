
namespace eufe {
	
	%nodefaultctor Drone;

	class Drone : public eufe::Item
	{
	public:
		void setTarget(eufe::Ship* target = NULL);
		void clearTarget();
		eufe::Ship* getTarget();
		
		bool dealsDamage();
		eufe::Charge* getCharge();
		
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