#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectNaniteRepairPasteArmorDamageBonus : public EffectInterpreter
	{
	public:
		EffectNaniteRepairPasteArmorDamageBonus(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive);
		virtual ~EffectNaniteRepairPasteArmorDamageBonus();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}