//
//  Charge.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Type.hpp"

namespace dgmpp2 {
	class Charge: public Type {
	public:
		static std::unique_ptr<Charge> Create (TypeID typeID) { return std::unique_ptr<Charge>(new Charge(typeID)); }
		
		int chargeSize();
		
	protected:
		virtual Type* domain (MetaInfo::Modifier::Domain domain) override;
		bool canBeActive() const	{ return flags_.canBeActive; }
		bool requireTarget() const	{ return flags_.requireTarget; }
		bool isAssistance() const	{ return flags_.isAssistance; }
		bool isOffensive() const	{ return flags_.isOffensive; }
		bool dealsDamage() const	{ return flags_.dealsDamage; }

	private:
		friend class Module;
		friend class Drone;
		
		struct {
			bool canBeActive : 1;
			bool requireTarget : 1;
			bool isAssistance : 1;
			bool isOffensive : 1;
			bool dealsDamage : 1;
		} flags_;
		
		Charge(TypeID typeID);
	};
}
