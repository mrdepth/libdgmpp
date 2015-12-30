
namespace dgmpp {
	
	class DamagePattern
	{
	public:
		DamagePattern();
		DamagePattern(float em, float thermal, float kinetic, float explosive);
		~DamagePattern(void);
		
		float emAmount;
		float thermalAmount;
		float kineticAmount;
		float explosiveAmount;
	};
}