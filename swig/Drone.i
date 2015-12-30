
namespace dgmpp {
	
	%nodefaultctor Drone;

	class Drone : public dgmpp::Item
	{
	public:
		void setTarget(dgmpp::Ship* target = NULL);
		void clearTarget();
		dgmpp::Ship* getTarget();
		
		bool dealsDamage();
		dgmpp::Charge* getCharge();
		
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