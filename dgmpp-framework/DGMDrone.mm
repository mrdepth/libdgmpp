//
//  DGMDrone.m
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "Internal.h"

@implementation DGMDrone {
	std::unique_ptr<dgmpp::Drone> _drone;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	@try {
		_drone = dgmpp::Drone::Create(static_cast<dgmpp::TypeID>(typeID));
		if (self = [super initWithType:_drone.get()]) {
		}
		return self;
	}
	@catch(NSException* exc) {
		if (error)
			*error = [NSError errorWithDomain:exc.name code:0 userInfo:exc.userInfo];
		return nil;
	}
}

- (BOOL) isActive {
	return dynamic_cast<dgmpp::Drone*>(self.type)->active();
}

- (void) setActive:(BOOL)active {
	dynamic_cast<dgmpp::Drone*>(self.type)->active(active);
}

- (nullable DGMCharge*) charge {
	return (DGMCharge*) [DGMType type:dynamic_cast<dgmpp::Drone*>(self.type)->charge()];
}

- (DGMDroneSquadron) squadron {
	return static_cast<DGMDroneSquadron>(dynamic_cast<dgmpp::Drone*>(self.type)->squadron());
}

- (NSInteger) squadronSize {
	return dynamic_cast<dgmpp::Drone*>(self.type)->squadronSize();
}

- (NSInteger) squadronTag {
	return static_cast<NSInteger>(dynamic_cast<dgmpp::Drone*>(self.type)->squadronTag());
}

- (nullable DGMShip*) target {
	return (DGMShip*) [DGMType type: dynamic_cast<dgmpp::Drone*>(self.type)->target()];
}

- (BOOL) setTarget:(nullable DGMShip*) target error:(NSErrorPtr) error {
	@try {
		if (target)
			dynamic_cast<dgmpp::Drone*>(self.type)->target(dynamic_cast<dgmpp::Ship*>(target.type));
		else
			dynamic_cast<dgmpp::Drone*>(self.type)->target(nullptr);
		return YES;
	}
	@catch(NSException* exc) {
		if (error)
			*error = [NSError errorWithDomain:exc.name code:0 userInfo:exc.userInfo];
		return NO;
	}
}


- (NSTimeInterval) cycleTime {
	return NSTimeIntervalMake(dynamic_cast<dgmpp::Drone*>(self.type)->cycleTime());
}

- (DGMDamagePerSecond) dps {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Drone*>(self.type)->dps());
}

- (DGMDamagePerSecond) dpsWithTaget:(DGMHostileTarget) target {
	return DGMDamagePerSecondMake(dynamic_cast<dgmpp::Drone*>(self.type)->dps(HostileTargetMake(target)));
}

- (DGMMeter) optimal {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Drone*>(self.type)->optimal());
}

- (DGMMeter) falloff {
	return static_cast<DGMMeter>(dynamic_cast<dgmpp::Drone*>(self.type)->falloff());
}

- (DGMPoints) accuracyScore {
	return static_cast<DGMPoints>(dynamic_cast<dgmpp::Drone*>(self.type)->accuracyScore());
}

- (DGMCubicMeterPerSecond) miningYield {
	return static_cast<DGMCubicMeterPerSecond>(dynamic_cast<dgmpp::Drone*>(self.type)->miningYield() * 1s);
}

- (DGMMetersPerSecond) velocity {
	return static_cast<DGMMetersPerSecond>(dynamic_cast<dgmpp::Drone*>(self.type)->velocity() * 1s);
}


@end
