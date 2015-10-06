#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Character : public Item
	{
	public:
		Character(std::shared_ptr<Engine> engine, std::shared_ptr<Gang> owner = nullptr, const char* characterName = "");
		virtual ~Character(void);
		std::shared_ptr<Character> shared_from_this() {
			return std::static_pointer_cast<Character>(Item::shared_from_this());
		}
		
		std::shared_ptr<Ship> getShip();
		std::shared_ptr<Ship> setShip(TypeID typeID);

		virtual Environment getEnvironment();
		
		virtual void reset();
		
		std::shared_ptr<Skill> getSkill(TypeID typeID);
		
		bool emptyImplantSlot(int slot);
		bool emptyBoosterSlot(int slot);
		std::shared_ptr<Implant> getImplant(int slot);
		std::shared_ptr<Booster> getBooster(int slot);
		std::shared_ptr<Implant> addImplant(TypeID typeID);
		std::shared_ptr<Booster> addBooster(TypeID typeID);
		void removeImplant(std::shared_ptr<Implant> implant);
		void removeBooster(std::shared_ptr<Booster> booster);
		const ImplantsList& getImplants();
		const BoostersList& getBoosters();
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		void setCharacterName(const char* characterName = "");
		const char* getCharacterName();
		
		void setSkillLevels(const std::map<TypeID, int>& levels);
		void setAllSkillsLevel(int level);
		
		friend std::ostream& operator<<(std::ostream& os, Character& character);
	protected:
		friend class Gang;

		virtual std::insert_iterator<ModifiersList> getLocationModifiers(std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual void lazyLoad();

	private:
		std::shared_ptr<Ship> ship_;
		SkillsMap skills_;
		ImplantsList implants_;
		BoostersList boosters_;
		std::string characterName_;

		std::shared_ptr<Skill> addSkill(TypeID typeID, int skillLevel, bool isLearned);
		void removeSkill(std::shared_ptr<Skill> skill);
	};
}