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
@property(readonly) DGMGigaJoulePerSecond use NS_REFINED_FOR_SWIFT;
@property(readonly) DGMGigaJoulePerSecond recharge NS_REFINED_FOR_SWIFT;

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
@property (readonly) DGMTank tank NS_REFINED_FOR_SWIFT;
@property (readonly) DGMTank effectiveTank NS_REFINED_FOR_SWIFT;
@property (readonly) DGMTank sustainableTank NS_REFINED_FOR_SWIFT;
@property (readonly) DGMTank effectiveSustainableTank NS_REFINED_FOR_SWIFT;
@property (readonly) DGMHitPoints hitPoints;
@property (readonly) DGMHitPoints effectiveHitPoints;

@property (readonly) DGMDamageVector turretsVolley;
@property (readonly) DGMDamageVector launchersVolley;
@property (readonly) DGMDamageVector dronesVolley;
@property (readonly) DGMDamagePerSecond turretsDPS NS_REFINED_FOR_SWIFT;
@property (readonly) DGMDamagePerSecond launchersDPS NS_REFINED_FOR_SWIFT;
@property (readonly) DGMDamagePerSecond dronesDPS NS_REFINED_FOR_SWIFT;
- (DGMDamagePerSecond) turretsDPSWithTaget:(DGMHostileTarget) target NS_SWIFT_NAME(__turretsDPS(target:)) NS_REFINED_FOR_SWIFT;
- (DGMDamagePerSecond) launchersDPSWithTaget:(DGMHostileTarget) target NS_SWIFT_NAME(__launchersDPS(target:)) NS_REFINED_FOR_SWIFT;
- (DGMDamagePerSecond) dronesDPSWithTaget:(DGMHostileTarget) target NS_SWIFT_NAME(__dronesDPS(target:)) NS_REFINED_FOR_SWIFT;

@property (readonly) DGMCubicMeterPerSecond minerYield NS_REFINED_FOR_SWIFT;
@property (readonly) DGMCubicMeterPerSecond droneYield NS_REFINED_FOR_SWIFT;

@property (readonly) NSTimeInterval alignTime;
@property (readonly) DGMAstronomicalUnitsPerSecond warpSpeed NS_REFINED_FOR_SWIFT;
@property (readonly) DGMMetersPerSecond velocity NS_REFINED_FOR_SWIFT;
@property (readonly) DGMMeter signatureRadius;
@property (readonly) DGMKilogram mass;
@property (readonly) DGMCubicMeter volume;
@property (readonly) DGMMultiplier agility;
- (DGMMetersPerSecond) maxVelocityInOrbit:(DGMMeter) radius NS_SWIFT_NAME(__maxVelocity(orbit:)) NS_REFINED_FOR_SWIFT;
- (DGMMeter) orbitRadiusWithTransverseVelocity:(DGMMetersPerSecond) velocity NS_SWIFT_NAME(__orbitRadius(transverseVelocity:)) NS_REFINED_FOR_SWIFT;
- (DGMMeter) orbitRadiusWithAngularVelocity:(DGMRadiansPerSecond) velocity NS_SWIFT_NAME(__orbitRadius(angularVelocity:)) NS_REFINED_FOR_SWIFT;

@property (readonly) NSInteger maxTargets;
@property (readonly) DGMMeter maxTargetRange;
@property (readonly) DGMPoints scanStrength;
@property (readonly) DGMScanType scanType;
@property (readonly) DGMMeter probeSize;
@property (readonly) DGMMillimeter scanResolution;
@end
