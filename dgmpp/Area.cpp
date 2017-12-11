//
//  Area.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Area.hpp"

namespace dgmpp {
	
	void Area::setEnabled(bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
		
		if (enabled)
			activateEffects(MetaInfo::Effect::Category::system);
		else
			deactivateEffects(MetaInfo::Effect::Category::system);
	}
}
