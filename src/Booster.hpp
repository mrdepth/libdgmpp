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
		static std::unique_ptr<Booster> Create (TypeID typeID) { return std::unique_ptr<Booster>(new Booster(typeID)); }
		static std::unique_ptr<Booster> Create (const Booster& other) { return std::unique_ptr<Booster>(new Booster(other)); }
		
		using Slot = int;
		
		Slot slot() const noexcept { return slot_; }
	protected:
	private:
		Slot slot_;
		friend class Character;
		
		Booster (TypeID typeID) : Type(typeID) {
			slot_ = static_cast<Slot>(attribute_(AttributeID::boosterness)->value_());
		}
		
		Booster (const Booster& other) : Type(other) {
			slot_ = other.slot_;
		}

	};
}

