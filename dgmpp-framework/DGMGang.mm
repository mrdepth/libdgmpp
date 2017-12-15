//
//  DGMGang.m
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "Internal.h"

@implementation DGMGang {
	std::unique_ptr<dgmpp::Gang> _gang;
}

- (nonnull instancetype) init {
	_gang = dgmpp::Gang::Create();
	if (self = [super initWithType:_gang.get()]) {
	}
	return self;
}

- (void) addPilot:(nonnull DGMCharacter*) pilot {
	if (auto& ptr = pilot.character)
		_gang->add(std::move(ptr));
}

- (void) removePilot:(nonnull DGMCharacter*) pilot {
	_gang->remove(dynamic_cast<dgmpp::Character*>(pilot.type));
}

- (nonnull NSArray<DGMCharacter*>*) pilots {
	auto pilots = _gang->pilots();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:pilots.size()];
	for (auto i: pilots)
		[result addObject:[DGMType type:i]];
	return result;
}

@end
