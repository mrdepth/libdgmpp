//
//  Structure.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Ship.hpp"

namespace dgmpp2 {
	class Structure: public Ship {
	public:
		static std::unique_ptr<Structure> Create (TypeID typeID) { return std::unique_ptr<Structure>(new Structure(typeID)); }
		
		TypeID fuelBlockTypeID();
		rate<Float, std::chrono::hours> fuelUse();
	private:
		
		Structure(TypeID typeID) : Ship(typeID) {}
	};
}
