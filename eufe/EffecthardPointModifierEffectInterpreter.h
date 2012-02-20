#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffecthardPointModifierEffectInterpreter : public EffectInterpreter
	{
	public:
		EffecthardPointModifierEffectInterpreter(Engine* engine, bool isAssistance, bool isOffensive);
		virtual ~EffecthardPointModifierEffectInterpreter();
		virtual bool addEffect(Environment* environment);
		virtual bool removeEffect(Environment* environment);
		virtual EffectInterpreter* clone() const;
	private:
		Engine* engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}