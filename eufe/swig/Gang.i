%include "types.i"
%include "Item.i"
%include "Character.i"

namespace eufe {
	
	%nodefaultctor Gang;

	class Gang : public eufe::Item
	{
		public:
		const eufe::CharactersList& getPilots();
		eufe::Character* addPilot();
		eufe::Character* addPilot(eufe::Character* character);
		void removePilot(eufe::Character* character);
		eufe::Character* getFleetBooster();
		eufe::Character* getWingBooster();
		eufe::Character* getSquadBooster();
		void setFleetBooster(eufe::Character* fleetBooster);
		void setWingBooster(eufe::Character* wingBooster);
		void setSquadBooster(eufe::Character* squadBooster);
		void removeFleetBooster();
		void removeWingBooster();
		void removeSquadBooster();
	};
	
}