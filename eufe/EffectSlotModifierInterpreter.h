#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectSlotModifierInterpreter : public EffectInterpreter
	{
	public:
		EffectSlotModifierInterpreter(Engine* engine, bool isAssistance, bool isOffensive);
		virtual ~EffectSlotModifierInterpreter();
		virtual bool addEffect(Environment* environment);
		virtual bool removeEffect(Environment* environment);
		virtual EffectInterpreter* clone() const;
	private:
		Engine* engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}