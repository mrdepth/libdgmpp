
namespace dgmpp {
	
	class DamageVector
	{
	public:
		DamageVector(float value = 0);
		DamageVector(float em, float thermal, float kinetic, float explosive);
		union {
			struct {
				float emAmount;
				float thermalAmount;
				float kineticAmount;
				float explosiveAmount;
			};
			float damageTypes[4];
		};
	};
}