//
//  DGMProductionCycle.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMProductionCycle {
	const dgmpp::ProductionCycle* _cycle;
}

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (nonnull instancetype) initWithCycle:(nonnull const dgmpp::ProductionCycle*) cycle {
	if (self = [super init]) {
		_cycle = cycle;
	}
	return self;

}

- (nonnull DGMCommodity*) yield {
	return [[DGMCommodity alloc] initWithCommodity:_cycle->yield];
}
- (nonnull DGMCommodity*) waste {
	return [[DGMCommodity alloc] initWithCommodity:_cycle->waste];
}

- (nonnull NSDate*) start {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(_cycle->start)];
}
- (NSTimeInterval) duration {
	return NSTimeIntervalMake(_cycle->duration);
}

- (nonnull NSDate*) end {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(_cycle->end())];
}


@end
