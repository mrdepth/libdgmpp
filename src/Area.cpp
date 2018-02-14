//
//  Area.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Area.hpp"

namespace dgmpp {
	
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
