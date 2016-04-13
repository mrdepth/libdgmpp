#pragma once
#include "Ship.h"
#include "Fighter.h"

namespace dgmpp {
	
	class SpaceStructure : public Ship
	{
	public:
		SpaceStructure(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner = std::shared_ptr<Character>(nullptr));
		virtual ~SpaceStructure(void);

		std::shared_ptr<SpaceStructure> shared_from_this() {
			return std::static_pointer_cast<SpaceStructure>(Item::shared_from_this());
		}
		virtual std::vector<TypeID> getSupportedModuleCategories() const;
		virtual std::vector<TypeID> getSupportedDroneCategories() const;
		
		virtual float getTotalDroneBay();
		TypeID getFuelBlockTypeID();
		/*int getDroneSquadronLimit(Fighter::Squadron squadron);
		int getDroneSquadronUsed(Fighter::Squadron squadron);
		int getTotalDroneLaunchTubes();
		int getUsedDroneLaunchTubes();*/
	};
}
