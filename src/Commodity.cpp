//
//  Commodity.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Commodity.hpp"
#include "SDE.hpp"

namespace dgmpp {
	
	Commodity::Commodity(TypeID typeID, size_t quantity) : Commodity(SDE::commodity(typeID), quantity) {}

}
