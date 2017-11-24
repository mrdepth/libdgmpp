//
//  Implant.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include "Type.hpp"

namespace dgmpp2 {
	
	class Implant: public Type {
	public:
		static std::unique_ptr<Implant> Create (TypeID typeID) { return std::unique_ptr<Implant>(new Implant(typeID)); }
		
		using Slot = int;
		
		Slot slot() const { return slot_; }
	protected:
	private:
		Slot slot_;
		friend class Character;
		
		Implant (TypeID typeID) : Type(typeID) {
			slot_ = static_cast<Slot>((*this)[AttributeID::implantness]->value());
		}
	};
}

