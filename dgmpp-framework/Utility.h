//
//  Utility.h
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import <Foundation/Foundation.h>


typedef NSInteger DGMTypeID;
typedef NSInteger DGMGroupID;
typedef NSInteger DGMCategoryID;
typedef NSInteger DGMAttributeID;
typedef NSInteger DGMEffectID;
typedef NSInteger DGMWarfareBuffID;
typedef NSInteger DGMSchematicID;
typedef NSInteger DGMModifierID;
typedef NSInteger DGMImplantSlot;
typedef NSInteger DGMBoosterSlot;

typedef double DGMGigaJoule;
typedef double DGMTeraflops;
typedef double DGMMegaWatts;
typedef double DGMCalibrationPoints;
typedef double DGMCubicMeter;
typedef double DGMMeter;
typedef double DGMMillimeter;
typedef double DGMMegabitsPerSecond;
typedef double DGMKilogram;
typedef double DGMPoints;
typedef double DGMHP;
typedef double DGMRadians;
typedef double DGMAstronomicalUnit;
typedef double DGMPercent;
typedef double DGMMultiplier;

typedef double DGMGigaJoulePerSecond NS_REFINED_FOR_SWIFT;
typedef double DGMCubicMeterPerSecond NS_REFINED_FOR_SWIFT;
typedef double DGMRadiansPerSecond NS_REFINED_FOR_SWIFT;
typedef double DGMMetersPerSecond NS_REFINED_FOR_SWIFT;
typedef double DGMAstronomicalUnitsPerSecond NS_REFINED_FOR_SWIFT;
typedef double DGMHPPerSecond NS_REFINED_FOR_SWIFT;
typedef double DGMFuelUnitsPerHour NS_REFINED_FOR_SWIFT;

typedef NSError * _Nullable __autoreleasing * _Nullable NSErrorPtr;

typedef NS_ENUM(NSInteger, DGMRaceID) {
	DGMRaceIDNone = 0,
	DGMRaceIDCaldari = 1,
	DGMRaceIDMinmatar = 2,
	DGMRaceIDAmarr = 4,
	DGMRaceIDGallente = 8
};


typedef NS_ENUM(NSInteger, DGMScanType) {
	DGMScanTypeRadar,
	DGMScanTypeLadar,
	DGMScanTypeMagnetometric,
	DGMScanTypeGravimetric,
	DGMScanTypeMultispectral
};

typedef struct {
	DGMHP em;
	DGMHP thermal;
	DGMHP kinetic;
	DGMHP explosive;
} DGMDamageVector;

typedef DGMDamageVector DGMDamagePerSecond NS_REFINED_FOR_SWIFT;

typedef struct {
	DGMHP shield;
	DGMHP armor;
	DGMHP hull;
} DGMHitPoints;

typedef struct {
	DGMHPPerSecond passiveShield;
	DGMHPPerSecond shieldRepair;
	DGMHPPerSecond armorRepair;
	DGMHPPerSecond hullRepair;
} DGMTank NS_REFINED_FOR_SWIFT;

typedef struct {
	DGMPercent em;
	DGMPercent thermal;
	DGMPercent kinetic;
	DGMPercent explosive;
} DGMResistancesLayer;


typedef struct {
	DGMResistancesLayer shield;
	DGMResistancesLayer armor;
	DGMResistancesLayer hull;
} DGMResistances;

typedef NS_ENUM(NSInteger, DGMModuleSlot) {
	DGMModuleSlotUnknown = -1,
	DGMModuleSlotNone = 0,
	DGMModuleSlotHi,
	DGMModuleSlotMed,
	DGMModuleSlotLow,
	DGMModuleSlotRig,
	DGMModuleSlotSubsystem,
	DGMModuleSlotMode,
	DGMModuleSlotService,
	DGMModuleSlotStarbaseStructure
};

typedef NS_ENUM(NSInteger, DGMModuleHardpoint) {
	DGMModuleHardpointNone = 0,
	DGMModuleHardpointLauncher,
	DGMModuleHardpointTurret,
};

typedef NS_ENUM(NSInteger, DGMModuleState) {
	DGMModuleStateUnknown = -1,
	DGMModuleStateOffline,
	DGMModuleStateOnline,
	DGMModuleStateActive,
	DGMModuleStateOverloaded
};

typedef NS_ENUM(NSInteger, DGMDroneSquadron) {
	DGMDroneSquadronNone = 0,
	DGMDroneSquadronHeavy,
	DGMDroneSquadronLight,
	DGMDroneSquadronSupport
};

typedef NS_ENUM(NSInteger, DGMChargeSize) {
	DGMChargeSizeNone = 0,
	DGMChargeSizeSmall = 1,
	DGMChargeSizeMedium = 2,
	DGMChargeSizeLarge = 3,
	DGMChargeSizeXLarge = 4
};


typedef struct {
	DGMRadiansPerSecond angularVelocity;
	DGMMetersPerSecond velocity;
	DGMMeter signature;
	DGMMeter range;
} DGMHostileTarget NS_REFINED_FOR_SWIFT;

