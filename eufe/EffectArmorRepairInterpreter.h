#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectArmorRepairInterpreter : public EffectInterpreter
	{
	public:
		EffectArmorRepairInterpreter(Engine* engine, bool isProjected, bool isAssistance, bool isOffensive);
		virtual ~EffectArmorRepairInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
		virtual EffectInterpreter* clone() const;
	private:
		Engine* engine_;
		bool isAssistance_;
		bool isOffensive_;
		bool isProjected_;
	};
	
}