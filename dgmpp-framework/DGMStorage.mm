//
//  DGMStorage.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMStorage

- (nonnull NSArray<DGMState*>*) states {
	const auto& v = dynamic_cast<dgmpp::Storage*>(self.facility)->states();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto& i: v)
		[result addObject: [[DGMState alloc] initWithState: i.get()]];
	return result;
}

@end
