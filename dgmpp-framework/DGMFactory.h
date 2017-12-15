//
//  DGMFactory.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "DGMFacility.h"

@class DGMCommodity;
@class DGMProductionState;
@class DGMProductionCycle;
@interface DGMFactory : DGMFacility
@property (readonly) DGMSchematicID schematicID;
- (BOOL) setSchematicID:(DGMSchematicID)schematicID error:(NSErrorPtr) error;
@property (nonnull) NSDate* launchTime;
@property (readonly) NSTimeInterval cycleTime;
@property (readonly, nullable) DGMCommodity* output;
@property (readonly, nonnull) NSArray<DGMProductionState*>* states;
@property (readonly, nonnull) NSArray<DGMProductionCycle*>* cycles;

@end
