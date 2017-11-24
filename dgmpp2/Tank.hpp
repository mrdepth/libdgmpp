//
//  Tank.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include "Utility.hpp"
#include "DamageVector.hpp"

namespace dgmpp2 {
	
	struct Tank {
		union {
			struct {
				rate<HP, std::chrono::seconds> passiveShield;
				rate<HP, std::chrono::seconds> shieldRepair;
				rate<HP, std::chrono::seconds> armorRepair;
				rate<HP, std::chrono::seconds> hullRepair;
			};
			rate<HP, std::chrono::seconds> layers[4];
		};
		
		Tank effective (const Resistances& resistances, const DamageVector damagePattern) {
			return {
				passiveShield * damagePattern.effectivity(resistances.shield),
				shieldRepair * damagePattern.effectivity(resistances.shield),
				armorRepair * damagePattern.effectivity(resistances.armor),
				hullRepair * damagePattern.effectivity(resistances.hull)
			};
		}
		
	};
}
