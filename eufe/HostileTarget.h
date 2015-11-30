#pragma once
#include "types.h"

namespace eufe {
	
	class HostileTarget
	{
	public:
		HostileTarget(float range = 0, float angularVelocity = 0, float signature = 0, float velocity = 0);
		float angularVelocity;
		float velocity;
		float signature;
		float range;
		const static HostileTarget defaultTarget;
	};
}