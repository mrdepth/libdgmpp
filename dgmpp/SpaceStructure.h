#pragma once
#include "Ship.h"

namespace dgmpp {
	
	class SpaceStructure : public Ship
	{
	public:
		SpaceStructure(std::shared_ptr<Engine> const& engine, TypeID typeID);
		virtual ~SpaceStructure(void);
	};
}
