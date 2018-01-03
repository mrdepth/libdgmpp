//
//  Structure.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#include "Structure.hpp"
#include <numeric>

namespace dgmpp {
	rate<Float, std::chrono::hours> Structure::fuelUse() {
		auto use = std::accumulate(modulesSet_.begin(), modulesSet_.end(), Float(0), [](auto sum, const auto& i) {
			auto& module = std::get<std::unique_ptr<Module>>(i);
			if (auto attribute = module->attribute_(AttributeID::serviceModuleFuelAmount))
				return sum + attribute->value_();
			else
				return sum;
		});
		return make_rate(use, 1h);
	}

}
