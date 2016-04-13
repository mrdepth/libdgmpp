%include "Module.i"

%shared_ptr(dgmpp::StarbaseStructure);

namespace dgmpp {

	%nodefaultctor StarbaseStructure;

	class StarbaseStructure : public dgmpp::Module
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