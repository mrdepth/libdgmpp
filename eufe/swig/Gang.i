%include "types.i"
%include "Item.i"
%include "Character.i"

namespace eufe {
	
	%nodefaultctor Gang;

	class Gang : public Item
	{
		public:
		const CharactersList& getPilots();
		Character* addPilot();
		Character* addPilot(Character* character);
		void removePilot(Character* character);
		Character* getFleetBooster();
		Character* getWingBooster();
		Character* getSquadBooster();
		void setFleetBooster(Character* fleetBooster);
		void setWingBooster(Character* wingBooster);
		void setSquadBooster(Character* squadBooster);
		void removeFleetBooster();
		void removeWingBooster();
		void removeSquadBooster();
	};
	
}