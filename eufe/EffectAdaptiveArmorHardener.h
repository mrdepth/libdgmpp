#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectAdaptiveArmorHardener : public EffectInterpreter
	{
	public:
		EffectAdaptiveArmorHardener(std::shared_ptr<Engine> engine, bool isAssistance, bool isOffensive);
		virtual ~EffectAdaptiveArmorHardener();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}