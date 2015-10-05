#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectHardPointModifierEffectInterpreter : public EffectInterpreter
	{
	public:
		EffectHardPointModifierEffectInterpreter(std::shared_ptr<Engine> engine, bool isAssistance, bool isOffensive);
		virtual ~EffectHardPointModifierEffectInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}