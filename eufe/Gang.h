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
		
		virtual Environment buildEnvironment();
		
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
		
		virtual void addLocationModifier(std::shared_ptr<Modifier> const& modifier);
		virtual void addLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier);
		virtual void addLocationRequiredSkillModifier(std::shared_ptr<LocationRequiredSkillModifier> const& modifier);
		
		virtual void removeLocationModifier(std::shared_ptr<Modifier> const& modifier);
		virtual void removeLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier);
		virtual void removeLocationRequiredSkillModifier(std::shared_ptr<LocationRequiredSkillModifier> const& modifier);

		
	protected:

		virtual std::insert_iterator<ModifiersList> getLocationModifiers(std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(Item* item, std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator);
		
	private:
		CharactersList pilots_;
		std::shared_ptr<Character> fleetBooster_;
		std::shared_ptr<Character> wingBooster_;
		std::shared_ptr<Character> squadBooster_;
		
		typedef std::map<AttributeID, std::map<int64_t, std::map<Character*, std::shared_ptr<Modifier>>>> LocationModifiers;
		typedef std::map<SkillID, LocationModifiers> LocationRequiredSkillModifiers;
		typedef std::map<GroupID, LocationModifiers> LocationGroupModifiers;
		
		LocationModifiers locationModifiers_;
		LocationGroupModifiers locationGroupModifiers_;
		LocationRequiredSkillModifiers locationRequiredSkillModifiers_;

	};

}