#pragma once
#include "types.h"

namespace eufe {
	
	class EffectInterpreter
	{
	public:
		virtual ~EffectInterpreter() {};
		virtual bool addEffect(const Environment& environment) = 0;
		virtual bool removeEffect(const Environment& environment) = 0;
	};
	
}