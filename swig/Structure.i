%include "Ship.i"

namespace dgmpp {
	
	class Structure: public Ship {
	public:
		Structure(TypeID typeID);

		TypeID fuelBlockTypeID();
		rate<Float, std::chrono::hours> fuelUse();
	};
}
