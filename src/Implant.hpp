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
		static std::unique_ptr<Implant> Create (TypeID typeID) { return std::unique_ptr<Implant>(new Implant(typeID)); }
		static std::unique_ptr<Implant> Create (const Implant& other) { return std::unique_ptr<Implant>(new Implant(other)); }
		
		using Slot = int;
		
		Slot slot() const noexcept { return slot_; }
	protected:
	private:
		Slot slot_;
		friend class Character;
		
		Implant (TypeID typeID) : Type(typeID) {
			slot_ = static_cast<Slot>(attribute_(AttributeID::implantness)->value_());
		}
		
		Implant (const Implant& other) : Type(other) {
			slot_ = other.slot_;
		}
	};
}

