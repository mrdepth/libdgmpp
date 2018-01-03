//
//  Charge.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Type.hpp"

namespace dgmpp {
	class Charge: public Type {
	public:
		enum class Size {
			none = 0,
			small = 1,
			medium = 2,
			large = 3,
			xLarge = 4
		};

		static std::unique_ptr<Charge> Create (TypeID typeID) { return std::unique_ptr<Charge>(new Charge(typeID)); }
		static std::unique_ptr<Charge> Create (const Charge& other) { return std::unique_ptr<Charge>(new Charge(other)); }
		
		Size size();
		
	protected:
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
		
		struct {
			bool canBeActive : 1;
			bool requireTarget : 1;
			bool isAssistance : 1;
			bool isOffensive : 1;
			bool dealsDamage : 1;
		} flags_;

	private:
		friend class Module;
		friend class Drone;
		
		
		Charge (TypeID typeID);
		Charge (const Charge& other);
	};
}
