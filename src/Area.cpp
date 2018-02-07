//
//  Area.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Area.hpp"
#include "SDE.hpp"

namespace dgmpp {
	
	Area::Area (TypeID typeID) : Type(typeID) {
		if (!std::any_of(SDE::areaCategories.begin(), SDE::areaCategories.end(), [categoryID = metaInfo().categoryID](const auto& i) { return categoryID == i; })) {
			throw InvalidCategoryID(metaInfo().categoryID);
		}
	}
	
	void Area::setEnabled_(bool enabled) {
		if (isEnabled_() == enabled)
			return Type::setEnabled_(enabled);
		else
			Type::setEnabled_(enabled);
		
		if (enabled)
			activateEffects_(MetaInfo::Effect::Category::system);
		else
			deactivateEffects_(MetaInfo::Effect::Category::system);
	}
}
