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

Route::Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier) : source_(source), destination_(destination), identifier_(identifier) {
	if (contentTypeID)
		commodity_ = std::make_shared<Commodity>(source->getOwner()->getEngine(), contentTypeID);
	else
		commodity_ = std::make_shared<Commodity>(Commodity::InvalidCommodity());
};

std::shared_ptr<Facility> Route::getSource() const {
	return source_.lock();
}

std::shared_ptr<Facility> Route::getDestination() const {
	return destination_.lock();
}
