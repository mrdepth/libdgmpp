%include "Item.i"
%include "Booster.i"
%include "Implant.i"
%include "Skill.i"
%include "Ship.i"
%include <std_map.i>

namespace std {
	%template(SkillLevelsMap) map<dgmpp::TypeID, int>;
}

%shared_ptr(dgmpp::Character);

namespace dgmpp {

	%nodefaultctor Character;

	class Character : public dgmpp::Item
	{
	public:
		std::shared_ptr<dgmpp::Ship> getShip();
		std::shared_ptr<dgmpp::Ship> setShip(dgmpp::TypeID typeID);
		
		std::shared_ptr<dgmpp::Skill> getSkill(dgmpp::TypeID typeID);
		
		bool emptyImplantSlot(int slot);
		bool emptyBoosterSlot(int slot);
		std::shared_ptr<dgmpp::Implant> getImplant(int slot);
		std::shared_ptr<dgmpp::Booster> getBooster(int slot);
		std::shared_ptr<dgmpp::Implant> addImplant(dgmpp::TypeID typeID);
		std::shared_ptr<dgmpp::Booster> addBooster(dgmpp::TypeID typeID);
		void removeImplant(const std::shared_ptr<dgmpp::Implant>& implant);
		void removeBooster(const std::shared_ptr<dgmpp::Booster>& booster);
		%extend {
			std::vector<std::shared_ptr<dgmpp::Implant>> getImplants() {
				const dgmpp::ImplantsList& implants = $self->getImplants();
				return std::vector<std::shared_ptr<dgmpp::Implant>>(implants.begin(), implants.end());
			}

			std::vector<std::shared_ptr<dgmpp::Booster>> getBoosters() {
				const dgmpp::BoostersList& boosters = $self->getBoosters();
				return std::vector<std::shared_ptr<dgmpp::Booster>>(boosters.begin(), boosters.end());
			}
		}
		
		void setCharacterName(const char* characterName = "");
		const char* getCharacterName();
		void setSkillLevels(const std::map<dgmpp::TypeID, int>& levels);
		void setAllSkillsLevel(int level);
	};
}