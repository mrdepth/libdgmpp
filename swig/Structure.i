%include "Ship.i"

namespace dgmpp {
	
	class Structure: public Ship {
	public:
		TypeID fuelBlockTypeID();
		rate<Float, std::chrono::hours> fuelUse();
	};
}
