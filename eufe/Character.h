#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Character : public Item
	{
	public:
		Character(Engine* engine, Gang* owner = NULL, const char* characterName = "");
		virtual ~Character(void);
		boost::shared_ptr<Ship> getShip();
		boost::shared_ptr<Ship> setShip(const boost::shared_ptr<Ship>& ship);
		boost::shared_ptr<Ship> setShip(TypeID typeID);

		virtual boost::shared_ptr<Environment> getEnvironment();
		
		virtual void reset();
		
		boost::shared_ptr<Skill> getSkill(TypeID typeID);
		
		bool emptyImplantSlot(int slot);
		bool emptyBoosterSlot(int slot);
		boost::shared_ptr<Implant> getImplant(int slot);
		boost::shared_ptr<Booster> getBooster(int slot);
		boost::shared_ptr<Implant> addImplant(TypeID typeID);
		boost::shared_ptr<Implant> addImplant(const boost::shared_ptr<Implant>& implant);
		boost::shared_ptr<Booster> addBooster(TypeID typeID);
		boost::shared_ptr<Booster> addBooster(const boost::shared_ptr<Booster>& booster);
		void removeImplant(const boost::shared_ptr<Implant>& implant);
		void removeBooster(const boost::shared_ptr<Booster>& booster);
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
		boost::shared_ptr<Ship> ship_;
		SkillsMap skills_;
		ImplantsList implants_;
		BoostersList boosters_;
		std::string characterName_;

		boost::shared_ptr<Skill> addSkill(TypeID typeID, int skillLevel, bool isLearned);
		void removeSkill(boost::shared_ptr<Skill>& skill);
	};
}