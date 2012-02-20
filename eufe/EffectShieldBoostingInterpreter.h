#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectShieldBoostingInterpreter : public EffectInterpreter
	{
	public:
		EffectShieldBoostingInterpreter(Engine* engine, bool isProjected, bool isAssistance, bool isOffensive);
		virtual ~EffectShieldBoostingInterpreter();
		virtual bool addEffect(Environment* environment);
		virtual bool removeEffect(Environment* environment);
		virtual EffectInterpreter* clone() const;
	private:
		Engine* engine_;
		bool isAssistance_;
		bool isOffensive_;
		bool isProjected_;
	};
	
}