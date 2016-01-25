//
//  Route.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Route.h"
#include "Facility.h"
#include "Planet.h"
#include "Commodity.h"

using namespace dgmpp;

Route::Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, const Commodity& commodity, int64_t identifier) : source_(source), destination_(destination), commodity_(commodity), identifier_(identifier) {
};

std::shared_ptr<Facility> Route::getSource() const {
	return source_.lock();
}

std::shared_ptr<Facility> Route::getDestination() const {
	return destination_.lock();
}

void Route::update(double time) const {
	if (commodity_.getTypeID()) {
		uint32_t quantity = std::min(getSource()->getCommodity(commodity_).getQuantity(), getDestination()->getFreeStorage(commodity_));
		if (quantity > 0) {
			auto product = Commodity(commodity_, quantity);
			getSource()->extractCommodity(product);
			getDestination()->addCommodity(product);
			getDestination()->update(time);
		}
	}
}
