//
//  DGMProductionState.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import <Foundation/Foundation.h>
#import "Utility.h"

@class DGMCommodity;
@class DGMProductionCycle;
@interface DGMState : NSObject
@property (readonly, nonnull) NSDate* timestamp;
@property (readonly, nonnull) NSArray<DGMCommodity*>* commodities;

- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");
@end

@interface DGMProductionState : DGMState
@property (readonly, nullable) DGMProductionCycle* cycle;
@property (readonly) DGMPercent efficiency;
@end
