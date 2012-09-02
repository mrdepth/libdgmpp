%include "Skill.i"
%include "Booster.i"
%include "Implant.i"
%include "Skill.i"
%include <std_map.i>

namespace std {
	%template(SkillLevelsMap) map<eufe::TypeID, int>;
}

namespace eufe {
	

	
	%nodefaultctor Character;

	class Character : public Item
	{
	public:
		eufe::Ship* getShip();
		eufe::Ship* setShip(eufe::TypeID typeID);
		
		eufe::Skill* getSkill(eufe::TypeID typeID);
		
		bool emptyImplantSlot(int slot);
		bool emptyBoosterSlot(int slot);
		eufe::Implant* getImplant(int slot);
		eufe::Booster* getBooster(int slot);
		eufe::Implant* addImplant(eufe::TypeID typeID);
		eufe::Implant* addImplant(eufe::Implant* implant);
		eufe::Booster* addBooster(eufe::TypeID typeID);
		eufe::Booster* addBooster(eufe::Booster* booster);
		void removeImplant(eufe::Implant* implant);
		void removeBooster(eufe::Booster* booster);
		const eufe::ImplantsList& getImplants();
		const eufe::BoostersList& getBoosters();
		void setCharacterName(const char* characterName = "");
		const char* getCharacterName();
		void setSkillLevels(const std::map<eufe::TypeID, int>& levels);
		void setAllSkillsLevel(int level);
	};
}