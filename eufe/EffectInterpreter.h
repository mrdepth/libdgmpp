#pragma once
#include "types.h"

namespace eufe {
	
	class EffectInterpreter
	{
	public:
		virtual bool addEffect(Environment* environment) = 0;
		virtual bool removeEffect(Environment* environment) = 0;
		virtual EffectInterpreter* clone() const = 0;
	};
	
}