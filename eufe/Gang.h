#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {

	class Gang : public Item
	{
	public:
		const CharactersList& getPilots();
		Character* addPilot();
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

		friend std::ostream& operator<<(std::ostream& os, Gang& gang);
		
	protected:
		friend class Engine;
		Gang(Engine* engine);
		virtual ~Gang(void);

		virtual std::insert_iterator<ModifiersList> getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		
	private:
		CharactersList pilots_;
		Character* fleetBooster_;
		Character* wingBooster_;
		Character* squadBooster_;
	};

}