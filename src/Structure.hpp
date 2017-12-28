//
//  Structure.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Ship.hpp"

namespace dgmpp {
	class Structure: public Ship {
	public:
		static std::unique_ptr<Structure> Create (TypeID typeID) { return std::unique_ptr<Structure>(new Structure(typeID)); }
		static std::unique_ptr<Structure> Create (const Structure& other) { return std::unique_ptr<Structure>(new Structure(other)); }
		
		TypeID fuelBlockTypeID();
		rate<Float, std::chrono::hours> fuelUse();
	private:
		
		Structure(TypeID typeID) : Ship(typeID) {}
		Structure(const Structure& other) : Ship(other) {}
	};
}
