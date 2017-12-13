//
//  DGMPlanet.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import <Foundation/Foundation.h>
#import "Utility.h"

@class DGMFacility;
@class DGMRoute;
@interface DGMPlanet : NSObject
@property (readonly, nonnull) NSArray<DGMFacility*>* facilities;
@property (nonnull) NSDate* lastUpdate;

- (nonnull instancetype) init;
- (BOOL) addFacilityWithTypeID:(DGMTypeID) typeID identifier:(int64_t) identifier error:(NSErrorPtr) error NS_SWIFT_NAME(addFacility(typeID:identifier:));
- (void) removeFacility:(nonnull DGMFacility*) facility;
- (nullable DGMFacility*) objectAtIndexedSubscript: (int64_t) identifier;
- (void) addRoute:(nonnull DGMRoute*) route;
- (void) removeRoute:(nonnull DGMRoute*) route;

- (nonnull NSDate*) run;

@end
