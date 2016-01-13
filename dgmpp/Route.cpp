//
//  Route.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Route.h"

using namespace dgmpp;

Route::Route(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier) : source_(source), destination_(destination), contentTypeID_(contentTypeID), identifier_(identifier) {
};
