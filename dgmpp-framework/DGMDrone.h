//
//  DGMDrone.h
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "DGMType.h"

@class DGMShip;
@class DGMCharge;
@interface DGMDrone : DGMType
@property (assign, getter = isActive) BOOL active;
@property (readonly, nullable) DGMCharge* charge;
@property (readonly) DGMDroneSquadron squadron;
@property (readonly) NSInteger squadronSize;
@property (readonly) NSInteger squadronTag;

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error;

@property (readonly, nullable) DGMShip* target;
- (BOOL) setTarget:(nullable DGMShip*) target error:(NSErrorPtr) error;

@property (readonly) NSTimeInterval cycleTime;
@property (readonly) DGMDamageVector volley;
@property (readonly) DGMDamagePerSecond dps NS_REFINED_FOR_SWIFT;
- (DGMDamagePerSecond) dpsWithTaget:(DGMHostileTarget) target NS_SWIFT_NAME(__dps(target:)) NS_REFINED_FOR_SWIFT;
@property (readonly) DGMMeter optimal;
@property (readonly) DGMMeter falloff;
@property (readonly) DGMPoints accuracyScore;
@property (readonly) DGMCubicMeterPerSecond miningYield NS_REFINED_FOR_SWIFT;
@property (readonly) DGMMetersPerSecond velocity NS_REFINED_FOR_SWIFT;

@end
