//
//  DGMStructure.m
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "Internal.h"

@implementation DGMStructure

- (DGMTypeID) fuelBlockTypeID {
	return static_cast<DGMTypeID>(dynamic_cast<dgmpp::Structure*>(self.type)->fuelBlockTypeID());
}

- (DGMFuelUnitsPerHour) fuelUse {
	return static_cast<DGMFuelUnitsPerHour>(dynamic_cast<dgmpp::Structure*>(self.type)->fuelUse() * 1h);
}

@end
