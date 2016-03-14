#pragma once
#include "Ship.h"

namespace dgmpp {
	
	class SpaceStructure : public Ship
	{
	public:
		SpaceStructure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner = std::shared_ptr<Character>(nullptr));
		virtual ~SpaceStructure(void);
		virtual std::vector<AttributeID> getSupportedModuleCategories() const;
	};
}
