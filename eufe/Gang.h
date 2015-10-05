#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {

	class Gang : public Item
	{
	public:
		const CharactersList& getPilots();
		std::shared_ptr<Character> addPilot();
		void removePilot(std::shared_ptr<Character> character);
		
		virtual Environment getEnvironment();
		
		virtual void reset();
		
		std::shared_ptr<Character> getFleetBooster();
		std::shared_ptr<Character> getWingBooster();
		std::shared_ptr<Character> getSquadBooster();
		void setFleetBooster(std::shared_ptr<Character> fleetBooster);
		void setWingBooster(std::shared_ptr<Character> wingBooster);
		void setSquadBooster(std::shared_ptr<Character> squadBooster);
		void removeFleetBooster();
		void removeWingBooster();
		void removeSquadBooster();

		friend std::ostream& operator<<(std::ostream& os, Gang& gang);
		
	protected:
		friend class Engine;
		Gang(std::shared_ptr<Engine> engine);
		virtual ~Gang(void);

		virtual std::insert_iterator<ModifiersList> getLocationModifiers(std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(Item* item, std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator);
		
	private:
		CharactersList pilots_;
		std::shared_ptr<Character> fleetBooster_;
		std::shared_ptr<Character> wingBooster_;
		std::shared_ptr<Character> squadBooster_;
	};

}