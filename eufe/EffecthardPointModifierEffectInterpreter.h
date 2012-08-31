#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectHardPointModifierEffectInterpreter : public EffectInterpreter
	{
	public:
		EffectHardPointModifierEffectInterpreter(Engine* engine, bool isAssistance, bool isOffensive);
		virtual ~EffectHardPointModifierEffectInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
		virtual EffectInterpreter* clone() const;
	private:
		Engine* engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}