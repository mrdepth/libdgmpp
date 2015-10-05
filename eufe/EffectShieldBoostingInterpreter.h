#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectShieldBoostingInterpreter : public EffectInterpreter
	{
	public:
		EffectShieldBoostingInterpreter(std::shared_ptr<Engine> engine, bool isProjected, bool isAssistance, bool isOffensive);
		virtual ~EffectShieldBoostingInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
		bool isProjected_;
	};
	
}