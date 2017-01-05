#pragma once
#include "types.h"

namespace dgmpp {
	
	class HostileTarget
	{
	public:
		HostileTarget(Float range = 0, Float angularVelocity = 0, Float signature = 0, Float velocity = 0);
		Float angularVelocity;
		Float velocity;
		Float signature;
		Float range;
		const static HostileTarget defaultTarget;
	};
}
