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
		boost::shared_ptr<Character> addPilot();
		boost::shared_ptr<Character> addPilot(const boost::shared_ptr<Character>& character);
		void removePilot(const boost::shared_ptr<Character>& character);
		
		virtual boost::shared_ptr<Environment> getEnvironment();
		
		virtual void reset();
		
		boost::shared_ptr<Character> getFleetBooster();
		boost::shared_ptr<Character> getWingBooster();
		boost::shared_ptr<Character> getSquadBooster();
		void setFleetBooster(const boost::shared_ptr<Character>& fleetBooster);
		void setWingBooster(const boost::shared_ptr<Character>& wingBooster);
		void setSquadBooster(const boost::shared_ptr<Character>& squadBooster);
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
		boost::shared_ptr<Character> fleetBooster_;
		boost::shared_ptr<Character> wingBooster_;
		boost::shared_ptr<Character> squadBooster_;
	};

}