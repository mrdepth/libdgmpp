%include "DamageVector.i"

namespace dgmpp {
	
	class DamagePattern : public dgmpp::DamageVector
	{
	public:
		DamagePattern();
		DamagePattern(const dgmpp::DamageVector& damage);
		DamagePattern(float em, float thermal, float kinetic, float explosive);
	};
}