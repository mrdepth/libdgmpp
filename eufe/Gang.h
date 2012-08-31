#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {

	class Gang : public Item
	{
	public:
		Gang(Engine* engine);
		virtual ~Gang(void);
		const CharactersList& getPilots();
		Character* addPilot();
		Character* addPilot(Character* character);
		void removePilot(Character* character);
		
		virtual Environment getEnvironment();
		
		virtual void reset();
		
		Character* getFleetBooster();
		Character* getWingBooster();
		Character* getSquadBooster();
		void setFleetBooster(Character* fleetBooster);
		void setWingBooster(Character* wingBooster);
		void setSquadBooster(Character* squadBooster);
		void removeFleetBooster();
		void removeWingBooster();
		void removeSquadBooster();

#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Gang& gang);
#endif
		
	protected:
		virtual std::insert_iterator<ModifiersList> getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		
	private:
		CharactersList pilots_;
		Character* fleetBooster_;
		Character* wingBooster_;
		Character* squadBooster_;
	};

}