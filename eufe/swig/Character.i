%include "Skill.i"
%include "Booster.i"
%include "Implant.i"
%include "Skill.i"

namespace eufe {
	
	%template(SkillLevelsMap) std::map<TypeID, int>;
	
	%nodefaultctor Character;

	class Character : public Item
	{
	public:
		Ship* getShip();
		Ship* setShip(TypeID typeID);
		
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
		void setCharacterName(const char* characterName = "");
		const char* getCharacterName();
		void setSkillLevels(const std::map<TypeID, int>& levels);
		void setAllSkillsLevel(int level);
	};
}