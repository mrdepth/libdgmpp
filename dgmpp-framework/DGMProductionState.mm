//
//  DGMProductionState.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMState

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (nonnull instancetype) initWithState:(nonnull const dgmpp::State*) state {
	if (self = [super init]) {
		_state = state;
//		_timestamp = [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(state->timestamp)];
//		NSMutableArray* commodities = [NSMutableArray new];
//		for (const auto& i: state->commodities) {
//			[commodities addObject:[[DGMCommodity alloc] initWithCommodity:i]];
//		}
//		_commodities = commodities;
	}
	return self;
}

- (nonnull NSDate*) timestamp {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(_state->timestamp)];
}

- (nonnull NSArray<DGMCommodity*>*) commodities {
	NSMutableArray* result = [NSMutableArray new];
	for (const auto& i: _state->commodities) {
		[result addObject:[[DGMCommodity alloc] initWithCommodity:i]];
	}
	return result;
}

@end

@implementation DGMProductionState

- (nullable DGMProductionCycle*) cycle {
	if (auto cycle = dynamic_cast<const dgmpp::ProductionState*>(self.state)->cycle)
		return [[DGMProductionCycle alloc] initWithCycle:cycle];
	else
		return nil;
}

- (DGMPercent) efficiency {
	return dynamic_cast<const dgmpp::ProductionState*>(self.state)->efficiency;
}

@end
