//
//  Booster.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#include "Booster.hpp"
#include "SDE.hpp"

namespace dgmpp {

	Booster::Booster (TypeID typeID) : Type(typeID) {
		if (!std::any_of(SDE::boosterCategories.begin(), SDE::boosterCategories.end(), [categoryID = metaInfo().categoryID](const auto& i) { return categoryID == i; })) {
			throw InvalidCategoryID(metaInfo().categoryID);
		}
	}
}
