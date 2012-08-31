#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectHullRepairInterpreter : public EffectInterpreter
	{
	public:
		EffectHullRepairInterpreter(Engine* engine, bool isProjected, bool isAssistance, bool isOffensive);
		virtual ~EffectHullRepairInterpreter();
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