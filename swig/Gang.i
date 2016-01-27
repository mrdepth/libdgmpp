%include "types.i"
%include "Item.i"
%include "Character.i"

%shared_ptr(dgmpp::Gang);

namespace dgmpp {

	%nodefaultctor Gang;

	class Gang : public dgmpp::Item
	{
		public:
		%extend {
			std::vector<std::shared_ptr<dgmpp::Character>> getPilots() {
				const dgmpp::CharactersList& pilots = $self->getPilots();
				return std::vector<std::shared_ptr<dgmpp::Character>>(pilots.begin(), pilots.end());
			}
		}
		std::shared_ptr<dgmpp::Character> addPilot();
		void removePilot(const std::shared_ptr<dgmpp::Character>& character);
		std::shared_ptr<dgmpp::Character> getFleetBooster();
		std::shared_ptr<dgmpp::Character> getWingBooster();
		std::shared_ptr<dgmpp::Character> getSquadBooster();
		void setFleetBooster(const std::shared_ptr<dgmpp::Character>& fleetBooster);
		void setWingBooster(const std::shared_ptr<dgmpp::Character>& wingBooster);
		void setSquadBooster(const std::shared_ptr<dgmpp::Character>& squadBooster);
		void removeFleetBooster();
		void removeWingBooster();
		void removeSquadBooster();
	};
	
}