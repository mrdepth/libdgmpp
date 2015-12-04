#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectLeechInterpreter : public EffectInterpreter
	{
	public:
		EffectLeechInterpreter(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive);
		virtual ~EffectLeechInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}