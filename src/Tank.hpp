//
//  Tank.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include "Utility.hpp"
#include "DamageVector.hpp"

namespace dgmpp {
	
	struct Tank {
		Tank() {};
		Tank(HPPerSecond passiveShield,
			 HPPerSecond shieldRepair,
			 HPPerSecond armorRepair,
			 HPPerSecond hullRepair)
		: passiveShield(passiveShield), shieldRepair(shieldRepair), armorRepair(armorRepair), hullRepair(hullRepair) {}
		
		union {
			struct {
				HPPerSecond passiveShield;
				HPPerSecond shieldRepair;
				HPPerSecond armorRepair;
				HPPerSecond hullRepair;
			};
			HPPerSecond layers[4];
		};
		
		Tank effective (const Resistances& resistances, const DamageVector damagePattern) const noexcept {
			return {
				passiveShield * damagePattern.effectivity(resistances.shield),
				shieldRepair * damagePattern.effectivity(resistances.shield),
				armorRepair * damagePattern.effectivity(resistances.armor),
				hullRepair * damagePattern.effectivity(resistances.hull)
			};
		}
		
	};
}
