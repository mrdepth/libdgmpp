#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectSlotModifierInterpreter : public EffectInterpreter
	{
	public:
		EffectSlotModifierInterpreter(std::shared_ptr<Engine> engine, bool isAssistance, bool isOffensive);
		virtual ~EffectSlotModifierInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}