//
//  DGMFacility.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import <Foundation/Foundation.h>
#import "Utility.h"

@class DGMCommodity;
@interface DGMFacility : NSObject
@property (readonly) int64_t identifier;
@property (readonly) DGMCubicMeter capacity;
@property (readonly) DGMCubicMeter freeVolume;
@property (readonly) DGMCubicMeter usedVolume;
@property (readonly, nonnull) NSArray<DGMCommodity*>* commodities;

- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");
- (nullable DGMCommodity*) objectAtIndexedSubscript: (DGMTypeID) typeID;
- (nullable DGMCommodity*) incomeWithTypeID:(DGMTypeID) typeID;
- (void) addCommodity:(nonnull DGMCommodity*) commodity;
- (void) extractCommodity:(nonnull DGMCommodity*) commodity;
@end
