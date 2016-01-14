//
//  Route.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Route.h"
#include "Facility.h"

using namespace dgmpp;

Route::Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier) : source_(source.get()), destination_(destination.get()), contentTypeID_(contentTypeID), identifier_(identifier) {
};

std::shared_ptr<Facility> Route::getSource() const {
	return source_ ? source_->shared_from_this() : nullptr;
}

std::shared_ptr<Facility> Route::getDestination() const {
	return source_ ? destination_->shared_from_this() : nullptr;
}
