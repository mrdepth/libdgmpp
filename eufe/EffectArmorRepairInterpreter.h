#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectArmorRepairInterpreter : public EffectInterpreter
	{
	public:
		EffectArmorRepairInterpreter(std::shared_ptr<Engine> const& engine, bool isProjected, bool isAssistance, bool isOffensive);
		virtual ~EffectArmorRepairInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
		bool isProjected_;
	};
	
}