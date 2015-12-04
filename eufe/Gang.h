#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {

	class Gang : public Item
	{
	public:
		Gang(std::shared_ptr<Engine> const& engine);
		virtual ~Gang(void);
		std::shared_ptr<Gang> shared_from_this() {
			return std::static_pointer_cast<Gang>(Item::shared_from_this());
		}

		const CharactersList& getPilots();
		std::shared_ptr<Character> addPilot();
		void removePilot(std::shared_ptr<Character> const& character);
		
		virtual Environment getEnvironment();
		
		virtual void reset();
		
		std::shared_ptr<Character> getFleetBooster();
		std::shared_ptr<Character> getWingBooster();
		std::shared_ptr<Character> getSquadBooster();
		void setFleetBooster(std::shared_ptr<Character> const& fleetBooster);
		void setWingBooster(std::shared_ptr<Character> const& wingBooster);
		void setSquadBooster(std::shared_ptr<Character> const& squadBooster);
		void removeFleetBooster();
		void removeWingBooster();
		void removeSquadBooster();

		friend std::ostream& operator<<(std::ostream& os, Gang& gang);
		
	protected:

		virtual std::insert_iterator<ModifiersList> getLocationModifiers(std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(std::shared_ptr<Item> const& item, std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator);
		
	private:
		CharactersList pilots_;
		std::shared_ptr<Character> fleetBooster_;
		std::shared_ptr<Character> wingBooster_;
		std::shared_ptr<Character> squadBooster_;
	};

}