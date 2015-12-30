%include "Skill.i"
%include "Booster.i"
%include "Implant.i"
%include "Skill.i"
%include <std_map.i>

namespace std {
	%template(SkillLevelsMap) map<dgmpp::TypeID, int>;
}

namespace dgmpp {
	

	
	%nodefaultctor Character;

	class Character : public Item
	{
	public:
		dgmpp::Ship* getShip();
		dgmpp::Ship* setShip(dgmpp::TypeID typeID);
		
		dgmpp::Skill* getSkill(dgmpp::TypeID typeID);
		
		bool emptyImplantSlot(int slot);
		bool emptyBoosterSlot(int slot);
		dgmpp::Implant* getImplant(int slot);
		dgmpp::Booster* getBooster(int slot);
		dgmpp::Implant* addImplant(dgmpp::TypeID typeID);
		dgmpp::Implant* addImplant(dgmpp::Implant* implant);
		dgmpp::Booster* addBooster(dgmpp::TypeID typeID);
		dgmpp::Booster* addBooster(dgmpp::Booster* booster);
		void removeImplant(dgmpp::Implant* implant);
		void removeBooster(dgmpp::Booster* booster);
		%extend {
			std::vector<dgmpp::Implant*> getImplants() {
				const dgmpp::ImplantsList& implants = $self->getImplants();
				return std::vector<dgmpp::Implant*>(implants.begin(), implants.end());
			}

			std::vector<dgmpp::Booster*> getBoosters() {
				const dgmpp::BoostersList& boosters = $self->getBoosters();
				return std::vector<dgmpp::Booster*>(boosters.begin(), boosters.end());
			}
		}
		
		void setCharacterName(const char* characterName = "");
		const char* getCharacterName();
		void setSkillLevels(const std::map<dgmpp::TypeID, int>& levels);
		void setAllSkillsLevel(int level);
	};
}