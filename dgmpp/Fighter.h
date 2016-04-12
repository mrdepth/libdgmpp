#pragma once
#include "Drone.h"
#include "DamageVector.h"
#include "HostileTarget.h"

namespace dgmpp {
	
	class Fighter : public Drone
	{
	public:
		enum Squadron
		{
			SQUADRON_UNKNOWN = -1,
			SQUADRON_HEAVY = 0,
			SQUADRON_LIGHT,
			SQUADRON_SUPPORT
		};
		
		Fighter(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Ship> const& owner = std::shared_ptr<Ship>(nullptr));
		virtual bool dealsDamage();
		virtual float getCycleTime();
		Squadron getSquadron();
		int getSquadronSize();
	protected:
		virtual void calculateDamageStats();

	};
}