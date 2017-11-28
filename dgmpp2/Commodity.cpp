//
//  Commodity.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Commodity.hpp"
#include "SDE.hpp"

namespace dgmpp2 {
	
	Commodity::Commodity (TypeID typeID) : metaInfo_ (SDE::commodity(typeID)) {}


}
