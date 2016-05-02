#pragma once
#include "types.h"
#include "Item.h"

namespace dgmpp {
	
	class Character : public Item
	{
	public:
		Character(std::shared_ptr<Engine> const& engine, std::shared_ptr<Gang> const& owner = std::shared_ptr<Gang>(nullptr), const char* characterName = "");
		virtual ~Character(void);
		std::shared_ptr<Character> shared_from_this() {
			return std::static_pointer_cast<Character>(Item::shared_from_this());
		}
		
		std::shared_ptr<Ship> getShip();
		std::shared_ptr<Ship> setShip(TypeID typeID);

		std::shared_ptr<SpaceStructure> setSpaceStructure(TypeID typeID);
		std::shared_ptr<SpaceStructure> getSpaceStructure();

		virtual void reset();
		
		std::shared_ptr<Skill> getSkill(TypeID typeID);
		
		bool emptyImplantSlot(int slot);
		bool emptyBoosterSlot(int slot);
		std::shared_ptr<Implant> getImplant(int slot);
		std::shared_ptr<Booster> getBooster(int slot);
		std::shared_ptr<Implant> addImplant(TypeID typeID, bool forced = false);
		std::shared_ptr<Booster> addBooster(TypeID typeID, bool forced = false);
		void removeImplant(std::shared_ptr<Implant> const& implant);
		void removeBooster(std::shared_ptr<Booster> const& booster);
		const ImplantsList& getImplants();
		const BoostersList& getBoosters();
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		void setCharacterName(const char* characterName = "");
		const char* getCharacterName();
		
		void setSkillLevels(const std::map<TypeID, int>& levels);
		void setAllSkillsLevel(int level);

		float getDroneControlRange();

		virtual Item* character();
		virtual Item* ship();
		virtual Item* structure();

		friend std::ostream& operator<<(std::ostream& os, Character& character);
	protected:
		friend class Gang;

		virtual std::insert_iterator<ModifiersList> getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual void lazyLoad();

	private:
		std::shared_ptr<Ship> ship_;
		std::shared_ptr<SpaceStructure> spaceStructure_;
		SkillsMap skills_;
		ImplantsList implants_;
		BoostersList boosters_;
		std::string characterName_;

		std::shared_ptr<Skill> addSkill(TypeID typeID, int skillLevel, bool isLearned);
		void removeSkill(std::shared_ptr<Skill> const& skill);
	};
}