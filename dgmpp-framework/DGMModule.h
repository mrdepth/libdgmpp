//
//  DGMModule.h
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "DGMType.h"

@class DGMShip;
@class DGMCharge;
@interface DGMModule : DGMType
@property (readonly) DGMModuleSlot slot;
@property (readonly) DGMModuleHardpoint hardpoint;
@property (readonly) NSInteger socket;
@property (assign) DGMModuleState state;
@property (readonly) DGMModuleState preferredState;
@property (readonly, nonnull) NSArray<NSNumber*>* availableStates NS_REFINED_FOR_SWIFT;
@property (readonly, nullable) DGMShip* target;
- (BOOL) setTarget:(nullable DGMShip*) target error:(NSErrorPtr) error;
@property (readonly, nullable) DGMCharge* charge;
- (BOOL) setCharge:(nullable DGMCharge*) charge error:(NSErrorPtr) error;
@property (readonly, nonnull) NSArray<NSNumber*>* chargeGroups NS_REFINED_FOR_SWIFT;
@property (readonly) DGMChargeSize chargeSize;
@property (readonly) BOOL isFail;

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error;

- (BOOL) canHaveState: (DGMModuleState) state;
- (BOOL) canFitCharge: (nonnull DGMCharge*) charge;

@property (readonly) NSTimeInterval reloadTime;
@property (readonly) NSTimeInterval cycleTime;
@property (readonly) NSTimeInterval rawCycleTime;
@property (readonly) NSInteger charges;
@property (readonly) NSInteger shots;
@property (readonly) DGMGigaJoulePerSecond capUse NS_REFINED_FOR_SWIFT;
@property (readonly) DGMTeraflops cpuUse;
@property (readonly) DGMMegaWatts powerGridUse;
@property (readonly) DGMCalibrationPoints calibrationUse;
@property (readonly) DGMPoints accuracyScore;
@property (readonly) DGMMeter signatureResolution;
@property (readonly) DGMCubicMeterPerSecond miningYield NS_REFINED_FOR_SWIFT;
@property (readonly) DGMDamageVector volley;
@property (readonly) DGMDamagePerSecond dps NS_REFINED_FOR_SWIFT;
- (DGMDamagePerSecond) dpsWithTaget:(DGMHostileTarget) target NS_SWIFT_NAME(__dps(target:)) NS_REFINED_FOR_SWIFT;
@property (readonly) DGMMeter optimal;
@property (readonly) DGMMeter falloff;
@property (readonly) NSTimeInterval lifeTime;

@end
