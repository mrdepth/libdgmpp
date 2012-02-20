#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectLeechInterpreter : public EffectInterpreter
	{
	public:
		EffectLeechInterpreter(Engine* engine, bool isAssistance, bool isOffensive);
		virtual ~EffectLeechInterpreter();
		virtual bool addEffect(Environment* environment);
		virtual bool removeEffect(Environment* environment);
		virtual EffectInterpreter* clone() const;
	private:
		Engine* engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}