//
//  DGMModule.m
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "Internal.h"

@implementation DGMModule {
	std::unique_ptr<dgmpp::Module> _module;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	@try {
		_module = dgmpp::Module::Create(static_cast<dgmpp::TypeID>(typeID));
		if (self = [super initWithType:_module.get()]) {
		}
		return self;
	}
	@catch(NSException* exc) {
		if (error)
			*error = [NSError errorWithDomain:exc.name code:0 userInfo:exc.userInfo];
		return nil;
	}
}

- (DGMModuleSlot) slot {
	return static_cast<DGMModuleSlot>(dynamic_cast<dgmpp::Module*>(self.type)->slot());
}

- (DGMModuleHardpoint) hardpoint {
	return static_cast<DGMModuleHardpoint>(dynamic_cast<dgmpp::Module*>(self.type)->hardpoint());
}

- (NSInteger) socket {
	return static_cast<NSInteger>(dynamic_cast<dgmpp::Module*>(self.type)->socket());
}

- (DGMModuleState) state {
	return static_cast<DGMModuleState>(dynamic_cast<dgmpp::Module*>(self.type)->state());
}

- (void) setState:(DGMModuleState)state {
	dynamic_cast<dgmpp::Module*>(self.type)->state(static_cast<dgmpp::Module::State>(state));
}

- (DGMModuleState) preferredState {
	return static_cast<DGMModuleState>(dynamic_cast<dgmpp::Module*>(self.type)->preferredState());
}

- (nonnull NSArray<NSNumber*>*) availableStates {
	auto v = dynamic_cast<dgmpp::Module*>(self.type)->availableStates();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto i: v)
		[result addObject: @(static_cast<DGMModuleState>(i))];
	return result;
}

- (nullable DGMShip*) target {
	return (DGMShip*) [DGMType type: dynamic_cast<dgmpp::Module*>(self.type)->target()];
}

- (BOOL) setTarget:(nullable DGMShip*) target error:(NSErrorPtr) error {
	@try {
		if (target)
			dynamic_cast<dgmpp::Module*>(self.type)->target(dynamic_cast<dgmpp::Ship*>(target.type));
		else
			dynamic_cast<dgmpp::Module*>(self.type)->target(nullptr);
		return YES;
	}
	@catch(NSException* exc) {
		if (error)
			*error = [NSError errorWithDomain:exc.name code:0 userInfo:exc.userInfo];
		return NO;
	}
}

- (nullable DGMCharge*) charge {
	return (DGMCharge*) [DGMType type: dynamic_cast<dgmpp::Module*>(self.type)->charge()];
}

- (BOOL) setCharge:(nullable DGMCharge*) charge error:(NSErrorPtr) error {
	@try {
		if (charge && charge.charge)
			dynamic_cast<dgmpp::Module*>(self.type)->charge(std::move(charge.charge));
		else
			dynamic_cast<dgmpp::Module*>(self.type)->charge(nil);
		return YES;
	}
	@catch(NSException* exc) {
		if (error)
			*error = [NSError errorWithDomain:exc.name code:0 userInfo:exc.userInfo];
		return NO;
	}
}

- (nonnull NSArray<NSNumber*>*) chargeGroups {
	auto v = dynamic_cast<dgmpp::Module*>(self.type)->chargeGroups();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto i: v)
		[result addObject: @(static_cast<DGMGroupID>(i))];
	return result;
}

- (DGMChargeSize) chargeSize {
	return static_cast<DGMChargeSize>(dynamic_cast<dgmpp::Module*>(self.type)->chargeSize());
}

- (BOOL) isFail {
	return dynamic_cast<dgmpp::Module*>(self.type)->fail();
}

- (BOOL) canHaveState: (DGMModuleState) state {
	return dynamic_cast<dgmpp::Module*>(self.type)->canHaveState(static_cast<dgmpp::Module::State>(state));
}

- (BOOL) canFitCharge: (nonnull DGMCharge*) charge {
	return false;
}

- (NSTimeInterval) reloadTime {
	return NSTimeIntervalMake(dynamic_cast<dgmpp::Module*>(self.type)->reloadTime());
}

- (NSTimeInterval) cycleTime {
	return NSTimeIntervalMake(dynamic_cast<dgmpp::Module*>(self.type)->cycleTime());
}

- (NSTimeInterval) rawCycleTime {
	return NSTimeIntervalMake(dynamic_cast<dgmpp::Module*>(self.type)->rawCycleTime());
}

- (NSInteger) charges {
	return dynamic_cast<dgmpp::Module*>(self.type)->charges();
}

- (NSInteger) shots {
	return dynamic_cast<dgmpp::Module*>(self.type)->shots();
}

- (DGMGigaJoulePerSecond) capUse {
	return static_cast<DGMGigaJoulePerSecond>(dynamic_cast<dgmpp::Module*>(self.type)->capUse() * 1s);
}

- (DGMTeraflops) cpuUse {
	return static_cast<DGMTeraflops>(dynamic_cast<dgmpp::Module*>(self.type)->cpuUse());
}

- (DGMMegaWatts) powerGridUse {
	return static_cast<DGMMegaWatts>(dynamic_cast<dgmpp::Module*>(self.type)->powerGridUse());
}

- (DGMCalibrationPoints) calibrationUse {
	return static_cast<DGMCalibrationPoints>(dynamic_cast<dgmpp::Module*>(self.type)->calibrationUse());
}

- (DGMPoints) accuracyScore {
	return static_cast<DGMPoints>(dynamic_cast<dgmpp::Module*>(self.type)->accuracyScore());
}

- (DGMMeter) signatureResolution {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Module*>(self.type)->signatureResolution());
}

- (DGMCubicMeterPerSecond) miningYield {
	return static_cast<DGMCubicMeterPerSecond>(dynamic_cast<dgmpp::Module*>(self.type)->miningYield() * 1s);
}

- (DGMDamageVector) volley {
	return DGMDamageVectorMake(dynamic_cast<dgmpp::Module*>(self.type)->volley());
}

- (DGMDamagePerSecond) dps {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Module*>(self.type)->dps());
}

- (DGMDamagePerSecond) dpsWithTaget:(DGMHostileTarget) target {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Module*>(self.type)->dps(HostileTargetMake(target)));
}

- (DGMMeter) optimal {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Module*>(self.type)->optimal());
}

- (DGMMeter) falloff {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Module*>(self.type)->falloff());
}

- (NSTimeInterval) lifeTime {
	if (auto lifeTime = dynamic_cast<dgmpp::Module*>(self.type)->lifeTime())
		return NSTimeIntervalMake(*lifeTime);
	else
		return -1;
}


@end
