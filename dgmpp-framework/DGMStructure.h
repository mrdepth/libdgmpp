//
//  DGMStructure.h
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "DGMShip.h"

@interface DGMStructure : DGMShip
@property (readonly) DGMTypeID fuelBlockTypeID;
@property (readonly) DGMFuelUnitsPerHour fuelUse;
@end
