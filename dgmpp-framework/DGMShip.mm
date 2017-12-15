//
//  DGMShip.m
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "Internal.h"

using namespace std::chrono_literals;

@implementation DGMCapacitor {
	dgmpp::Capacitor* _capacitor;
}

- (nonnull instancetype) initWithCapacitor:(dgmpp::Capacitor*) capacitor {
	if (self = [super init]) {
		_capacitor = capacitor;
	}
	return self;
}

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (DGMGigaJoule) capacity {
	return static_cast<DGMGigaJoule>(_capacitor->capacity());
}

- (NSTimeInterval) rechargeTime {
	return NSTimeIntervalMake(_capacitor->rechargeTime());
}

- (NSTimeInterval) lastsTime {
	return NSTimeIntervalMake(_capacitor->lastsTime());
}

- (BOOL) isStable {
	return _capacitor->isStable();
}

- (DGMPercent) stableLevel {
	return static_cast<DGMPercent>(_capacitor->stableLevel());
}

- (DGMGigaJoulePerSecond) use {
	return static_cast<DGMGigaJoulePerSecond>(_capacitor->use() * 1s);
}

- (DGMGigaJoulePerSecond) recharge {
	return static_cast<DGMGigaJoulePerSecond>(_capacitor->recharge() * 1s);
}



@end

@implementation DGMShip {
	std::unique_ptr<dgmpp::Ship> _ship;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	try {
		_ship = dgmpp::Ship::Create(static_cast<dgmpp::TypeID>(typeID));
		if (self = [super initWithType:_ship.get()]) {
		}
		return self;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return nil;
	}
}

- (DGMRaceID) raceID {
	return static_cast<DGMRaceID>(dynamic_cast<dgmpp::Ship*>(self.type)->raceID());
}

- (nonnull NSArray<NSNumber*>*) supportedDroneCategories {
	auto v = dynamic_cast<dgmpp::Ship*>(self.type)->supportedDroneCategories();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto i: v)
		[result addObject: @(static_cast<DGMCategoryID>(i))];
	return result;
}

- (nullable DGMArea*) area {
	return (DGMArea*) [DGMType type: dynamic_cast<dgmpp::Ship*>(self.type)->area()];
}

- (void) setArea:(nullable DGMArea *)area {
	if (area && area.area)
		dynamic_cast<dgmpp::Ship*>(self.type)->area(std::move(area.area));
	else
		dynamic_cast<dgmpp::Ship*>(self.type)->area(nullptr);
}

- (NSInteger) rigSize {
	return dynamic_cast<dgmpp::Ship*>(self.type)->rigSize();
}

- (DGMDamageVector) damagePattern {
	return DGMDamageVectorMake(dynamic_cast<dgmpp::Ship*>(self.type)->damagePattern());
}

- (void) setDamagePattern:(DGMDamageVector)damagePattern {
	dynamic_cast<dgmpp::Ship*>(self.type)->damagePattern(DamageVectorMake(damagePattern));
}

- (BOOL) addModule:(nonnull DGMModule*) module socket:(NSInteger) socket ignoringRequirements:(BOOL) ignoringRequirements error:(NSErrorPtr) error {
	try {
		if (auto& ptr = module.module)
			dynamic_cast<dgmpp::Ship*>(self.type)->add(std::move(ptr), ignoringRequirements, static_cast<dgmpp::Module::Socket>(socket));
		return YES;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return NO;
	}
}

- (BOOL) addModule:(nonnull DGMModule*) module socket:(NSInteger) socket error:(NSErrorPtr) error {
	return [self addModule:module socket:socket ignoringRequirements:NO error:error];
}

- (BOOL) addModule:(nonnull DGMModule*) module error:(NSErrorPtr) error {
	return [self addModule:module socket:static_cast<NSInteger>(dgmpp::Module::anySocket) ignoringRequirements:NO error:error];
}

- (BOOL) addDrone:(nonnull DGMDrone*) drone squadronTag:(NSInteger) squadronTag error:(NSErrorPtr) error {
	try {
		if (auto& ptr = drone.drone)
			dynamic_cast<dgmpp::Ship*>(self.type)->add(std::move(ptr), static_cast<dgmpp::Drone::SquadronTag>(squadronTag));
		return YES;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return NO;
	}
}

- (BOOL) addDrone:(nonnull DGMDrone*) drone error:(NSErrorPtr) error {
	return [self addDrone:drone squadronTag:static_cast<NSInteger>(dgmpp::Drone::anySquadronTag) error: error];
}

- (void) removeModule:(nonnull DGMModule*) module {
	dynamic_cast<dgmpp::Ship*>(self.type)->remove(dynamic_cast<dgmpp::Module*>(module.type));
}

- (void) removeDrone:(nonnull DGMDrone*) drone {
	dynamic_cast<dgmpp::Ship*>(self.type)->remove(dynamic_cast<dgmpp::Drone*>(drone.type));
}

- (BOOL) canFitModule:(nonnull DGMModule*) module {
	return dynamic_cast<dgmpp::Ship*>(self.type)->canFit(dynamic_cast<dgmpp::Module*>(module.type));
}

- (BOOL) canFitDrone:(nonnull DGMDrone*) drone {
	return dynamic_cast<dgmpp::Ship*>(self.type)->canFit(dynamic_cast<dgmpp::Drone*>(drone.type));
}

- (nonnull NSArray<DGMModule*>*) modules {
	auto v = dynamic_cast<dgmpp::Ship*>(self.type)->modules();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto i: v)
		[result addObject: [DGMType type:i]];
	return result;
}

- (nonnull NSArray<DGMDrone*>*) drones {
	auto v = dynamic_cast<dgmpp::Ship*>(self.type)->drones();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto i: v)
		[result addObject: [DGMType type:i]];
	return result;
}

- (nonnull NSArray<DGMModule*>*) modulesWithSlot:(DGMModuleSlot) slot {
	auto v = dynamic_cast<dgmpp::Ship*>(self.type)->modules(static_cast<dgmpp::Module::Slot>(slot));
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto i: v)
		[result addObject: [DGMType type:i]];
	return result;
}

- (NSInteger) totalDroneSquadron:(DGMDroneSquadron) squadron {
	return dynamic_cast<dgmpp::Ship*>(self.type)->totalDroneSquadron(static_cast<dgmpp::Drone::Squadron>(squadron));
}

- (NSInteger) usedDroneSquadron:(DGMDroneSquadron) squadron {
	return dynamic_cast<dgmpp::Ship*>(self.type)->usedDroneSquadron(static_cast<dgmpp::Drone::Squadron>(squadron));
}

- (NSInteger) totalFighterLaunchTubes {
	return dynamic_cast<dgmpp::Ship*>(self.type)->totalFighterLaunchTubes();
}

- (NSInteger) usedFighterLaunchTubes {
	return dynamic_cast<dgmpp::Ship*>(self.type)->usedFighterLaunchTubes();
}

- (NSInteger) totalSlots:(DGMModuleSlot) slot {
	return dynamic_cast<dgmpp::Ship*>(self.type)->totalSlots(static_cast<dgmpp::Module::Slot>(slot));
}

- (NSInteger) freeSlots:(DGMModuleSlot) slot {
	return dynamic_cast<dgmpp::Ship*>(self.type)->freeSlots(static_cast<dgmpp::Module::Slot>(slot));
}

- (NSInteger) usedSlots:(DGMModuleSlot) slot {
	return dynamic_cast<dgmpp::Ship*>(self.type)->usedSlots(static_cast<dgmpp::Module::Slot>(slot));
}

- (NSInteger) totalHardpoints:(DGMModuleHardpoint) hardpoint {
	return dynamic_cast<dgmpp::Ship*>(self.type)->totalHardpoints(static_cast<dgmpp::Module::Hardpoint>(hardpoint));
}

- (NSInteger) freeHardpoints:(DGMModuleHardpoint) hardpoint {
	return dynamic_cast<dgmpp::Ship*>(self.type)->freeHardpoints(static_cast<dgmpp::Module::Hardpoint>(hardpoint));
}

- (NSInteger) usedHardpoints:(DGMModuleHardpoint) hardpoint {
	return dynamic_cast<dgmpp::Ship*>(self.type)->usedHardpoints(static_cast<dgmpp::Module::Hardpoint>(hardpoint));
}

- (nonnull DGMCapacitor*) capacitor {
	return [[DGMCapacitor alloc] initWithCapacitor:&dynamic_cast<dgmpp::Ship*>(self.type)->capacitor()];
}

- (DGMCalibrationPoints) usedCalibration {
	return static_cast<DGMCalibrationPoints>(dynamic_cast<dgmpp::Ship*>(self.type)->usedCalibration());
}

- (DGMCalibrationPoints) totalCalibration {
	return static_cast<DGMCalibrationPoints>(dynamic_cast<dgmpp::Ship*>(self.type)->totalCalibration());
}

- (DGMGigaJoule) usedPowerGrid {
	return static_cast<DGMGigaJoule>(dynamic_cast<dgmpp::Ship*>(self.type)->usedPowerGrid());
}

- (DGMGigaJoule) totalPowerGrid {
	return static_cast<DGMGigaJoule>(dynamic_cast<dgmpp::Ship*>(self.type)->totalPowerGrid());
}

- (DGMTeraflops) usedCPU {
	return static_cast<DGMTeraflops>(dynamic_cast<dgmpp::Ship*>(self.type)->usedCPU());
}

- (DGMTeraflops) totalCPU {
	return static_cast<DGMTeraflops>(dynamic_cast<dgmpp::Ship*>(self.type)->totalCPU());
}

- (DGMMegabitsPerSecond) usedDroneBandwidth {
	return static_cast<DGMMegabitsPerSecond>(dynamic_cast<dgmpp::Ship*>(self.type)->usedDroneBandwidth());
}

- (DGMMegabitsPerSecond) totalDroneBandwidth {
	return static_cast<DGMMegabitsPerSecond>(dynamic_cast<dgmpp::Ship*>(self.type)->totalDroneBandwidth());
}

- (DGMCubicMeter) usedDroneBay {
	return static_cast<DGMCubicMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->usedDroneBay());
}

- (DGMCubicMeter) totalDroneBay {
	return static_cast<DGMCubicMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->totalDroneBay());
}

- (DGMCubicMeter) usedFighterHangar {
	return static_cast<DGMCubicMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->usedFighterHangar());
}

- (DGMCubicMeter) totalFighterHangar {
	return static_cast<DGMCubicMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->totalFighterHangar());
}

- (DGMCubicMeter) cargoCapacity {
	return static_cast<DGMCubicMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->cargoCapacity());
}

- (DGMCubicMeter) oreHoldCapacity {
	return static_cast<DGMCubicMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->oreHoldCapacity());
}

- (DGMResistances) resistances {
	return DGMResistancesMake(dynamic_cast<dgmpp::Ship*>(self.type)->resistances());
}

- (DGMTank) tank {
	return DGMTankMake(dynamic_cast<dgmpp::Ship*>(self.type)->tank());
}

- (DGMTank) effectiveTank {
	return DGMTankMake(dynamic_cast<dgmpp::Ship*>(self.type)->effectiveTank());
}

- (DGMTank) sustainableTank {
	return DGMTankMake(dynamic_cast<dgmpp::Ship*>(self.type)->sustainableTank());
}

- (DGMTank) effectiveSustainableTank {
	return DGMTankMake(dynamic_cast<dgmpp::Ship*>(self.type)->effectiveSustainableTank());
}

- (DGMHitPoints) hitPoints {
	return DGMHitPointsMake(dynamic_cast<dgmpp::Ship*>(self.type)->hitPoints());
}

- (DGMHitPoints) effectiveHitPoints {
	return DGMHitPointsMake(dynamic_cast<dgmpp::Ship*>(self.type)->effectiveHitPoints());
}

- (DGMDamageVector) turretsVolley {
	return DGMDamageVectorMake(dynamic_cast<dgmpp::Ship*>(self.type)->turretsVolley());
}

- (DGMDamageVector) launchersVolley {
	return DGMDamageVectorMake(dynamic_cast<dgmpp::Ship*>(self.type)->launchersVolley());
}

- (DGMDamageVector) dronesVolley {
	return DGMDamageVectorMake(dynamic_cast<dgmpp::Ship*>(self.type)->dronesVolley());
}

- (DGMDamagePerSecond) turretsDPS {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Ship*>(self.type)->turretsDPS());
}

- (DGMDamagePerSecond) launchersDPS {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Ship*>(self.type)->launchersDPS());
}

- (DGMDamagePerSecond) dronesDPS {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Ship*>(self.type)->dronesDPS());
}

- (DGMDamageVector) turretsDPSWithTaget:(DGMHostileTarget) target {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Ship*>(self.type)->turretsDPS(HostileTargetMake(target)));
}

- (DGMDamageVector) launchersDPSWithTaget:(DGMHostileTarget) target {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Ship*>(self.type)->launchersDPS(HostileTargetMake(target)));
}

- (DGMDamageVector) dronesDPSWithTaget:(DGMHostileTarget) target {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Ship*>(self.type)->dronesDPS(HostileTargetMake(target)));
}

- (DGMCubicMeterPerSecond) minerYield {
	return static_cast<DGMCubicMeterPerSecond>(dynamic_cast<dgmpp::Ship*>(self.type)->minerYield() * 1s);
}

- (DGMCubicMeterPerSecond) droneYield {
	return static_cast<DGMCubicMeterPerSecond>(dynamic_cast<dgmpp::Ship*>(self.type)->droneYield() * 1s);
}

- (NSTimeInterval) alignTime {
	return NSTimeIntervalMake(dynamic_cast<dgmpp::Ship*>(self.type)->alignTime());
}

- (DGMAstronomicalUnitsPerSecond) warpSpeed {
	return static_cast<DGMAstronomicalUnitsPerSecond>(dynamic_cast<dgmpp::Ship*>(self.type)->warpSpeed() * 1s);
}

- (DGMMetersPerSecond) velocity {
	return static_cast<DGMMetersPerSecond>(dynamic_cast<dgmpp::Ship*>(self.type)->velocity() * 1s);
}

- (DGMMeter) signatureRadius {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->signatureRadius());
}

- (DGMKilogram) mass {
	return static_cast<DGMKilogram>(dynamic_cast<dgmpp::Ship*>(self.type)->mass());
}

- (DGMCubicMeter) volume {
	return static_cast<DGMCubicMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->volume());
}

- (DGMMultiplier) agility {
	return static_cast<DGMMultiplier>(dynamic_cast<dgmpp::Ship*>(self.type)->agility());
}

- (DGMMetersPerSecond) maxVelocityInOrbit:(DGMMeter) radius {
	return static_cast<DGMMetersPerSecond>(dynamic_cast<dgmpp::Ship*>(self.type)->maxVelocityInOrbit(static_cast<dgmpp::Meter>(radius)) * 1s);
}

- (DGMMeter) orbitRadiusWithTransverseVelocity:(DGMMetersPerSecond) velocity {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->orbitRadiusWithTransverseVelocity(dgmpp::make_rate(velocity, 1s)));
}

- (DGMMeter) orbitRadiusWithAngularVelocity:(DGMRadiansPerSecond) velocity {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->orbitRadiusWithAngularVelocity(dgmpp::make_rate(velocity, 1s)));
}

- (NSInteger) maxTargets {
	return dynamic_cast<dgmpp::Ship*>(self.type)->maxTargets();
}

- (DGMMeter) maxTargetRange {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->maxTargetRange());
}

- (DGMPoints) scanStrength {
	return static_cast<DGMPoints>(dynamic_cast<dgmpp::Ship*>(self.type)->scanStrength());
}

- (DGMScanType) scanType {
	return static_cast<DGMScanType>(dynamic_cast<dgmpp::Ship*>(self.type)->scanType());
}

- (DGMMeter) probeSize {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Ship*>(self.type)->probeSize());
}

- (DGMMillimeter) scanResolution {
	return static_cast<DGMMillimeter>(dynamic_cast<dgmpp::Ship*>(self.type)->scanResolution());
}



@end
