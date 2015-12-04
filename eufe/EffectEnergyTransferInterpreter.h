#pragma once
#include "EffectInterpreter.h"

namespace eufe {
	
	class EffectEnergyTransferInterpreter : public EffectInterpreter
	{
	public:
		EffectEnergyTransferInterpreter(std::shared_ptr<Engine> const& engine, bool isAssistance, bool isOffensive);
		virtual ~EffectEnergyTransferInterpreter();
		virtual bool addEffect(const Environment& environment);
		virtual bool removeEffect(const Environment& environment);
	private:
		std::weak_ptr<Engine> engine_;
		bool isAssistance_;
		bool isOffensive_;
	};
	
}