//
//  DGMPlanet.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMPlanet {
	std::unique_ptr<dgmpp::Planet> _planet;
}

- (nonnull instancetype) init {
	if (self = [super init]) {
		_planet.reset(new dgmpp::Planet());
	}
	return self;
}

- (nonnull NSArray<DGMFacility*>*) facilities {
	auto v = _planet->facilities();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto i: v)
		[result addObject: [DGMFacility facility:i]];
	return result;
}

- (nonnull NSDate*) lastUpdate {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(_planet->lastUpdate())];
}

- (void) setLastUpdate:(NSDate *)lastUpdate {
	_planet->lastUpdate(std::chrono::seconds(static_cast<std::chrono::seconds::rep>(lastUpdate.timeIntervalSinceReferenceDate)));
}

- (BOOL) addFacilityWithTypeID:(DGMTypeID) typeID identifier:(int64_t) identifier error:(NSErrorPtr) error {
	try {
		_planet->add(static_cast<dgmpp::TypeID>(typeID), identifier);
		return YES;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return NO;
	}
}

- (void) removeFacility:(nonnull DGMFacility*) facility {
	_planet->remove(facility.facility);

}

- (nullable DGMFacility*) objectAtIndexedSubscript: (int64_t) identifier {
	if (auto facility = (*_planet)[identifier])
		return [DGMFacility facility:facility];
	else
		return nil;
}

- (void) addRoute:(nonnull DGMRoute*) route {
	_planet->add(dgmpp::Route{route.from.facility, route.to.facility, route.commodity.commodity});
}

- (void) removeRoute:(nonnull DGMRoute*) route {
	_planet->remove(dgmpp::Route{route.from.facility, route.to.facility, route.commodity.commodity});
}

- (nonnull NSDate*) run {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(_planet->run())];
}


@end
