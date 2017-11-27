//
//  HitPoints.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 24.11.2017.
//

#pragma once
#include "Utility.hpp"
#include "DamageVector.hpp"

namespace dgmpp2 {
	
	struct HitPoints {
		union {
			struct {
				HP shield;
				HP armor;
				HP hull;
			};
			HP layers[3];
		};

		HitPoints effective (const Resistances& resistances, const DamageVector damagePattern) {
			return {
				shield * damagePattern.effectivity(resistances.shield),
				armor * damagePattern.effectivity(resistances.armor),
				hull * damagePattern.effectivity(resistances.hull)
			};
		}
		
		HP total() const {
			return shield + armor + hull;
		}
		
		explicit operator HP() const {
			return total();
		}

	};
}

