
namespace eufe {
	
	%nodefaultctor Structure;

	class Structure : public eufe::Module
	{
	public:
		const eufe::Resistances& getResistances();
		const eufe::Tank& getTank();
		const eufe::Tank& getEffectiveTank();
		
		const eufe::HitPoints& getHitPoints();
		const eufe::HitPoints& getEffectiveHitPoints();
		
		float getShieldRecharge();
	};
}