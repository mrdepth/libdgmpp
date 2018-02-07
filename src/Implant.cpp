//
//  Implant.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#include "Implant.hpp"
#include "SDE.hpp"

namespace dgmpp {
	
	Implant::Implant (TypeID typeID) : Type(typeID) {
		if (!std::any_of(SDE::implantCategories.begin(), SDE::implantCategories.end(), [categoryID = metaInfo().categoryID](const auto& i) { return categoryID == i; })) {
			throw InvalidCategoryID(metaInfo().categoryID);
		}
	}
}
