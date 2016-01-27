%include "Item.i"

%shared_ptr(dgmpp::Drone);

namespace dgmpp {

	%nodefaultctor Drone;

	class Drone : public dgmpp::Item
	{
	public:
		void setTarget(const std::shared_ptr<dgmpp::Ship>& target = NULL);
		void clearTarget();
		std::shared_ptr<dgmpp::Ship> getTarget();
		
		bool dealsDamage();
		std::shared_ptr<dgmpp::Charge> getCharge();
		
		void setActive(bool active);
		bool isActive();
		
		//Calculations
		
		float getCycleTime();
		
		dgmpp::DamageVector getVolley();
		dgmpp::DamageVector getDps();
		float getMaxRange();
		float getFalloff();
		float getTrackingSpeed();
	};
	
}