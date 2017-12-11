#pragma once
#include "types.h"
#include "Item.h"
#include "GangBoost.h"
#include "Type.hpp"

namespace dgmpp {

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
		
		virtual void reset();
		
		void addGangBoost(std::shared_ptr<GangBoost> boost);
		void removeGangBoost(std::shared_ptr<GangBoost> boost);

		friend std::ostream& operator<<(std::ostream& os, Gang& gang);
		
	protected:

		virtual std::insert_iterator<ModifiersList> getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		
	private:
		CharactersList pilots_;
		std::list<std::shared_ptr<GangBoost>> boosts_;
		std::shared_ptr<ItemModifiers> boostModifiers_;
		
		const ItemModifiers& getBoostModifiers();

	};

}

