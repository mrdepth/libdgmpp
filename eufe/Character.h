#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Character : public Item
	{
	public:
		Character(Engine* engine, Gang* owner = NULL, const char* characterName = "");
		virtual ~Character(void);
		Ship* getShip();
		Ship* setShip(Ship* ship);
		Ship* setShip(TypeID typeID);

		virtual Environment getEnvironment();
		
		virtual void reset();
		
		Skill* getSkill(TypeID typeID);
		
		bool emptyImplantSlot(int slot);
		bool emptyBoosterSlot(int slot);
		Implant* getImplant(int slot);
		Booster* getBooster(int slot);
		Implant* addImplant(TypeID typeID);
		Implant* addImplant(Implant* implant);
		Booster* addBooster(TypeID typeID);
		Booster* addBooster(Booster* booster);
		void removeImplant(Implant* implant);
		void removeBooster(Booster* booster);
		const ImplantsList& getImplants();
		const BoostersList& getBoosters();
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		
		void setCharacterName(const char* characterName = "");
		const char* getCharacterName();
		
		void setSkillLevels(const std::map<TypeID, int>& levels);
		void setAllSkillsLevel(int level);
		
#if _DEBUG
		friend std::ostream& operator<<(std::ostream& os, Character& character);
#endif
	protected:
		virtual std::insert_iterator<ModifiersList> getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);

	private:
		Ship* ship_;
		SkillsMap skills_;
		ImplantsList implants_;
		BoostersList boosters_;
		std::string characterName_;

		Skill* addSkill(TypeID typeID, int skillLevel, bool isLearned);
		void removeSkill(Skill* skill);
	};
}