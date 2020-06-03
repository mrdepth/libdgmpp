//
//  Booster.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include "Type.hpp"

namespace dgmpp {
	
	class Booster: public Type {
	public:
        Booster (TypeID typeID);
        Booster (const Booster& other) : Type(other), slot_(other.slot_) {}

		using Slot = int;
		
		Slot slot() const noexcept { return slot_; }
	protected:
	private:
		const Slot slot_ {static_cast<Slot>(attribute_(AttributeID::boosterness)->value_())};
		friend class Character;
		

	};
}

