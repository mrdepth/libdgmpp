//
//  DGMShip.h
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "DGMType.h"

@interface DGMCapacitor: NSObject
- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");

@property(readonly) DGMGigaJoule capacity;
@property(readonly) NSTimeInterval rechargeTime;
@property(readonly) NSTimeInterval lastsTime;
@property(readonly) BOOL isStable;
@property(readonly) DGMPercent stableLevel;
@property(readonly) DGMGigaJoulePerSecond use;
@property(readonly) DGMGigaJoulePerSecond recharge;

@end

@class DGMModule;
@class DGMDrone;
@class DGMArea;
@interface DGMShip : DGMType
@property (readonly) DGMRaceID raceID;
@property (readonly, nonnull) NSArray<NSNumber*>* supportedDroneCategories NS_REFINED_FOR_SWIFT;
@property (nullable) DGMArea* area;

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error;

@property (readonly) NSInteger rigSize;
@property (assign) DGMDamageVector damagePattern;

- (BOOL) addModule:(nonnull DGMModule*) module socket:(NSInteger) socket ignoringRequirements:(BOOL) ignoringRequirements error:(NSErrorPtr) error;
- (BOOL) addModule:(nonnull DGMModule*) module socket:(NSInteger) socket error:(NSErrorPtr) error;
- (BOOL) addModule:(nonnull DGMModule*) module error:(NSErrorPtr) error;
- (BOOL) addDrone:(nonnull DGMDrone*) drone squadronTag:(NSInteger) squadronTag error:(NSErrorPtr) error;
- (BOOL) addDrone:(nonnull DGMDrone*) drone error:(NSErrorPtr) error;
- (void) removeModule:(nonnull DGMModule*) module;
- (void) removeDrone:(nonnull DGMDrone*) drone;
- (BOOL) canFitModule:(nonnull DGMModule*) module;
- (BOOL) canFitDrone:(nonnull DGMDrone*) drone;
@property (readonly, nonnull) NSArray<DGMModule*>* modules;
@property (readonly, nonnull) NSArray<DGMDrone*>* drones;
- (nonnull NSArray<DGMModule*>*) modulesWithSlot:(DGMModuleSlot) slot;

- (NSInteger) totalDroneSquadron:(DGMDroneSquadron) squadron;
- (NSInteger) usedDroneSquadron:(DGMDroneSquadron) squadron;
@property (readonly) NSInteger totalFighterLaunchTubes;
@property (readonly) NSInteger usedFighterLaunchTubes;

- (NSInteger) totalSlots:(DGMModuleSlot) slot;
- (NSInteger) freeSlots:(DGMModuleSlot) slot;
- (NSInteger) usedSlots:(DGMModuleSlot) slot;
- (NSInteger) totalHardpoints:(DGMModuleHardpoint) hardpoint;
- (NSInteger) freeHardpoints:(DGMModuleHardpoint) hardpoint;
- (NSInteger) usedHardpoints:(DGMModuleHardpoint) hardpoint;

@property (readonly, nonnull) DGMCapacitor* capacitor;

@property (readonly) DGMCalibrationPoints usedCalibration;
@property (readonly) DGMCalibrationPoints totalCalibration;
@property (readonly) DGMGigaJoule usedPowerGrid;
@property (readonly) DGMGigaJoule totalPowerGrid;
@property (readonly) DGMTeraflops usedCPU;
@property (readonly) DGMTeraflops totalCPU;
@property (readonly) DGMMegabitsPerSecond usedDroneBandwidth;
@property (readonly) DGMMegabitsPerSecond totalDroneBandwidth;
@property (readonly) DGMCubicMeter usedDroneBay;
@property (readonly) DGMCubicMeter totalDroneBay;
@property (readonly) DGMCubicMeter usedFighterHangar;
@property (readonly) DGMCubicMeter totalFighterHangar;
@property (readonly) DGMCubicMeter cargoCapacity;
@property (readonly) DGMCubicMeter oreHoldCapacity;

@property (readonly) DGMResistances resistances;
@property (readonly) DGMTank tank;
@property (readonly) DGMTank effectiveTank;
@property (readonly) DGMTank sustainableTank;
@property (readonly) DGMTank effectiveSustainableTank;
@property (readonly) DGMHitPoints hitPoints;
@property (readonly) DGMHitPoints effectiveHitPoints;

@property (readonly) DGMDamageVector turretsVolley;
@property (readonly) DGMDamageVector launchersVolley;
@property (readonly) DGMDamageVector dronesVolley;
@property (readonly) DGMDamagePerSecond turretsDPS;
@property (readonly) DGMDamagePerSecond launchersDPS;
@property (readonly) DGMDamagePerSecond dronesDPS;
- (DGMDamagePerSecond) turretsDPSWithTaget:(DGMHostileTarget) target;
- (DGMDamagePerSecond) launchersDPSWithTaget:(DGMHostileTarget) target;
- (DGMDamagePerSecond) dronesDPSWithTaget:(DGMHostileTarget) target;

@property (readonly) DGMCubicMeterPerSecond minerYield;
@property (readonly) DGMCubicMeterPerSecond droneYield;

@property (readonly) NSTimeInterval alignTime;
@property (readonly) DGMAstronomicalUnitsPerSecond warpSpeed;
@property (readonly) DGMMetersPerSecond velocity;
@property (readonly) DGMMeter signatureRadius;
@property (readonly) DGMKilogram mass;
@property (readonly) DGMCubicMeter volume;
@property (readonly) DGMMultiplier agility;
- (DGMMetersPerSecond) maxVelocityInOrbit:(DGMMeter) radius;
- (DGMMeter) orbitRadiusWithTransverseVelocity:(DGMMetersPerSecond) velocity;
- (DGMMeter) orbitRadiusWithAngularVelocity:(DGMRadiansPerSecond) velocity;

@property (readonly) NSInteger maxTargets;
@property (readonly) DGMMeter maxTargetRange;
@property (readonly) DGMPoints scanStrength;
@property (readonly) DGMScanType scanType;
@property (readonly) DGMMeter probeSize;
@property (readonly) DGMMillimeter scanResolution;
@end
