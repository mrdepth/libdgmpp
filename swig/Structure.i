%include "Item.i"

%shared_ptr(dgmpp::Structure);

namespace dgmpp {

	%nodefaultctor Structure;

	class Structure : public dgmpp::Module
	{
	public:
		const dgmpp::Resistances& getResistances();
		const dgmpp::Tank& getTank();
		const dgmpp::Tank& getEffectiveTank();
		
		const dgmpp::HitPoints& getHitPoints();
		const dgmpp::HitPoints& getEffectiveHitPoints();
		
		float getShieldRecharge();
	};
}