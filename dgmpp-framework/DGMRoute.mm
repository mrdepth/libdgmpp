//
//  DGMRoute.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "DGMRoute.h"

@implementation DGMRoute

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (nonnull instancetype) initWithCommodity:(nonnull DGMCommodity*) commodity from:(nonnull DGMFacility*) from to:(nonnull DGMFacility*) to {
	if (self = [super init]) {
		_commodity = commodity;
		_from = from;
		_to = to;
	}
	return self;
}

@end
