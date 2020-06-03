//
//  Implant.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include "Type.hpp"

namespace dgmpp {
	
	class Implant: public Type {
	public:
        Implant (TypeID typeID);
        Implant (const Implant& other) : Type(other), slot_(other.slot_) {}

		using Slot = int;
		
		Slot slot() const noexcept { return slot_; }
	protected:
	private:
		const Slot slot_ {static_cast<Slot>(attribute_(AttributeID::implantness)->value_())};
		friend class Character;
		
	};
}

