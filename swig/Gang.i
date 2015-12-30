%include "types.i"
%include "Item.i"
%include "Character.i"

namespace dgmpp {
	
	%nodefaultctor Gang;

	class Gang : public dgmpp::Item
	{
		public:
		%extend {
			std::vector<dgmpp::Character*> getPilots() {
				const dgmpp::CharactersList& pilots = $self->getPilots();
				return std::vector<dgmpp::Character*>(pilots.begin(), pilots.end());
			}
		}
		dgmpp::Character* addPilot();
		dgmpp::Character* addPilot(dgmpp::Character* character);
		void removePilot(dgmpp::Character* character);
		dgmpp::Character* getFleetBooster();
		dgmpp::Character* getWingBooster();
		dgmpp::Character* getSquadBooster();
		void setFleetBooster(dgmpp::Character* fleetBooster);
		void setWingBooster(dgmpp::Character* wingBooster);
		void setSquadBooster(dgmpp::Character* squadBooster);
		void removeFleetBooster();
		void removeWingBooster();
		void removeSquadBooster();
	};
	
}