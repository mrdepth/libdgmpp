//
//  Spaceport.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "Storage.hpp"

namespace dgmpp {
	
	class Spaceport: public Storage {
	public:
	protected:
		using Storage::Storage;
	public:
		friend class Planet;
	};
	
}

