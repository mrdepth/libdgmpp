//
//  DGMExtractorControlUnit.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "DGMFacility.h"

@class DGMCommodity;
@class DGMProductionState;
@class DGMProductionCycle;
@interface DGMExtractorControlUnit : DGMFacility
@property (nonnull) NSDate* launchTime;
@property (nonnull) NSDate* installTime;
@property (nonnull) NSDate* expiryTime;
@property (assign) NSTimeInterval cycleTime;
@property (assign) NSInteger quantityPerCycle;
@property (readonly, nullable) DGMCommodity* output;
@property (readonly, nonnull) NSArray<DGMProductionState*>* states;
@property (readonly, nonnull) NSArray<DGMProductionCycle*>* cycles;
@end
