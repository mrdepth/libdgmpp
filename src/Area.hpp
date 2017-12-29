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
		static std::unique_ptr<Area> Create (const Area& other) { return std::unique_ptr<Area>(new Area(other)); }
	protected:
		virtual void setEnabled (bool enabled) override;
	private:
		friend class Ship;
		friend class Gang;
		Area (TypeID typeID) : Type(typeID) {}
		Area (const Area& other) : Type(other) {}
	};
}


