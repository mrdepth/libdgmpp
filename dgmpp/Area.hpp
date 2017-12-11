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
		static std::unique_ptr<Area> Create (TypeID typeID) { return std::unique_ptr<Area>(new Area(typeID)); }
		virtual void setEnabled(bool enabled) override;
	private:
		friend class Ship;
		Area (TypeID typeID) : Type(typeID) {}
	};
}


