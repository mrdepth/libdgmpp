//
//  Structure.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Structure.hpp"
#include <numeric>

namespace dgmpp2 {
	TypeID Structure::fuelBlockTypeID() {
		switch (raceID()) {
			case RaceID::caldari:
				return TypeID::nitrogenFuelBlock;
			case RaceID::minmatar:
				return TypeID::hydrogenFuelBlock;
			case RaceID::amarr:
				return TypeID::heliumFuelBlock;
			case RaceID::gallente:
				return TypeID::oxygenFuelBlock;
			default:
				return TypeID::none;
		}
	}
	
	rate<Float, std::chrono::hours> Structure::fuelUse() {
		auto use = std::accumulate(modules_.begin(), modules_.end(), Float(0), [](auto sum, const auto& i) {
			auto& module = std::get<std::unique_ptr<Module>>(i);
			if (auto attribute = (*module)[AttributeID::serviceModuleFuelAmount])
				return sum + attribute->value();
			else
				return sum;
		});
		return make_rate(use, 1h);
	}

}
