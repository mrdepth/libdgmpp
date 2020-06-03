//
//  Area.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Type.hpp"

namespace dgmpp {
	
	class Area: public Type {
	public:
        Area (TypeID typeID);
        Area (const Area& other) : Type(other) {}
	protected:
		virtual void setEnabled_ (bool enabled) override;
	private:
		friend class Ship;
		friend class Gang;
	};
}


