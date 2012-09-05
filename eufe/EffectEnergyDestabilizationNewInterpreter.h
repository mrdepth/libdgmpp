#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectEnergyDestabilizationNewInterpreter : public EffectInterpreter
	{
	public:
		EffectEnergyDestabilizationNewInterpreter(Engine* engine, bool isAssistance, bool isOffensive);
		virtual ~EffectEnergyDestabilizationNewInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
		virtual EffectInterpreter* clone() const;
	private:
		Engine* engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}